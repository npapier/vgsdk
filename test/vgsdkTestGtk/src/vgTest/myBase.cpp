// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/myBase.hpp"

#include <vgGTK/event/sdl.hpp>
#include <vgGTK/Logging.hpp>
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

	myBase::myBase(std::string filename, vgsdkTestGtk::vgTest::testType t)
	:	m_window( 0 ), 
		m_frame ( 0 ),
		m_duration ( 0 ),
		m_fps ( 0 ),
		m_run ( false ),
		Base(filename)
	{
		prerun(t);
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

	void myBase::prerun(vgsdkTestGtk::vgTest::testType t)
	{
		m_canvas = new myCanvas;

		m_canvas->setBase(this);
		m_canvas->setType(t);
		m_canvas->setScreenShotName(m_datedFilename);

		// Creates the main window content.
		m_window = new Gtk::Window;
		m_window->set_default_size( 1024, 768 );
		m_window->set_reallocate_redraws( true );

		m_window->add( *m_canvas );
		m_window->show_all();

		Glib::signal_timeout().connect( sigc::mem_fun(*this, &myBase::quit), 500 );
	}

	void myBase::run()
	{
		m_run = true;
		Gtk::Main::run(*m_window);
	}

	void myBase::addObject(std::string filename)
	{
		m_canvas->appendToScene(filename );
	}

	void myBase::addObject(vgd::Shp<vgd::node::VertexShape> shape)
	{
		m_canvas->getScene()->addChild(shape);
	}

	void myBase::addObject(std::list<vgd::Shp<vgd::node::VertexShape>> shapeList)
	{
		for (std::list<vgd::Shp<vgd::node::VertexShape>>::iterator it = shapeList.begin(); it != shapeList.end(); it++)
		{
			m_canvas->getScene()->addChild(*it);
		}
	}

	bool myBase::quit()
	{
		if(m_quit == true)
		{
			m_window->hide();
			
			if( m_run == true )
			{
				Gtk::Main::quit();
			}
			return false;
		}
		return true;
	}

	vgsdkTestGtk::vgTest::myCanvas* myBase::getCanvas()
	{
		return m_canvas;
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
