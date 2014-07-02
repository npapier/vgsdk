// VGSDK - Copyright (C) 2014, Yakhouba Keita.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Yakhouba Keita

#ifndef _PYTHON_LOADER_HPP
#define _PYTHON_LOADER_HPP

#include <iostream>
#include <string>

namespace vgsdkViewerQt
{

	struct PythonLoader
	{
		/**
		 *@brief use this function to read and execute a python file content in vgsdkViewerQt
		 */
		void load(const std::string & filePath);
	};
}

#endif
