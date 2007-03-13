// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGITK_VGITK_H
#define _VGITK_VGITK_H

/** 
 * @namespace vgITK
 * 
 * @brief Virtuals Graphical ITK
 *
 * vgITK is a collection of method to convert vgd::basic::IImage to ITK image.
 * 
 * \b vgITK is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

   #ifdef VGITK_EXPORTS
   #define VGITK_API	__declspec(dllexport)
   #else
   #define VGITK_API	__declspec(dllimport)
   #endif

#else

    #define VGITK_API

#endif



#endif // #ifndef _VGITK_VGITK_H
