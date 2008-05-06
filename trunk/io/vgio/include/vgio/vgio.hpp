// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGIO_VGIO_HPP
#define _VGIO_VGIO_HPP


#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGIO_EXPORTS
	#define VGIO_API	__declspec(dllexport)
	#else
	#define VGIO_API	__declspec(dllimport)
	#endif

	#define VGIO_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGIO_EXPORTS
	#define VGIO_API __attribute__ ((visibility("default")))
	#define VGIO_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGIO_API __attribute__ ((visibility("hidden")))
	#define VGIO_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGIO_API
	#define VGIO_CLASS_API

#endif



#endif // #ifndef _VGIO_VGIO_HPP
