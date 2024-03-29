// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_VGQT_HPP_
#define _VGQT_VGQT_HPP_

/**
 * @namespace vgQt
 *
 * @brief	Qt-based specialization of vgUI and user interface building blocks.
 */

#include <vgBase/Type.hpp>

#ifdef WIN32

	#ifdef VGQT_EXPORTS
	#define VGQT_API	__declspec(dllexport)
	#else
	#define VGQT_API	__declspec(dllimport)
	#endif

	#define VGQT_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGQT_EXPORTS
	#define VGQT_API __attribute__ ((visibility("default")))
	#define VGQT_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGQT_API __attribute__ ((visibility("hidden")))
	#define VGQT_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGQT_API
	#define VGQT_CLASS_API

#endif

#define VGQT_CLASS_API

#endif // _VGQT_VGQT_HPP_
