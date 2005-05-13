// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "basicGL/Frame.hpp"

#include <wx/layout.h>

#include "basicGL/GLCanvas.hpp"



namespace basicGL
{



BEGIN_EVENT_TABLE( Frame, wxFrame )
END_EVENT_TABLE()



Frame::Frame()
:	wxFrame( 0, -1, _T("BasicGL") )
{
	// Creation of the child GL canvas.
	basicGL::GLCanvas*				pCanvas		= new basicGL::GLCanvas( this );
	wxLayoutConstraints*	pLayoutConstraints	= new wxLayoutConstraints();

	pLayoutConstraints->left	.SameAs( this, wxLeft	);
	pLayoutConstraints->right	.SameAs( this, wxRight	);
	pLayoutConstraints->top		.SameAs( this, wxTop	);
	pLayoutConstraints->bottom	.SameAs( this, wxBottom );

	pCanvas->SetConstraints( pLayoutConstraints );
	pCanvas->Show( true );
	SetAutoLayout( true );
}



} // namespace basicGL
