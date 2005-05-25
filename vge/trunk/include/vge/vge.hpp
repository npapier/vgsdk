// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_VGE_H
#define _VGE_VGE_H

/** 
 * @namespace vge
 * 
 * @brief Virtuals Graphical Evaluation
 * 
 * \b vge is open source (LGPL).
 */

#include <Virtuals/Type.h>



#ifdef _WIN32

   #ifdef VGE_EXPORTS
   #define VGE_API	__declspec(dllexport)
   #else
   #define VGE_API	__declspec(dllimport)
   #endif

#else

	#define VGE_API

#endif



#endif //#ifndef _VGE_VGE_H
