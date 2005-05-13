// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "basicViewer/App.hpp"

#include "basicViewer/Frame.hpp"



IMPLEMENT_APP( basicViewer::App )

namespace basicViewer
{



BEGIN_EVENT_TABLE( App, wxGLApp )
END_EVENT_TABLE()



bool App::OnInit()
{
	Frame*	pFrame = new Frame();

	SetTopWindow( pFrame );

	pFrame->Show( true );

	return true;
}



} // namespace basicViewer
