// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

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

	/**
	 * @brief	Retrieves the width.
	 */
	const int getWidth() const;

	/**
	 * @brief	Retrieves the height.
	 */
	const int getHeight() const;

	/**
	 * @brief	Retrieves video duration (in seconds).
	 */
	const float getDuration() const;

	/**
	 * @brief Set video position to the given time (in seconds).
	 */
	void seek(const float time);



	const bool next();

	const vgd::basic::ImageInfo& getCurrent();

	const bool isOver();

	void restart();


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
