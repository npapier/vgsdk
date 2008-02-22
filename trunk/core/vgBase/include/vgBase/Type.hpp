// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGBASE_TYPE_HPP
#define _VGBASE_TYPE_HPP

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

#include <cassert>
#include <typeinfo>

// @todo FIXME static assertion on sizeof( following types) must == 1 2 4...
#ifdef __STDC__
	typedef signed char		int8;
#else
	typedef char			int8;
#endif
typedef unsigned char		uint8;

typedef short				int16;
typedef unsigned short		uint16;

typedef long				int32;
typedef unsigned long		uint32;

typedef long long			int64;

//typedef int				int;
typedef unsigned int		uint;

#endif // #ifdef _VGBASE_TYPE_HPP
