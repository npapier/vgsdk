// VGSDK - Copyright (C) 2008, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGOBJ_VGOBJ_HPP
#define _VGOBJ_VGOBJ_HPP

/**
 * @namespace vgObj
 *
 * @brief OBJ files serializer.
 *
 * Serializer for the .obj files : http://fr.wikipedia.org/wiki/OBJ (a
 * more exhaustive description of this file format can be found here :
 * http://people.scs.fsu.edu/~burkardt/txt/obj_format.txt)
 *
 * For now, only triangles are supported.
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGOBJ_EXPORTS
	#define VGOBJ_API	__declspec(dllexport)
	#else
	#define VGOBJ_API	__declspec(dllimport)
	#endif

	#define VGOBJ_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGOBJ_EXPORTS
	#define VGOBJ_API __attribute__ ((visibility("default")))
	#define VGOBJ_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGOBJ_API __attribute__ ((visibility("hidden")))
	#define VGOBJ_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGOBJ_API
	#define VGOBJ_CLASS_API

#endif



#endif // #ifndef _VGOBJ_VGOBJ_HPP
