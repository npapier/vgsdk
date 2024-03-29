// VGSDK - Copyright (C) 2004-2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_VGM_HPP
#define _VGM_VGM_HPP

/**
 * @defgroup g_vgm vgm- (V)ersatile (G)raphical (M)athematics
 */

/**
 * @defgroup Geometry Geometrical classes
 *
 * vgm provides some basic geometrical classes like box, line, plane and rectangle.
 * 
 * @ingroup g_vgm
 */

/**
 * @defgroup LinearAlgebra Linear algebra.
 *
 * Linear Algebra consists mostly of matrix calculus. It formalises and gives geometrical interpretation of the resolution of equation systems.
 * It creates a formal link between matrix calculus and the use of linear and quadratic transformations.
 *
 * This linear algebra package contains mainly matrix, rotation and vectors classes.
 * 
 * @ingroup g_vgm
 */

/** 
 * @namespace vgm
 * 
 * @brief (V)ersatile (G)raphical (M)athematics
 *
 * Vgm is a collection of classes for doing basic linear algebra(matrix, vector and rotation...) and geometry
 * (line, box, plane...).
 * 
 * \b vgm is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGM_EXPORTS
	#define VGM_API	__declspec(dllexport)
	#else
	#define VGM_API	__declspec(dllimport)
	#endif

	#define VGM_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGM_EXPORTS
	#define VGM_API __attribute__ ((visibility("default")))
	#define VGM_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGM_API __attribute__ ((visibility("hidden")))
	#define VGM_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGM_API
	#define VGM_CLASS_API

#endif

namespace vgm
{
	const double PI		= 3.1415926535897931160E0;
	const double PI_2	= 1.5707963267948965580E0;
}



#endif // #ifndef _VGM_VGM_HPP
