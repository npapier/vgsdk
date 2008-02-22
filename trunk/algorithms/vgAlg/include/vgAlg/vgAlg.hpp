// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_VGALG_HPP
#define _VGALG_VGALG_HPP

/** 
 * @namespace vgAlg
 * 
 * @brief Virtuals Graphical Algorithms
 *
 * vgAlg is a collection of algorithms that could be applied on some vgd object.
 * 
 * \b vgAlg is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGALG_EXPORTS
	#define VGALG_API	__declspec(dllexport)
	#else
	#define VGALG_API	__declspec(dllimport)
	#endif

	#define VGALG_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGALG_EXPORTS
	#define VGALG_API __attribute__ ((visibility("default")))
	#define VGALG_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGALG_API __attribute__ ((visibility("hidden")))
	#define VGALG_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGALG_API
	#define VGALG_CLASS_API

#endif

#endif // #ifndef _VGALG_VGALG_HPP
