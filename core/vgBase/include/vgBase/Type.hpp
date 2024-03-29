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
	
		// need a dll interface (Un classe de base ou une structure doit �tre d�clar�e avec 
		// le mot cl� __declspec(dllexport) pour qu'une fonction d'une classe d�riv�e soit export�e)
		#pragma warning (disable:4251)
		
		// interface non-dll classkey 'identificateur' utilis�e comme base d'une interface dll classkey 'identificateur'
		// Une classe export�e a �t� d�riv�e depuis une classe qui n'a pas �t� export�e.
		#pragma warning (disable:4275)
	
		// Sp�cification d'exception C++ ignor�e sauf pour indiquer qu'une fonction n'est pas 
		// __declspec(nothrow)
		#pragma warning (disable:4290)
	
		// The following line prevents from this file to be included several times by the compiler with
		// Visual C++. This makes compiling quicker, but must not be used when your file content may
		// change depending on some macro definitions. In the general case, leave these lines as they are.
		#pragma once
	
	#endif

#include <boost/cstdint.hpp>
#include <cassert>
#include <typeinfo>

/**
 * @brief Macro to issue warning when using deprecated functions
 *
 * @remarks Only for gcc and MS/VisualCPP
 */
#if defined(_WIN32) && (_MSC_VER>= 1300)
	#define vgDEPRECATED(x) __declspec(deprecated) x
#else
/// @todo Checks gcc usage and version (>3.1)
/// #define vgDEPRECATED(x) x if not supported
	#define vgDEPRECATED(x) x __attribute__ ((deprecated))
#endif

// @todo FIXME static assertion on sizeof( following types) must == 1 2 4...
#ifdef __STDC__
	typedef signed char		int8;
#else
	typedef char			int8;
#endif
typedef unsigned char		uint8;

typedef boost::int16_t		int16;
typedef boost::uint16_t		uint16;

typedef boost::int32_t		int32;
typedef boost::uint32_t		uint32;

typedef boost::int64_t		int64;
typedef boost::uint64_t		uint64;

//typedef int				int;
typedef unsigned int		uint;

#endif // #ifdef _VGBASE_TYPE_HPP
