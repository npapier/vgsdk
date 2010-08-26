// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGPHYSICFS_VGPHYSICFS_HPP
#define _VGPHYSICFS_VGPHYSICFS_HPP

/** 
 * @namespace vgPhysicFS
 * 
 * @brief (V)ersatile (G)raphical PhysicFS.
 *
 * \b vgVz is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGPHYSICFS_EXPORTS
	#define VGPHYSICFS_API	__declspec(dllexport)
	#else
	#define VGPHYSICFS_API	__declspec(dllimport)
	#endif

	#define VGPHYSICFS_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGPHYSICFS_EXPORTS
	#define VGPHYSICFS_API __attribute__ ((visibility("default")))
	#define VGPHYSICFS_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGPHYSICFS_API __attribute__ ((visibility("hidden")))
	#define VGPHYSICFS_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGPHYSICFS_API
	#define VGPHYSICFS_CLASS_API

#endif



#endif // #ifndef _VGPHYSICFS_VGPHYSICFS_HPP
