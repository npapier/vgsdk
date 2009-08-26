// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/myBase.hpp"

#include <vgGTK/event/sdl.hpp>
#include <vgGTK/Logging.hpp>
#include <sbf/path.hpp>
#include <sbf/Module.hpp>

#include "vgTest/myCanvas.hpp"

namespace vgTest
{

myBase::myBase()
:	m_window( 0 ), 
	m_frame ( 0 ),
	m_duration ( 0 ),
	m_fps ( 0 ),
	m_filename ( "test" ),
	m_run ( false )
{
	prerun();
}

myBase::myBase(std::string filename, vgTest::testType t)
:	m_window( 0 ), 
	m_frame ( 0 ),
	m_duration ( 0 ),
	m_fps ( 0 ),
	m_run ( false )
{
	m_filename = filename;
	m_datedFilename = vgTest::getDatedImageName(m_filename);
	prerun(t);
}

myBase::~myBase()
{
	delete m_canvas;
	delete m_window;
}

void myBase::prerun()
{
	prerun(vgTest::NOTHING);
}

void myBase::prerun(vgTest::testType t)
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

vgTest::myCanvas* myBase::getCanvas()
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

std::string myBase::getReferencePath()
{
	// @todo Replace the hard coded path
	boost::filesystem::path path = sbf::path::getTopLevel(sbf::path::Var) / "vgUI" / "0-5" / "references" /  m_filename;
	return path.string();
}

std::string myBase::getScreenShotPath()
{
	// @todo Replace the hard coded path

	boost::filesystem::path path = sbf::path::getTopLevel(sbf::path::Var) / "vgUI" / "0-5" / "screenshots" /  m_datedFilename;
	return path.string();
}

std::string myBase::getDifferencePath()
{
	// @todo Replace the hard coded path
	boost::filesystem::path path = sbf::path::getTopLevel(sbf::path::Var) / "vgUI" / "0-5" / "differences" /  m_datedFilename;
	return path.string();	
}

std::string myBase::getImagesPath(bool diff)
{
	// @todo Replace the hard coded path
	std::string imagePath = "references="+getReferencePath();
	imagePath += "|screenshots="+getScreenShotPath();

	if (diff)
	{
		imagePath += "|differences="+getDifferencePath();
	}
	return imagePath;	
}

} // namespace vgTest
