// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_VGTEST_HPP
#define _VGTEST_VGTEST_HPP

/**
 * @defgroup g_vgTest vgTest - (V)ersatile (G)raphical (T)est framework
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGTEST_EXPORTS
	#define VGTEST_API	__declspec(dllexport)
	#else
	#define VGTEST_API	__declspec(dllimport)
	#endif

	#define VGTEST_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGTEST_EXPORTS
	#define VGTEST_API __attribute__ ((visibility("default")))
	#define VGTEST_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGTEST_API __attribute__ ((visibility("hidden")))
	#define VGTEST_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGTEST_API
	#define VGTEST_CLASS_API

#endif

/** 
 * @namespace vgTest
 * 
 * @brief (V)ersatile (G)raphical (T)est framework
 *
 * vgTest is the shared test library of vgsdk.
 * 
 * \b vgTest is open source (LGPL).
 */

// namespace vgTest
// {

// } // namespace vgTest

#endif // _VGTEST_VGTEST_HPP
