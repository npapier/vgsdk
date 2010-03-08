// VGSDK - Copyright (C) 2006, 2008, 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_VGOPENCOLLADA_HPP
#define _VGOPENCOLLADA_VGOPENCOLLADA_HPP

/**
 * @defgroup g_vgOpenCOLLADA vgCollada-(V)ersatile (G)raphical (OpenCOLLADA)
 *
 * @ingroup g_vgio
 */

/** 
 * @namespace vgOpenCOLLADA
 * 
 * @brief  (V)ersatile (G)raphical OpenCOLLADA reader and writer
 *
 * vgOpenCollada is a vgsdk component to read and write (todo) the COLLADA digital asset exchange (DAE) schema using the OpenCOLLADA library.
 * 
 * @sa http://collada.org/
 * @sa http://khronos.org/collada/ for further informations.
 * @sa http://code.google.com/p/opencollada/
 * 
 * \b vgOpenCOLLADA is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGOPENCOLLADA_EXPORTS
	#define VGOPENCOLLADA_API	__declspec(dllexport)
	#else
	#define VGOPENCOLLADA_API	__declspec(dllimport)
	#endif

	#define VGOPENCOLLADA_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGOPENCOLLADA_EXPORTS
	#define VGOPENCOLLADA_API __attribute__ ((visibility("default")))
	#define VGOPENCOLLADA_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGOPENCOLLADA_API __attribute__ ((visibility("hidden")))
	#define VGOPENCOLLADA_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGOPENCOLLADA_API
	#define VGOPENCOLLADA_CLASS_API

#endif

#endif // #ifndef _VGOPENCOLLADA_VGOPENCOLLADA_HPP

