// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_VGWX_HPP
#define _VGWX_VGWX_HPP

/** 
 * @namespace vgWX
 * 
 * @brief (V)irtuals (G)raphical bindings for (wx)Widgets.
 *
 * \b vgWX is open source (LGPL).
 */

/**
 * @defgroup g_vgWXGroup vgWX
 * 
 * @brief (V)irtuals (G)raphical bindings for (wx)Widgets.
 *
 * \b vgWX is open source (LGPL).
 * 
 * vgWX is a collection of classes or widgets that simplify the creation of 3D window designed to be used with vgSDK.
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGWX_EXPORTS
	#define VGWX_API	__declspec(dllexport)
	#else
	#define VGWX_API	__declspec(dllimport)
	#endif

	#define VGWX_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGWX_EXPORTS
	#define VGWX_API __attribute__ ((visibility("default")))
	#define VGWX_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGWX_API __attribute__ ((visibility("hidden")))
	#define VGWX_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGWX_API
	#define VGWX_CLASS_API

#endif



#endif // #ifndef _VGWX_VGWX_HPP
