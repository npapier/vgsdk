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

	MyCanvas *						m_canvas;
	const boost::filesystem::path	m_filename;
	const std::string				m_moduleName;
	vgd::Shp< vgd::event::TimerCallback >	m_refreshCallback;
	

	PyObject * import();
	const bool hasFunction( PyObject * module, const std::string & name );
};


}

#endif
