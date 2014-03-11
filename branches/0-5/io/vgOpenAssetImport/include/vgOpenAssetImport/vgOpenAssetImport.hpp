// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGOPENASSETIMPORT_VGOPENASSETIMPORT_HPP
#define _VGOPENASSETIMPORT_VGOPENASSETIMPORT_HPP

/** 
 * @namespace vgOpenAssetImport
 * 
 * @brief (V)ersatile (G)raphical (OpenAssetImport)
 *
 * \b vgOpenAssetImport is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGOPENASSETIMPORT_EXPORTS
	#define VGOPENASSETIMPORT_API	__declspec(dllexport)
	#else
	#define VGOPENASSETIMPORT_API	__declspec(dllimport)
	#endif

	#define VGOPENASSETIMPORT_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGOPENASSETIMPORT_EXPORTS
	#define VGOPENASSETIMPORT_API __attribute__ ((visibility("default")))
	#define VGOPENASSETIMPORT_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGOPENASSETIMPORT_API __attribute__ ((visibility("hidden")))
	#define VGOPENASSETIMPORT_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGOPENASSETIMPORT_API
	#define VGOPENASSETIMPORT_CLASS_API

#endif



#endif // #ifndef _VGOPENASSETIMPORT_VGOPENASSETIMPORT_HPP
