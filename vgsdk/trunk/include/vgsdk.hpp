// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGSDK_VGSDK_H
#define _VGSDK_VGSDK_H

#include <Virtuals/Type.h>
#include <assert.h>

#ifdef _WIN32

	#if _MSC_VER > 1000
	#pragma once
	#pragma warning (disable:4251)// need a dll interface
	//#pragma warning (disable:4244)
	//#pragma warning (disable:4305)
	#endif // _MSC_VER > 1000

#else

#endif

#ifndef M_PI
#define M_PI       3.1415926535897931160E0
#define M_PI_2     1.5707963267948965580E0  
#endif



/** 
 * @namespace vgsdk
 * 
 * @brief Virtuals Graphical Software Development Kit
 *
 * \b vgsdk is a cross-platform C++/OpenGL library for the real-time visualization of 3d worlds.
 * \b vgsdk is open source (LGPL).
 */

#endif // #ifndef _VGSDK_VGSDK_H
