// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifdef _MSC_VER

	// The Visual C++ debugger doesn't know string larger than 255 char. STL often creates large
	// symbol. The following line cancels warning created by Visual.
	#pragma warning (disable : 4786)

	// need a dll interface (Un classe de base ou une structure doit �tre d�clar�e avec 
	// le mot cl� __declspec(dllexport) pour qu'une fonction d'une classe d�riv�e soit export�e)
	#pragma warning (disable:4251)
	
	// The following line prevents from this file to be included several times by the compiler with
	// Visual C++. This makes compiling quicker, but must not be used when your file content may
	// change depending on some macro definitions. In the general case, leave these lines as they are.
	#pragma once

#endif

#include <cassert>
#include <typeinfo>

// FIXME: TODO test if sizeof( followin types) must == 1 2 4...
#ifdef __STDC__
	typedef signed char		int8;
#else
	typedef char				int8;
#endif
typedef unsigned char		uint8;

typedef short					int16;
typedef unsigned short		uint16;

typedef int						int32;
typedef unsigned int			uint32;
