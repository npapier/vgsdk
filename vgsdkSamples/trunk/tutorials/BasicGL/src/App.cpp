// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "basicGL/App.hpp"

#include "basicGL/Frame.hpp"



IMPLEMENT_APP( basicGL::App )

namespace basicGL
{



BEGIN_EVENT_TABLE( App, wxGLApp )
END_EVENT_TABLE()



bool App::OnInit()
{
	// Create the frame window.
	Frame*	pFrame = new Frame();

	// Setup the frame to be the main window and show it.
	pFrame->Show( true );
	SetTopWindow( pFrame );

	return true;
}



} // namespace basicGL
