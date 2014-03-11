// VGSDK - Copyright (C) 2009, 2013, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/myBase.hpp"

#include <vgGTK/Logging.hpp>
#include <vgGTK/Notebook.hpp>

#include "vgsdkTestGtk/vgTest/myCanvas.hpp"



namespace vgsdkTestGtk
{

namespace vgTest
{


myBase::myBase()
:	m_window( 0 ), 
	m_frame ( 0 ),
	m_duration ( 0 ),
	m_fps ( 0 ),
	m_run ( false )
{
	prerun();
}


myBase::myBase(const std::string filename, const vgsdkTestGtk::vgTest::testType type)
:	Base(filename),
	m_window( 0 ), 
	m_frame ( 0 ),
	m_duration ( 0 ),
	m_fps ( 0 ),
	m_run ( false )
{
	prerun(type);
}


myBase::~myBase()
{
	delete m_canvas;
	delete m_window;
}


void myBase::prerun()
{
	prerun(vgsdkTestGtk::vgTest::NOTHING);
}


void myBase::prerun(const vgsdkTestGtk::vgTest::testType type)
{
	// Creates the main window content.
	Gtk::HPaned					*hpaned		= Gtk::manage( new Gtk::HPaned );

	Gtk::VBox					*vbox1		= Gtk::manage( new Gtk::VBox );

	vgGTK::Notebook				*notebook	= Gtk::manage( new vgGTK::Notebook );
	m_canvas								= Gtk::manage( new myCanvas );

	// Configures the main window.
	m_window = new Gtk::Window;
	m_window->set_title("vgsdkTest (Gtk version)");
	m_window->set_default_size( 1024, 768 );
	m_window->set_reallocate_redraws( true );

	//
	hpaned->pack1( *vbox1, true, true );
	hpaned->pack2( *m_canvas, true, true );

	//
#ifndef _VGSDK_DONT_KILL_VIEWER_AUTOMATICALLY
	vbox1->pack_start( *notebook, true, true );
#endif

	notebook->set_border_width( 2 );
	notebook->set_size_request( 384 /*333*/, 512/*768*/ ); // @todo should be able to resize detached notebook 
	notebook->setCanvas( *m_canvas ); // Gives the canvas' root node to the notebook.

	// Canvas
	m_canvas->setBase(this);
	m_canvas->setType(type);

	// Creates the main window content.
	m_window->add( *hpaned );

	m_window->show_all_children();

	// define _VGSDK_DONT_KILL_VIEWER_AUTOMATICALLY in default.options to disable quit
#ifndef _VGSDK_DONT_KILL_VIEWER_AUTOMATICALLY
	Glib::signal_timeout().connect( sigc::mem_fun(*this, &myBase::quit), 500 );
#endif
}


void myBase::run()
{
	m_run = true;
	Gtk::Main::run(*m_window);
}


bool myBase::quit()
{
	if ( m_quit )
	{
		m_window->hide();

		if( m_run )
		{
			Gtk::Main::quit();

			// Finalized test
			if ( !getCreateReference() )
			{
				// do the test
				/*base->*/compareScreenShots();
			}
		}
		return false;
	}
	return true;
}


void myBase::addObject(const std::string filename)
{
	m_canvas->appendToScene( filename );
}

void myBase::addObject( const vgd::Shp<vgd::node::Node > node )
{
	m_canvas->getScene()->addChild(node);
}


void myBase::addObject( const std::list< vgd::Shp<vgd::node::Node> > nodeList )
{
	for (std::list<vgd::Shp<vgd::node::Node>>::const_iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		m_canvas->getScene()->addChild(*it);
	}
}


vgd::Shp< vgd::node::Group > myBase::getSetup()
{
	return m_canvas->getSetup();
}


vgd::Shp< vgd::node::Group > myBase::getScene()
{
	return m_canvas->getScene();
}


} // namespace vgTest

} //namespace vgsdkTestGtk
