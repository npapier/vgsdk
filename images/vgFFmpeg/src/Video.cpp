// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgFFmpeg/Video.hpp"
#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswscale/swscale.h>
}

#include <stdio.h>
#include <stdlib.h>
#include <vgd/Shp.hpp>
#include <vgd/basic/Image.hpp>
#include <vgDebug/convenience.hpp>



namespace vgFFmpeg
{

namespace
{


/**
 * @brief Global startup and shutdown of FFmpeg library
 */
struct FFmpegStartupManagement
{
	/**
	 * @brief Default constructor that initializes FFmpeg library.
	 */
	FFmpegStartupManagement()
	{
		// Register all formats and codecs
		vgLogDebug("FFmpeg library startup.");
		av_register_all();
	}

	/**
	 * @brief Default destructor that shutdown FFmpeg library.
	 */
	~FFmpegStartupManagement()
	{
		vgLogDebug("FFmpeg library shutdown.");
	}
};

	static FFmpegStartupManagement ffmpegStartupManagement; ///< Global startup and shutdown of ffmpeg library 
}



Video::Video( const std::string& pathFilename )
:	pFormatCtx(0),
	videoStream(-1),

	pCodecCtx(0),
	pCodec(0),

	pFrame(0),
	pFrameRGB(0),

	numBytes(0),
	buffer(0),

	i(0),
	currentPos(0)
	// m_currentImage
{
	// Open video file
	if ( av_open_input_file(&pFormatCtx, pathFilename.c_str(), NULL, 0, NULL)!=0 )
	{
		// Couldn't open file
		vgLogDebug2( "vgFFmpeg: Couldn't open file %s", pathFilename.c_str() );
		return;
		//throw std::exception("vgFFmpeg: Couldn't open file.");
	}

	// Retrieve stream information
	if ( av_find_stream_info(pFormatCtx)<0 )
	{
		// Couldn't find stream information
		return;
	}

	// Dump information about file onto standard error
	dump_format(pFormatCtx, 0, pathFilename.c_str(), false);


	// Find the first video stream
	for(i=0; i<pFormatCtx->nb_streams; ++i)
	{
		if ( pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO )
		{
			videoStream = i;
			break;
		}
	}

	if ( videoStream == -1 )
	{
		// Didn't find a video stream
		return;
		//return -1; 
	}


	// Get a pointer to the codec context for the video stream
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;

	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder( pCodecCtx->codec_id );
	if ( pCodec == NULL )
	{
		// Codec not found
		return;
		//return -1; 
	}

	// Open codec
	if ( avcodec_open(pCodecCtx, pCodec) < 0 )
	{
		// Could not open codec
		return;
		//return -1;
	}

	// Allocate video frame and an AVFrame structure
	pFrame		= avcodec_alloc_frame();
	pFrameRGB	= avcodec_alloc_frame();

	if ( pFrame==NULL || pFrameRGB==NULL)
		return;

	// Determine required buffer size and allocate buffer
	numBytes = avpicture_get_size(	PIX_FMT_RGBA, //PIX_FMT_RGB24,
									pCodecCtx->width,
									pCodecCtx->height );
	// @todo uses new
	buffer = static_cast< uint8_t * >( malloc(numBytes) );

	// Assign appropriate parts of buffer to image planes in pFrameRGB
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGBA, //PIX_FMT_RGB24,
					pCodecCtx->width, pCodecCtx->height);

	//
	i = 0;
}


Video::~Video()
{
	// @todo if buffer != 0 ...

	// Free the RGB image
	free(buffer);
	av_free(pFrameRGB);

	// Free the YUV frame
	av_free(pFrame);

	// Close the codec
	avcodec_close(pCodecCtx);

	// Close the video file
	av_close_input_file(pFormatCtx);
}



const int Video::getWidth() const
{
	return pCodecCtx ? pCodecCtx->width : 0;
}



const int Video::getHeight() const
{
	return pCodecCtx ? pCodecCtx->height : 0;
}



