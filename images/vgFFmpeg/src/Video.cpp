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
}

#include <stdio.h>
#include <stdlib.h>
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



static const int SDL_AUDIO_BUFFER_SIZE = 1024;


struct PacketQueue
{
	PacketQueue()
	:	first_pkt(0),
		last_pkt(0),
		nb_packets(0),
		size(0),
		mutex( SDL_CreateMutex() ),
		cond(  SDL_CreateCond() )
	{}

	~PacketQueue()
	{
		if ( mutex )	SDL_DestroyMutex( mutex );
		if ( cond )		SDL_DestroyCond( cond );
	}

	AVPacketList *first_pkt, *last_pkt;
	int nb_packets;
	int size;
	SDL_mutex *mutex;
	SDL_cond *cond;
};

vgd::Shp< PacketQueue > audioq;

int packet_queue_put(PacketQueue *q, AVPacket *pkt){
  AVPacketList *pkt1;
  if(av_dup_packet(pkt) < 0) {
    return -1;
  }
  pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList));
  if (!pkt1)
    return -1;
  pkt1->pkt = *pkt;
  pkt1->next = NULL;
  
  
  SDL_LockMutex(q->mutex);
  
  if (!q->last_pkt)
    q->first_pkt = pkt1;
  else
    q->last_pkt->next = pkt1;
  q->last_pkt = pkt1;
  q->nb_packets++;
  q->size += pkt1->pkt.size;
  SDL_CondSignal(q->cond);

  SDL_UnlockMutex(q->mutex);
  return 0;
}


bool audioPause = true;
int quit = 0;
int decode_interrupt_cb(void) {
  return quit;
}
// @todo url_set_interrupt_cb(decode_interrupt_cb); 
// @todo quit = 1

static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{

  AVPacketList *pkt1;
  int ret;
  
  SDL_LockMutex(q->mutex);
  
  for(;;) {
    
    if(quit) {
      ret = -1;
      break;
    }

    pkt1 = q->first_pkt;
    if (pkt1) {
      q->first_pkt = pkt1->next;
      if (!q->first_pkt)
	q->last_pkt = NULL;
      q->nb_packets--;
      q->size -= pkt1->pkt.size;
      *pkt = pkt1->pkt;
      av_free(pkt1);
      ret = 1;
      break;
    } else if (!block) {
      ret = 0;
      break;
    } else {
      SDL_CondWait(q->cond, q->mutex);
    }
  }
  SDL_UnlockMutex(q->mutex);
  return ret;
}



int audio_decode_frame(AVCodecContext *aCodecCtx, uint8_t *audio_buf, int buf_size) {

  static AVPacket pkt;
  static uint8_t *audio_pkt_data = NULL;
  static int audio_pkt_size = 0;

  int len1, data_size;

  for(;;) {
    while(audio_pkt_size > 0) {
      data_size = buf_size;
      len1 = avcodec_decode_audio2(aCodecCtx, (int16_t *)audio_buf, &data_size, 
				  audio_pkt_data, audio_pkt_size);
      if(len1 < 0) {
	/* if error, skip frame */
	audio_pkt_size = 0;
	break;
      }
      audio_pkt_data += len1;
      audio_pkt_size -= len1;
      if(data_size <= 0) {
	/* No data yet, get more frames */
	continue;
      }
      /* We have data, return it and come back for more later */
      return data_size;
    }
    if(pkt.data)
      av_free_packet(&pkt);

	if ( audioPause )
	{
		return -1;
	}

    if(quit){
      return -1;
    }

    if(packet_queue_get(audioq.get(), &pkt, 1) < 0) {
      return -1;
    }
    audio_pkt_data = pkt.data;
    audio_pkt_size = pkt.size;
  }
}


void sdl_audio_callback(void *userdata, Uint8 *stream, int len) {

  AVCodecContext *aCodecCtx = (AVCodecContext *)userdata;
  int len1, audio_size;

  static uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
  static unsigned int audio_buf_size = 0;
  static unsigned int audio_buf_index = 0;

  while(len > 0) {
    if(audio_buf_index >= audio_buf_size) {
      /* We have already sent all our data; get more */
      audio_size = audio_decode_frame(aCodecCtx, audio_buf, sizeof(audio_buf));
      if(audio_size < 0) {
	/* If error, output silence */
	audio_buf_size = SDL_AUDIO_BUFFER_SIZE;
	memset(audio_buf, 0, audio_buf_size);
      } else {
	audio_buf_size = audio_size;
      }
      audio_buf_index = 0;
    }
    len1 = audio_buf_size - audio_buf_index;
    if(len1 > len)
      len1 = len;
    memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);
    len -= len1;
    stream += len1;
    audio_buf_index += len1;
  }
}



}



