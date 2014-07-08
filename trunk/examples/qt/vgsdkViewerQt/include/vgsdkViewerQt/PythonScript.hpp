// VGSDK - Copyright (C) 2014, Yakhouba Keita.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Yakhouba Keita

#ifndef _PYTHON_LOADER_HPP
#define _PYTHON_LOADER_HPP

#include <iostream>
#include <string>
#include <Python.h>
#include <boost/filesystem/path.hpp>
#include <vgd/Shp.hpp>


namespace vgd { namespace event { struct TimerCallback; } }



namespace vgsdkViewerQt
{


struct MyCanvas;


struct PythonScript
{
	/**
	 * @brief	Creates a python script loaded from the given filename
	 */
	PythonScript( MyCanvas * canvas, const std::string & filename );

	/**
	 * @brief	Destructor
	 */
	~PythonScript();

	/**
	 * @brief	Calls the python refresh callback
	 */
	void refresh();

private:

	MyCanvas *						m_canvas;		///< Points to the canvas used for rendering.
	const boost::filesystem::path	m_filename;		///< Holds the filename of the script to run.
	PyObject *						m_pyModule;		///< Points to the python module representing the script in the python interpreter.
	vgd::Shp< vgd::event::TimerCallback >	m_refreshCallback;

	const bool import();
	const bool hasFunction( PyObject * module, const std::string & name );
};


}

#endif
