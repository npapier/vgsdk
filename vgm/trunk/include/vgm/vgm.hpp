// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_VGM_H
#define _VGM_VGM_H

/** 
 * @namespace vgm
 * 
 * @brief Virtuals Graphical Mathematics
 *
 * Vgm is a collection of classes for doing basic linear algebra(matrix, vector and rotation...) and geometry
 * (line, box, plane...).
 * 
 * \b vgm is open source (LGPL).
 */

/**
 * @defgroup vgmGroup vgm
 */

/**
 * @defgroup Geometry Geometrical classes
 *
 * vgm provides some basic geometrical classes like box, line, plane and rectangle.
 * 
 * @ingroup vgmGroup
 */

/**
 * @defgroup LinearAlgebra Linear algebra.
 *
 * Linear Algebra consists mostly of matrix calculus. It formalises and gives geometrical interpretation of the resolution of equation systems.
 * It creates a formal link between matrix calculus and the use of linear and quadratic transformations.
 *
 * This linear algebra package contains mainly matrix, rotation and vectors classes.
 * 
 * @ingroup vgmGroup
 */ 

#include <Virtuals/Type.h>

#ifdef _WIN32

   #ifdef VGM_EXPORTS
   #define VGM_API	__declspec(dllexport)
   #else
   #define VGM_API	__declspec(dllimport)
   #endif

#else

    #define VGM_API

#endif

#ifndef M_PI
#define M_PI       3.1415926535897931160E0
#define M_PI_2     1.5707963267948965580E0  
#endif



#endif // #ifndef _VGM_VGM_H
