// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_MYBASE_HPP
#define _VGTEST_MYBASE_HPP

#include <gtkmm.h>
#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>

#include <vgTest/Base.hpp>

#include "vgTest/convenience.hpp"
#include <list>

namespace vgTest
{
	struct myCanvas;
}

namespace vgTest
{

	struct myBase : public Base
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
	myBase(std::string filename, vgTest::testType t);

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
	void								addObject(std::string filename);

	/**
	 * @brief Add a shape to the scene
	 * 
	 * @param the VertexShape
	 */
	void								addObject(vgd::Shp<vgd::node::VertexShape> shape);

	/**
	 * @brief Add a list of shape to the scene
	 * 
	 * @param the VertexShape
	 */
	void								addObject(std::list<vgd::Shp<vgd::node::VertexShape>> shapeList);

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

	/**
	* @brief Get the path of the reference image
	*/
	std::string							getReferencePath();

	/**
	* @brief Get the path of the screenshot
	*/
	std::string							getScreenShotPath();

	/**
	* @brief Get the path of the difference
	*/
	std::string							getDifferencePath();

	/**
	* @brief Get the images path for xml attribute
	*/
	std::string							getImagesPath(bool diff);

private:
	
	void								prerun();
	/**
	 * @brief Prerun the Gtk application : create canvas and window
	 * @param true to take screenshot in the paint function
	 */
	void								prerun(vgTest::testType t);


	Gtk::Window							*m_window;
	myCanvas							*m_canvas;
	int									m_frame;
	int									m_duration;
	int									m_fps;
	std::string							m_filename;
	std::string							m_datedFilename;
	bool								m_run;
};

} // namespace vgTest

#endif // #ifndef _VGTEST_MYBASE_HPP
