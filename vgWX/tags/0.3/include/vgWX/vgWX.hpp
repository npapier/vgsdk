// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_VGWX_H
#define _VGWX_VGWX_H

/** 
 * @namespace vgWX
 * 
 * @brief (V)irtuals (G)raphical bindings for (wx)Widgets.
 *
 * \b vgWX is open source (LGPL).
 */

/**
 * @defgroup g_vgWXGroup vgWX
 * 
 * @brief (V)irtuals (G)raphical bindings for (wx)Widgets.
 *
 * \b vgWX is open source (LGPL).
 * 
 * vgWX is a collection of classes or widgets that simplify the creation of 3D window designed to be used with VGL.
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

   #ifdef VGWX_EXPORTS
   #define VGWX_API	__declspec(dllexport)
   #else
   #define VGWX_API	__declspec(dllimport)
   #endif

#else

    #define VGWX_API

#endif



#endif // #ifndef _VGWX_VGWX_H
