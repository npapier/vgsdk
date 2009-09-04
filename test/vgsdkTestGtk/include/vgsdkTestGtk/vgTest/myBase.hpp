// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_MYBASE_HPP
#define _VGSDKTESTGTK_VGTEST_MYBASE_HPP

#include <gtkmm.h>
#include <list>

#include <vgd/node/Group.hpp>
#include <vgd/Shp.hpp>
#include <vgTest/Base.hpp>

#include "vgsdkTestGtk/vgTest/convenience.hpp"


namespace vgsdkTestGtk
{

namespace vgTest
{

	struct myCanvas;
	
	struct myBase : public ::vgTest::Base
{
	/**
	 * @brief Default constructor
	 */
	myBase();

	/**
	 * @brief Constructor which define if the paint function take a screenshot or not
	 *
	 * @param screenShot true take screeshot
	 * @param name the screenshot name
	 */
	myBase(const std::string filename, const vgsdkTestGtk::vgTest::testType t);

	virtual ~myBase();

	/**
	 * @brief Run the Gtk main loop
	 */
	void								run();

	/**
	 * @brief Add an object to the scene
	 * 
	 * @param the object file name
	 */
	void								addObject(const std::string filename);

	/**
	 * @brief Add a shape to the scene
	 * 
	 * @param the VertexShape
	 */
	void								addObject(const vgd::Shp<vgd::node::VertexShape> shape);

	/**
	 * @brief Add a list of shape to the scene
	 * 
	 * @param the VertexShape
	 */
	void								addObject(const std::list<vgd::Shp<vgd::node::VertexShape>> shapeList);

	/**
	 * @brief Quit the Gtk main loop and destroy the canvas and window
	 */
	bool								quit();

	/**
	 * @brief Return the current canvas
	 */
	myCanvas							*getCanvas();

	/**
	 * @brief Return the setup from canvas
	 */
	vgd::Shp< vgd::node::Group >		getSetup();

	/**
	 * @brief Return the scene from canvas
	 */
	vgd::Shp< vgd::node::Group >		getScene();



private:
	
	void								prerun();
	/**
	 * @brief Prerun the Gtk application : create canvas and window
	 * @param true to take screenshot in the paint function
	 */
	void								prerun(const vgsdkTestGtk::vgTest::testType t);


	Gtk::Window							*m_window;
	myCanvas							*m_canvas;
	int									m_frame;
	int									m_duration;
	int									m_fps;
	bool								m_run;
};

} // namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_MYBASE_HPP

