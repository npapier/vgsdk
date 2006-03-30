// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDK_VGSDK_HPP
#define _VGSDK_VGSDK_HPP

#include <vgBase/Type.hpp>

/** 
 * @namespace vgsdk
 * 
 * @brief Virtuals Graphical Software Development Kit
 *
 * \b vgsdk is a cross-platform C++/OpenGL library for the real-time visualization of 3d worlds.
 * \b vgsdk is open source (LGPL).
 */

#ifdef _WIN32

   #ifdef VGSDK_EXPORTS
   #define VGSDK_API	__declspec(dllexport)
   #else
   #define VGSDK_API	__declspec(dllimport)
   #endif

#else

    #define VGSDK_API

#endif

#endif // #ifndef _VGSDK_VGSDK_HPP
