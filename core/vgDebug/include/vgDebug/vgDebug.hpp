// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_HPP
#define _VGDEBUG_HPP

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGDEBUG_EXPORTS
	#define VGDEBUG_API	__declspec(dllexport)
	#else
	#define VGDEBUG_API	__declspec(dllimport)
	#endif

	#define VGDEBUG_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGDEBUG_EXPORTS
	#define VGDEBUG_API __attribute__ ((visibility("default")))
	#define VGDEBUG_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGDEBUG_API __attribute__ ((visibility("hidden")))
	#define VGDEBUG_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGDEBUG_API
	#define VGDEBUG_CLASS_API

#endif



/** 
 * @namespace vgDebug
 * 
 * @brief (V)ersatile (G)raphical Debug
 * 
 * \b vgDebug is open source (LGPL).
 */

#endif //#ifndef _VGDEBUG_HPP
