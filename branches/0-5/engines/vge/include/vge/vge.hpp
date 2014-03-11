// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_VGE_HPP
#define _VGE_VGE_HPP

/** 
 * @namespace vge
 * 
 * @brief (V)ersatile (G)raphical (E)valuation
 * 
 * \b vge is open source (LGPL).
 */

#include <vgBase/Type.hpp>


#ifdef _WIN32

	#ifdef VGE_EXPORTS
	#define VGE_API __declspec(dllexport)
	#else
	#define VGE_API __declspec(dllimport)
	#endif
	
	#define VGE_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGE_EXPORTS
	#define VGE_API __attribute__ ((visibility("default")))
	#define VGE_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGE_API __attribute__ ((visibility("hidden")))
	#define VGE_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGE_API
	#define VGE_CLASS_API

#endif


#endif //#ifndef _VGE_VGE_HPP
