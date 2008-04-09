// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _BASICVIEWER_APP_HPP
#define _BASICVIEWER_APP_HPP

#include <wx/defs.h>
#include <wx/app.h>



namespace basicViewer
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



} // namespace basicViewer

#endif // #ifndef _BASICVIEWER_APP_HPP
