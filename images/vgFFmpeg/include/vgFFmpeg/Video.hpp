// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGFFMPEG_VIDEO_HPP
#define _VGFFMPEG_VIDEO_HPP

#include <string>
#include <vgd/basic/ImageInfo.hpp>
#include "vgFFmpeg/vgFFmpeg.hpp"

struct AVCodec;
struct AVCodecContext;
struct AVFormatContext;
struct AVFrame;



namespace vgFFmpeg
{



/**
 * @brief Base class to read and decode a video using FFmpeg
 *
  * @todo better error reporting/handling
  */
struct VGFFMPEG_API Video
{
	/**
	 * @brief Constructor
	 */
	Video( const std::string& pathFilename );

	/**
	 * @brief Destructor
	 */
	~Video();




	const bool next();

	const vgd::basic::ImageInfo& getCurrent();



protected:
	AVFormatContext *	pFormatCtx;
	int					videoStream;

	AVCodecContext	*pCodecCtx;
	AVCodec			*pCodec;

	AVFrame	*pFrame; 
	AVFrame	*pFrameRGB;

	int					numBytes;
	uint8 /*uint8_t*/ *	buffer;

	uint i;

	vgd::basic::ImageInfo m_currentImage;
};



} // namespace vgFFmpeg

#endif // #ifndef _VGFFMPEG_VIDEO_HPP
