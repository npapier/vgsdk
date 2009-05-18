// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_VGGTK_HPP
#define _VGGTK_VGGTK_HPP

/**
 * @namespace vgGTK
 *
 * @brief	GTK-based specialization of vgUI and user interface building blocks.
 */

#include <vgBase/Type.hpp>



#ifdef _WIN32

	#ifdef VGGTK_EXPORTS
	#define VGGTK_API	__declspec(dllexport)
	#else
	#define VGGTK_API	__declspec(dllimport)
	#endif

	#define VGGTK_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGGTK_EXPORTS
	#define VGGTK_API __attribute__ ((visibility("default")))
	#define VGGTK_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGGTK_API __attribute__ ((visibility("hidden")))
	#define VGGTK_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGGTK_API
	#define VGGTK_CLASS_API

#endif




#endif // #ifndef _VGGTK_VGGTK_HPP