Video::Video( const std::string& pathFilename )
:	m_pathfilename( pathFilename ),
	m_time(false),

	pFormatCtx(0),
	videoStream(-1),
	audioStream(-1),

	pCodecCtx(0),
	pCodec(0),
	img_convert_ctx(0),

	aCodecCtx(0),
	aCodec(0),
	//wanted_spec, spec,

	pFrame(0),
	pFrameRGB(0),

	numBytes(0),
	buffer(0),

	currentPos(0)
	//imageQueue
{
	quit = 0;

	if ( !SDL_WasInit(SDL_INIT_AUDIO) )
	{
		if ( SDL_InitSubSystem( SDL_INIT_AUDIO ) ) 
		{
			vgAssertN( false, "Unable to initialize SDL audio subsystem : %s", SDL_GetError() );
			return;
		}
		else
		{
			vgLogDebug("SDL audio subsystem initialized.");
		}
	}
	else
	{
		vgLogDebug("SDL audio subsystem already initialized.");
	}

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
		vgAssertN( false, "Couldn't find stream information in %s", pFormatCtx->filename );
		return;
	}

	// Dump information about file onto standard error
	dump_format(pFormatCtx, 0, pathFilename.c_str(), false);


	// Find the first video and audio stream 
	for(uint i=0; i<pFormatCtx->nb_streams; ++i)
	{
		if (	(videoStream < 0) &&
				pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO )
		{
			videoStream = i;
		}

		if (	(audioStream < 0) &&
				pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_AUDIO )
		{
			audioStream = i;
		}
	}

	if ( videoStream == -1 )
	{
		vgAssertN( false, "Didn't find a video stream in %s", pFormatCtx->filename );
		return;
	}



	// Get a pointer to the codec context for the video stream
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;

	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder( pCodecCtx->codec_id );
	if ( pCodec == NULL )
	{
		// Codec not found
		vgAssertN( false, "Video codec not found for %s", pFormatCtx->filename );
		return;
	}

	// Open codec
	if ( avcodec_open(pCodecCtx, pCodec) < 0 )
	{
		vgAssertN( false, "Could not open video codec for %s", pFormatCtx->filename );
		return;
	}


	// Allocate video frame and an AVFrame structure
	pFrame		= avcodec_alloc_frame();
	pFrameRGB	= avcodec_alloc_frame();

	if ( pFrame==NULL || pFrameRGB==NULL)
	{
		vgAssertN( false, "Unable to allocate frame and frameRGB" );
		return;
	}

	// Determine required buffer size and allocate buffer
	numBytes = avpicture_get_size(	PIX_FMT_RGBA, //PIX_FMT_RGB24,
									pCodecCtx->width,
									pCodecCtx->height );

	buffer = static_cast< uint8_t * >( av_malloc(numBytes*sizeof(uint8_t) ) );

	// Assign appropriate parts of buffer to image planes in pFrameRGB
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGBA, //PIX_FMT_RGB24,
					pCodecCtx->width, pCodecCtx->height);


	// Audio
	if ( audioStream >= 0 )
	{
		// Find the decoder for the audio stream
		aCodecCtx = pFormatCtx->streams[audioStream]->codec;

		aCodec = avcodec_find_decoder( aCodecCtx->codec_id );
		if ( !aCodec )
		{
			vgAssertN( false, "Audio codec not found for %s", pFormatCtx->filename );
			return;
		}

		// Open codec
		if ( avcodec_open(aCodecCtx, aCodec) < 0 )
		{
			vgAssertN( false, "Could not open audio codec for %s", pFormatCtx->filename );
			return;
		}

		// Set audio settings from codec info
		wanted_spec.freq = aCodecCtx->sample_rate;
		wanted_spec.format = AUDIO_S16SYS;
		wanted_spec.channels = aCodecCtx->channels;
		wanted_spec.silence = 0;
		wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
		wanted_spec.callback = sdl_audio_callback;
		wanted_spec.userdata = aCodecCtx;

		vgLogDebug("SDL_OpenAudio");
		audioq.reset( new PacketQueue() );
		if( SDL_OpenAudio(&wanted_spec, &spec) < 0)
		{
			vgAssertN( false, "SDL_OpenAudio: %s\n", SDL_GetError() );
		}

		m_time.restart();
		pause();
	}
}


Video::~Video()
{
	// shuts down audio
	pause();
	quit = 1;

	vgLogDebug("SDL_CloseAudio()");
	SDL_CloseAudio();

	if ( SDL_WasInit(SDL_INIT_AUDIO) )
	{
		SDL_QuitSubSystem( SDL_INIT_AUDIO );
		vgLogDebug("SDL audio subsystem released.");
	}
	else
	{
		vgLogDebug("No SDL audio subsystem.");
	}

	// Free the RGB image
	av_free(buffer);
	av_free(pFrameRGB);

	// Free the YUV frame
	av_free(pFrame);

	// Close the codec
	avcodec_close(aCodecCtx);
	// @todo img_convert_ctx
	avcodec_close(pCodecCtx);

	// Close the video file
	av_close_input_file(pFormatCtx);
}



