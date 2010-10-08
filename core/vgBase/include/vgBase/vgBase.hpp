// VGSDK - Copyright (C) 2004, 2006 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGBASE_VGBASE_HPP
#define _VGBASE_VGBASE_HPP

/** 
 * @namespace vgBase
 * 
 * @brief (V)ersatile (G)raphical (B)ase
 *
 * \b vgBase is open source (LGPL).
 */

#ifdef WIN32

	#ifdef _MSC_VER
	
		// The Visual C++ debugger doesn't know string larger than 255 char. STL often creates large
		// symbol. The following line cancels warning created by Visual.
		#pragma warning (disable:4786)
	
		// need a dll interface (Un classe de base ou une structure doit être déclarée avec 
		// le mot clé __declspec(dllexport) pour qu'une fonction d'une classe dérivée soit exportée)
		#pragma warning (disable:4251)
		
		// interface non-dll classkey 'identificateur' utilisée comme base d'une interface dll classkey 'identificateur'
		// Une classe exportée a été dérivée depuis une classe qui n'a pas été exportée.
		#pragma warning (disable:4275)
	
		// Spécification d'exception C++ ignorée sauf pour indiquer qu'une fonction n'est pas 
		// __declspec(nothrow)
		#pragma warning (disable:4290)
	
		// The following line prevents from this file to be included several times by the compiler with
		// Visual C++. This makes compiling quicker, but must not be used when your file content may
		// change depending on some macro definitions. In the general case, leave these lines as they are.
		#pragma once

	#endif

	#if defined(VGBASE_STATIC)
		#define VGBASE_API
	#elif defined(VGBASE_SHARED) || defined(VGBASE_EXPORTS)
		#define VGBASE_API __declspec(dllexport)
	#else
		#define VGBASE_API __declspec(dllimport)
	#endif

	#define VGBASE_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGBASE_EXPORTS
	#define VGBASE_API __attribute__ ((visibility("default")))
	#define VGBASE_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGBASE_API __attribute__ ((visibility("hidden")))
	#define VGBASE_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGBASE_API
	#define VGBASE_CLASS_API

#endif

namespace vgBase
{

/**
 * @brief This function do nothing and is only here to have one symbol exported (needed for Visual C++ dll).
 */
VGBASE_API void vgBase();
}

#endif // #ifndef _VGBASE_VGBASE_HPP
