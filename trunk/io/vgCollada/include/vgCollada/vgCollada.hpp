// VGSDK - Copyright (C) 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCOLLADA_VGCOLLADA_HPP
#define _VGCOLLADA_VGCOLLADA_HPP

/**
 * @defgroup g_vgCollada vgCollada-(V)ersatile (G)raphical (COLLADA)
 *
 * @ingroup g_vgio
 */

/** 
 * @namespace vgCollada
 * 
 * @brief  (V)ersatile (G)raphical COLLADA reader and writer
 *
 * vgCollada is a vgsdk component to read and write (todo) the COLLADA digital asset exchange (DAE) schema.
 * 
 * @sa http://collada.org/
 * @sa http://khronos.org/collada/ for further informations.
 * 
 * \b vgCollada is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGCOLLADA_EXPORTS
	#define VGCOLLADA_API	__declspec(dllexport)
	#else
	#define VGCOLLADA_API	__declspec(dllimport)
	#endif

	#define VGCOLLADA_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGCOLLADA_EXPORTS
	#define VGCOLLADA_API __attribute__ ((visibility("default")))
	#define VGCOLLADA_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGCOLLADA_API __attribute__ ((visibility("hidden")))
	#define VGCOLLADA_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGCOLLADA_API
	#define VGCOLLADA_CLASS_API

#endif

#endif // #ifndef _VGCOLLADA_VGCOLLADA_HPP
