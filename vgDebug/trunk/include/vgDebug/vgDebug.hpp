// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_H
#define _VGDEBUG_H

#include <vgsdk/vgsdk.hpp>

#ifdef _WIN32

   #ifdef VGDEBUG_EXPORTS
   #define VGDEBUG_API	__declspec(dllexport)
   #else
   #define VGDEBUG_API	__declspec(dllimport)
   #endif

#else

    #define VGDEBUG_API

#endif



/** 
 * @namespace vgDebug
 * 
 * @brief Virtuals Graphical Debug
 * 
 * \b vge is open source (LGPL).
 */

#endif //#ifndef _VGDEBUG_H
