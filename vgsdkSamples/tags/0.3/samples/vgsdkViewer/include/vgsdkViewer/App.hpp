// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKVIEWER_APP_H
#define _VGSDKVIEWER_APP_H

#include <wx/defs.h>
#include <wx/glcanvas.h>



namespace vgsdkViewer
{



/**
 * @brief The application class.
 */
class App : public wxGLApp
{
	DECLARE_EVENT_TABLE();

public:

	bool OnInit();
};



} // namespace vgsdkViewer

#endif // #ifndef _VGSDKVIEWER_APP_H
