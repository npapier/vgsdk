// VGSDK - Copyright (C) 2004, 2006 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKVIEWER_APP_HPP
#define _VGSDKVIEWER_APP_HPP

#include <wx/app.h>



namespace vgsdkViewer
{



/**
 * @brief The application class.
 */
class App : public wxApp
{
	DECLARE_EVENT_TABLE();

public:

	bool OnInit();
};



} // namespace vgsdkViewer

#endif // #ifndef _VGSDKVIEWER_APP_HPP
