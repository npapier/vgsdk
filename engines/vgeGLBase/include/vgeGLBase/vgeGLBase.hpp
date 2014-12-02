// VGSDK - Copyright (C) 2004, 2009, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

//#ifndef _VGEGLBASE_VGEGLBASE_HPP
//#define _VGEGLBASE_VGEGLBASE_HPP

/** 
* @namespace vgeGLBase
* 
* @brief (V)ersatile (G)raphical (E)valuation with Open(GL) (Base)
* 
* \b vgeGLBase is open source (LGPL).
*/

#include <vgBase/Type.hpp>


/**
* @defgroup g_glsl Shading language
*
* Uniforms :
* - vec4	random
* - int	time
* - vec2	nearFar
* - vec4	viewport with accessors VIEWPORT_WIDTH and VIEWPORT_HEIGHT
*/

#if !defined(DONT_INCLUDE_GL_HEADERS_IN_VGEGL)
	// See glo/glo.hpp
	#if defined(__OPENGLES2__) || defined(__EMSCRIPTEN__)
		// emscripten => WebGL 1.0 (i.e. almost OpenGLES2.0)
		#include <GLES2/gl2.h>
		#include <GLES2/gl2ext.h>
	#else
		// Desktop OpenGL (3.x and 4.x)
		#include <gle/gl.h>
	#endif
#endif


#ifdef _WIN32

	#ifdef VGEGLBASE_EXPORTS
	#define VGEGLBASE_API	__declspec(dllexport)
	#else
	#define VGEGLBASE_API	__declspec(dllimport)
	#endif

	#define VGEGLBASE_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGEGLBASE_EXPORTS
	#define VGEGLBASE_API __attribute__ ((visibility("default")))
	#define VGEGLBASE_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGEGLBASE_API __attribute__ ((visibility("hidden")))
	#define VGEGLBASE_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGEGLBASE_API
	#define VGEGLBASE_CLASS_API

#endif


//#endif //#ifndef _VGEGLBASE_VGEGLBASE_HPP
