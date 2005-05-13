// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgsdkViewer/App.hpp"

#include "vgsdkViewer/myCanvas.hpp"
#include <wx/Frame.h>



IMPLEMENT_APP( vgsdkViewer::App )

namespace vgsdkViewer
{



BEGIN_EVENT_TABLE( App, wxGLApp )
END_EVENT_TABLE()



bool App::OnInit()
{
	wxFrame*	pFrame = new wxFrame( NULL, -1, _T("vgsdkViewer") );
	pFrame->CreateStatusBar();		
	SetTopWindow( pFrame );
		
	// Creation of the child GL canvas.
	vgsdkViewer::myCanvas*	pCanvas					= new vgsdkViewer::myCanvas( pFrame );

	wxLayoutConstraints*		pLayoutConstraints	= new wxLayoutConstraints();
	pLayoutConstraints->left	.SameAs( pFrame, wxLeft	);
	pLayoutConstraints->right	.SameAs( pFrame, wxRight	);
	pLayoutConstraints->top		.SameAs( pFrame, wxTop	);
	pLayoutConstraints->bottom	.SameAs( pFrame, wxBottom );
	pCanvas->SetConstraints( pLayoutConstraints );
	
	//
	pFrame->Show( true );

	return true;
}



} // namespace vgsdkViewer