const float Video::getFrameRate() const
{
	return pCodecCtx ?
		static_cast<float>(pCodecCtx->time_base.den) / static_cast<float>(pCodecCtx->time_base.num * pCodecCtx->ticks_per_frame ) :
		0;
}



const float Video::getDuration() const
{
	if( pFormatCtx && pFormatCtx->streams[videoStream] )
	{
		const int num = pFormatCtx->streams[videoStream]->time_base.num;
		const int den = pFormatCtx->streams[videoStream]->time_base.den;

		return pFormatCtx->streams[videoStream]->duration * ( num / (float)den );
	}
	else
	{
		return 0.f;
	}
}


const float Video::getPosition() const
{
	if( pFormatCtx && pFormatCtx->streams[videoStream] )
	{
		const int num = pFormatCtx->streams[videoStream]->time_base.num;
		const int den = pFormatCtx->streams[videoStream]->time_base.den;

		return currentPos*(num/(float)den);
	}
	else
	{
		return 0.f;
	}
}


const bool Video::isOver()
{
	return url_feof( pFormatCtx->pb );
}


void Video::seek( const float time )
{
	av_seek_frame(pFormatCtx, -1, (int64_t)(time*AV_TIME_BASE), AVSEEK_FLAG_FRAME);
}


void Video::restart()
{
	av_seek_frame( pFormatCtx, 0, 0, AVSEEK_FLAG_ANY ); 
}


const bool Video::next()
{
	if ( pFormatCtx == 0 )
	{
		return false;
	}

	//
	AVPacket packet;

	while( av_read_frame( pFormatCtx, &packet) >= 0 )
	{
		// Is this a packet from the video stream ?
		if ( packet.stream_index == videoStream )
		{
			// Decode video frame
			int frameFinished = 0;
			avcodec_decode_video(	pCodecCtx, pFrame, &frameFinished,
									packet.data, packet.size);

			// Did we get a video frame ?
			if ( frameFinished )
			{
				// ***
				// @todo Moves convert stuff
				static struct SwsContext *img_convert_ctx;

				// Convert the image into RGB32 format
				if ( img_convert_ctx == NULL )
				{
					const int w = pCodecCtx->width;
					const int h = pCodecCtx->height;

					img_convert_ctx = sws_getContext(
											w, h, pCodecCtx->pix_fmt,
											w, h, PIX_FMT_RGBA/*PIX_FMT_RGB24*/,
											SWS_BICUBIC, //SWS_FAST_BILINEAR, //SWS_BICUBIC,
											NULL, NULL, NULL);

					if ( img_convert_ctx == NULL)
					{
						// @todo
						vgLogDebug("vgFFmpeg: Cannot initialize the conversion context!");
						return false;
					}
				}
				// ***

				int ret = sws_scale(	img_convert_ctx, 
										pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
										pFrameRGB->data, pFrameRGB->linesize );

				const int width = pCodecCtx->width;
				const int height = pCodecCtx->height;

				using vgd::basic::IImage;
				m_currentImage.set(
					pCodecCtx->width,
					pCodecCtx->height,
					1,
					IImage::RGBA,
					IImage::UINT8,
					pFrameRGB->data[0] );

				/*//
				uint8 * pixels = static_cast< uint8* >( m_currentImage.editPixels() );

				// Write pixel data
				for(int y=0; y<height; y++)
				{
					memcpy(		pixels + y*width*3,
								pFrameRGB->data[0]+y*pFrameRGB->linesize[0],
								width*3 );
				}
				m_currentImage.editPixelsDone();
				//m_currentImage.save("video.png");*/

				//
				currentPos = packet.dts;
				av_free_packet( &packet );// @todo not very cute (DUPLICATED)
				return true;
			}
		}

		// Free the packet that was allocated by av_read_frame
		av_free_packet( &packet );
	}

	return false;
}


const vgd::basic::ImageInfo& Video::getCurrent()
{
	assert( m_currentImage.isEmpty() == false && "Current image is empty." );
	return m_currentImage;
}


} // namespace vgFFmpeg
