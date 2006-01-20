// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/Frame.hpp"

#include <wx/layout.h>

#include "vgWX/BasicManipulator.hpp"



namespace vgWX
{



BEGIN_EVENT_TABLE( Frame, wxFrame )
END_EVENT_TABLE()



Frame::Frame(	wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
					const wxSize& size, long style, const wxString& name ) :
	wxFrame( parent, id, title, pos, size, style, name )
{
	// Creation of the child GL canvas.
	vgWX::BasicManipulator*	pCanvas					= new vgWX::BasicManipulator( this );

	wxLayoutConstraints*		pLayoutConstraints	= new wxLayoutConstraints();

	pLayoutConstraints->left	.SameAs( this, wxLeft	);
	pLayoutConstraints->right	.SameAs( this, wxRight	);
	pLayoutConstraints->top		.SameAs( this, wxTop	);
	pLayoutConstraints->bottom	.SameAs( this, wxBottom );

	pCanvas->SetConstraints( pLayoutConstraints );
	pCanvas->Show( true );
	
	SetAutoLayout( true );
}



} // namespace vgWX
