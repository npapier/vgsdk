// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGTRIAN_VGTRIAN_H
#define _VGTRIAN_VGTRIAN_H

/** 
 * @namespace vgTrian
 * 
 * @brief Virtuals Graphical Trian files serializer.
 *
 * \b vgTrian is open source (LGPL).
 */

#include <vgsdk/vgsdk.hpp>

#ifdef _WIN32

   #ifdef VGTRIAN_EXPORTS
   #define VGTRIAN_API	__declspec(dllexport)
   #else
   #define VGTRIAN_API	__declspec(dllimport)
   #endif

#else

    #define VGTRIAN_API

#endif



#endif // #ifndef _VGTRIAN_VGTRIAN_H
