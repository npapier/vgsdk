// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_VGUI_HPP
#define _VGUI_VGUI_HPP

/**
 * @namespace vgUI
 *
 * @brief (V)ersatile (G)raphical abstraction of (U)ser (I)nterface.
 *
 * Cross-platform interface to OpenGL windows.
 */

/**
 * @defgroup g_vgUIGroup vgUI
 *
 * @brief (V)ersatile (G)raphical abstraction of (U)ser (I)nterface.
 *
 * \b vgUI is open source (LGPL).
 *
 * Cross-platform interface to OpenGL windows.
 */

#include <vgBase/Type.hpp>



#ifdef _WIN32

	#ifdef VGUI_EXPORTS
	#define VGUI_API	__declspec(dllexport)
	#else
	#define VGUI_API	__declspec(dllimport)
	#endif

	#define VGUI_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGUI_EXPORTS
	#define VGUI_API __attribute__ ((visibility("default")))
	#define VGUI_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGUI_API __attribute__ ((visibility("hidden")))
	#define VGUI_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGUI_API
	#define VGUI_CLASS_API

#endif



#endif // #ifndef _VGUI_VGUI_HPP
