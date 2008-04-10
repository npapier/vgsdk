// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_VGEGL_HPP
#define _VGEGL_VGEGL_HPP

/** 
 * @namespace vgeGL
 * 
 * @brief (V)ersatile (G)raphical (E)valuation with Open(GL)
 * 
 * \b vgeGL is open source (LGPL).
 */

#include <vgBase/Type.hpp>


#ifndef _VGEGL_DISABLED_GLE_

#include <gle/Wrapper.hpp>
#include <gle/WrapperGen.hpp>
#include <gle/OpenGLExtensionsGen.hpp>

#endif


#ifdef _WIN32

	#ifdef VGEGL_EXPORTS
	#define VGEGL_API	__declspec(dllexport)
	#else
	#define VGEGL_API	__declspec(dllimport)
	#endif

	#define VGEGL_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGEGL_EXPORTS
	#define VGEGL_API __attribute__ ((visibility("default")))
	#define VGEGL_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGEGL_API __attribute__ ((visibility("hidden")))
	#define VGEGL_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGEGL_API
	#define VGEGL_CLASS_API

#endif


#endif //#ifndef _VGEGL_VGEGL_HPP
