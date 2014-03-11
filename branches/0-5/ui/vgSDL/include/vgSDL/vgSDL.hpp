// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGSDL_VGSDL_HPP
#define _VGSDL_VGSDL_HPP

/**
 * @namespace vgSDL
 *
 * @brief	Provides SDL based user interface services.
 */

#include <vgBase/Type.hpp>



#ifdef _WIN32

	#ifdef VGSDL_EXPORTS
	#define VGSDL_API	__declspec(dllexport)
	#else
	#define VGSDL_API	__declspec(dllimport)
	#endif

	#define VGSDL_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGSDL_EXPORTS
	#define VGSDL_API __attribute__ ((visibility("default")))
	#define VGSDL_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGSDL_API __attribute__ ((visibility("hidden")))
	#define VGSDL_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGSDL_API
	#define VGSDL_CLASS_API

#endif




#endif // #ifndef _VGSDL_VGSDL_HPP
