// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGTRIAN_VGTRIAN_HPP
#define _VGTRIAN_VGTRIAN_HPP

/** 
 * @namespace vgTrian
 * 
 * @brief Virtuals Graphical Trian files serializer.
 *
 * \b vgTrian is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGTRIAN_EXPORTS
	#define VGTRIAN_API	__declspec(dllexport)
	#else
	#define VGTRIAN_API	__declspec(dllimport)
	#endif

	#define VGTRIAN_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGTRIAN_EXPORTS
	#define VGTRIAN_API __attribute__ ((visibility("default")))
	#define VGTRIAN_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGTRIAN_API __attribute__ ((visibility("hidden")))
	#define VGTRIAN_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGTRIAN_API
	#define VGTRIAN_CLASS_API

#endif



#endif // #ifndef _VGTRIAN_VGTRIAN_HPP
