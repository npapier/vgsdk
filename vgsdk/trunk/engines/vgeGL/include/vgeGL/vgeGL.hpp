// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_VGEGL_HPP
#define _VGEGL_VGEGL_HPP

/** 
 * @namespace vgeGL
 * 
 * @brief Virtuals Graphical Evaluation with OpenGL
 * 
 * \b vgeGL is open source (LGPL).
 */

#include <vgBase/Type.hpp>


#ifndef _VGEGL_DISABLED_GLE_

#include <gle/Wrapper.hpp>
#include <gle/WrapperGen.hpp>
#include <gle/OpenGLExtensionsGen.hpp>

#endif


#ifdef _WIN32

   #ifdef VGEGL_EXPORTS
   #define VGEGL_API	__declspec(dllexport)
   #else
   #define VGEGL_API	__declspec(dllimport)
   #endif

#else

    #define VGEGL_API

#endif



#endif //#ifndef _VGEGL_VGEGL_HPP
