// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_VGALG_H
#define _VGALG_VGALG_H

/** 
 * @namespace vgAlg
 * 
 * @brief Virtuals Graphical Algorithms
 *
 * vgAlg is a collection of algorithms that could be applied on some vgd object.
 * 
 * \b vgAlg is open source (LGPL).
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

   #ifdef VGALG_EXPORTS
   #define VGALG_API	__declspec(dllexport)
   #else
   #define VGALG_API	__declspec(dllimport)
   #endif

#else

    #define VGALG_API

#endif

#endif // #ifndef _VGALG_VGALG_H
