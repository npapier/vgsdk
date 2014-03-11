// VGSDK - Copyright (C) 2010, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#ifndef _VGPHYSFS_VGPHYSFS_HPP
#define _VGPHYSFS_VGPHYSFS_HPP

/** 
 * @namespace vgPhysfs
 * 
 * @brief (V)ersatile (G)raphical PhysFS.
 *
 * This library encapsulates PhysicsFS to provide an abstract access to various archives using vgPhysfs::Archive.\n
 * In addition, encryption and decryption using blowfish algorithm is available using vgPhysfs::CBlowFish class.
 *
 * \b vgPhysfs is open source (LGPL).
 *
 * See http://icculus.org/physfs/ and http://www.schneier.com/blowfish.html
 *
 * @todo creates archive ? lzma library
 */

/**
 * @addtogroup g_archCrypto Archive and encryption/decryption
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGPHYSFS_EXPORTS
	#define VGPHYSFS_API	__declspec(dllexport)
	#else
	#define VGPHYSFS_API	__declspec(dllimport)
	#endif

	#define VGPHYSFS_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGPHYSFS_EXPORTS
	#define VGPHYSFS_API __attribute__ ((visibility("default")))
	#define VGPHYSFS_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGPHYSFS_API __attribute__ ((visibility("hidden")))
	#define VGPHYSFS_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGPHYSFS_API
	#define VGPHYSFS_CLASS_API

#endif



#endif // #ifndef _VGPHYSFS_VGPHYSFS_HPP
