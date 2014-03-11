// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGITK_VGITK_HPP
#define _VGITK_VGITK_HPP

/** 
 * @namespace vgITK
 * 
 * @brief (V)ersatile (G)raphical (ITK)
 *
 * vgITK is a collection of functions to :
 * - create an itk image from a vgsdk image (see vgd::basic::IImage). The buffer is shared and owned by vgsdk.
 * - create vgsdk image using an itk reader.
 * @todo save vgsdk image using an itk writer.
 * 
 * \b vgITK is open source (LGPL).
 *
 * @todo adds documentation to g_image (doxygen group)
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGITK_EXPORTS
	#define VGITK_API	__declspec(dllexport)
	#else
	#define VGITK_API	__declspec(dllimport)
	#endif

	#define VGITK_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGITK_EXPORTS
	#define VGITK_API __attribute__ ((visibility("default")))
	#define VGITK_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGITK_API __attribute__ ((visibility("hidden")))
	#define VGITK_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGITK_API
	#define VGITK_CLASS_API

#endif



#endif // #ifndef _VGITK_VGITK_HPP
