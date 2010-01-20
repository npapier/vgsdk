// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGFFMPEG_VGFFMPEG_HPP
#define _VGFFMPEG_VGFFMPEG_HPP

/** 
 * @namespace vgFFmpeg
 * 
 * @brief (V)ersatile (G)raphical (FFmpeg)
 *
 * FFmpeg is a complete, cross-platform solution to record, convert and stream audio and video. It includes libavcodec - the leading audio/video codec library. See http://ffmpeg.org
 * vgFFmpeg contains several wrapper around the FFmpeg library.
 * 
 * \b vgFFmpeg is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGFFMPEG_EXPORTS
	#define VGFFMPEG_API	__declspec(dllexport)
	#else
	#define VGFFMPEG_API	__declspec(dllimport)
	#endif

	#define VGFFMPEG_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGFFMPEG_EXPORTS
	#define VGFFMPEG_API __attribute__ ((visibility("default")))
	#define VGFFMPEG_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGFFMPEG_API __attribute__ ((visibility("hidden")))
	#define VGFFMPEG_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGFFMPEG_API
	#define VGFFMPEG_CLASS_API

#endif



#endif // #ifndef _VGFFMPEG_VGFFMPEG_HPP