const std::string Video::getPathFilename() const
{
	return m_pathfilename;
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
	if( pFormatCtx && pFormatCtx->streams[videoStream] )
	{
		const float frameRate =
			static_cast<float>(pFormatCtx->streams[videoStream]->time_base.den) /
			static_cast<float>(pFormatCtx->streams[videoStream]->time_base.num /** pFormatCtx->streams[videoStream]->ticks_per_frame*/ );
		return frameRate;
	}
	else
	{
		return 0.f;
	}
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


const int64 Video::getPlayingElapsedTime() const
{
	return m_time.getElapsedTime().ms();
}


const bool Video::isOver()
{
	const bool eof = url_feof( pFormatCtx->pb ) != 0;
	const bool emptyQueue = getImageQueueSize() == 0;
	return eof && emptyQueue;
}


const bool Video::isPaused() const
{
	return m_time.isPaused();
}


void Video::pause( const bool newState )
{
	if ( newState )
	{
		// pause
		audioPause = true;
		//SDL_PauseAudio(1); @todo

		if ( !m_time.isPaused() )	m_time.pause();
	}
	else
	{
		// unpause
		audioPause = false;
		SDL_PauseAudio(0);

		if ( m_time.isPaused() )	m_time.resume();
	}
}


void Video::play()
{
	pause( false );
}


void Video::seek( const float time )
{
	av_seek_frame( pFormatCtx, -1, (int64_t)(time*AV_TIME_BASE), AVSEEK_FLAG_FRAME );
}


void Video::restart()
{
	vgLogDebug( "restart()" );

	pause();

	vgLogDebug("SDL_CloseAudio");
	SDL_CloseAudio();
	audioq.reset( new PacketQueue() );

	vgLogDebug("SDL_OpenAudio");
	if( SDL_OpenAudio(&wanted_spec, &spec) < 0)
	{
		vgAssertN( false, "SDL_OpenAudio: %s\n", SDL_GetError() );
	}

	av_seek_frame( pFormatCtx, 0, 0, AVSEEK_FLAG_ANY ); 
	imageQueue.clear();

	m_time.restart();
	play();
}


const bool Video::processPacket()
{
	if ( !pFormatCtx )	return false;

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
				// @todo begin initImageConvert()
				// Convert the image into RGB32 format
				if ( img_convert_ctx == NULL )
				{
					const int w = pCodecCtx->width;
					const int h = pCodecCtx->height;

					img_convert_ctx = sws_getContext(
											w, h, pCodecCtx->pix_fmt,
											w, h, PIX_FMT_RGBA/*PIX_FMT_RGB24*/,
											SWS_FAST_BILINEAR, //SWS_BICUBIC,
											NULL, NULL, NULL);

					if ( img_convert_ctx == NULL)
					{
						vgAssertN(false, "vgFFmpeg: Cannot initialize the conversion context!");
						return false;
					}
				}
				// @todo begin end initImageConvert()

				int ret = sws_scale(	img_convert_ctx, 
										pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
										pFrameRGB->data, pFrameRGB->linesize );

				using vgd::basic::Image;
				vgd::Shp< Image > newImage = vgd::makeShp( new Image(
					pCodecCtx->width, pCodecCtx->height, 1,
					Image::RGBA,
					Image::UINT8,
					pFrameRGB->data[0] )
					);

				// Computes pts (Presentation TimeStamp)
				const double	ptsf		= (packet.dts != AV_NOPTS_VALUE) ? packet.dts : 0.f;
				const double	ptsInSecond	= ptsf * av_q2d( pFormatCtx->streams[videoStream]->time_base );
				const int64		ptsInMS		= static_cast< int64 >( ptsInSecond * 1000.f );
				imageQueue.put( vgd::makeShp( new ImageFrame(newImage, ptsInMS) ) );

				//
				av_free_packet( &packet );// @todo not very cute (DUPLICATED)
				return true;
			}
		}
		else if ( packet.stream_index == audioStream )
		{
			packet_queue_put( audioq.get(), &packet );
			return true;
		}
		else
		{
			// Free the packet that was allocated by av_read_frame
			av_free_packet( &packet );
		}
	}

	return false;
}


const vgd::Shp< ImageFrame > Video::getImage()
{
	vgd::Shp< ImageFrame > imageFrame = imageQueue.get( false );

	if ( imageFrame )
	{
		currentPos = imageFrame->getPosition();
	}

	return imageFrame;
}


const int Video::getImageQueueSize() const
{
	return imageQueue.size();
}



} // namespace vgFFmpeg
