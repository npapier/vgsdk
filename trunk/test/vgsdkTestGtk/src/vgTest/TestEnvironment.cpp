// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/TestEnvironment.hpp"

#include <vgDebug/convenience.hpp>
#include <vgGTK/event/sdl.hpp>
#include <vgGTK/Logging.hpp>
#include <gtkmm.h>

namespace vgsdkTestGtk
{
	namespace vgTest
	{

	TestEnvironment::TestEnvironment( int argc, char **argv )
	:	m_kit ( 0 ),
		m_argc( argc ),
		m_argv( argv )
	{}

		TestEnvironment::~TestEnvironment()
		{
			//assert(false); // @todo really called ?
		}
		
		void TestEnvironment::SetUp()
		{
			// Glib thread system initialization.
			Glib::thread_init();

			// Initializes the gtk system.
			m_kit = new Gtk::Main( m_argc, m_argv );

			// Installs the GTK-based logging.
			vgDebug::set< vgGTK::Logging >();

			// Another initialization thing.
			vgGTK::event::initSDL();

			// Set the human readable name of the application.
			Glib::set_application_name("vgsdkTestGtk");
		}

		void TestEnvironment::TearDown()
		{
		}

	} // namespace vgTest

} //namespace vgsdkTestGtk
