// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCAIRO_VGCAIRO_HPP
#define _VGCAIRO_VGCAIRO_HPP

/** 
 * @namespace vgCairo
 * 
 * @brief (V)ersatile (G)raphical (Cairo)
 *
 * vgCairo contains an implementation of IImage abstract class using the cairo library (a powerful 2d graphics library).
 * 
 * \b vgCairo is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGCAIRO_EXPORTS
	#define VGCAIRO_API	__declspec(dllexport)
	#else
	#define VGCAIRO_API	__declspec(dllimport)
	#endif

	#define VGCAIRO_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGCAIRO_EXPORTS
	#define VGCAIRO_API __attribute__ ((visibility("default")))
	#define VGCAIRO_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGCAIRO_API __attribute__ ((visibility("hidden")))
	#define VGCAIRO_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGCAIRO_API
	#define VGCAIRO_CLASS_API

#endif



#endif // #ifndef _VGCAIRO_VGCAIRO_HPP
