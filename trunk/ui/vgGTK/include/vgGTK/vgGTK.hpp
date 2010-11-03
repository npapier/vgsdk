// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_VGGTK_HPP
#define _VGGTK_VGGTK_HPP

/**
 * @namespace vgGTK
 *
 * @brief	GTK-based specialization of vgUI and user interface building blocks.
 */

#include <vgBase/Type.hpp>



#ifdef _WIN32

// GTKMM_BEGIN_CLASS()
// struct myGtkClass : public Gtk::VBox {};
// GTKMM_END_CLASS()
#define GTKMM_BEGIN_CLASS()	__pragma( warning(push) ) \
							__pragma( warning(disable:4939) ) \
							__pragma( vtordisp(on) )

#define GTKMM_END_CLASS()	__pragma( vtordisp(off) ) \
							__pragma( warning(pop) )

// boost::format() segv with /vd2 compiler option needed by gtkmm (i.e. uses=['gtkmmext'])
// GTKMM_BEGIN_DISABLED()
// boost::format() no more segv inside GTKMM_BEGIN_DISABLED() and GTKMM_END_DISABLED()
// GTKMM_END_DISABLED()
#define GTKMM_BEGIN_DISABLED()	__pragma( warning(push) ) \
								__pragma( warning(disable:4939) ) \
								__pragma( vtordisp(off) )

#define GTKMM_END_DISABLED()	__pragma( vtordisp(on) ) \
								__pragma( warning(pop) )


	#ifdef VGGTK_EXPORTS
	#define VGGTK_API	__declspec(dllexport)
	#else
	#define VGGTK_API	__declspec(dllimport)
	#endif

	#define VGGTK_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGGTK_EXPORTS
	#define VGGTK_API __attribute__ ((visibility("default")))
	#define VGGTK_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGGTK_API __attribute__ ((visibility("hidden")))
	#define VGGTK_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGGTK_API
	#define VGGTK_CLASS_API

#endif



#endif // #ifndef _VGGTK_VGGTK_HPP
