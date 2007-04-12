// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgsdkViewer/App.hpp"

#include <wx/cmdline.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>

#include "vgsdkViewer/myCanvas.hpp"



IMPLEMENT_APP( vgsdkViewer::App )



namespace vgsdkViewer
{



//BEGIN_EVENT_TABLE( App, wxApp )
//END_EVENT_TABLE()



void App::fileOpen( const bool clearScene )
{
	wxFileDialog dialog(	getFrame(), _T("Choose file(s)"), _T(""), _T(""),
	_T("All supported files (*.trian;*.trian2;*.DAE)|*.trian;*.trian2;*.DAE|All .trian files (*.trian)|*.trian|All .trian2 files (*.trian2)|*.trian2|All collada files (*.DAE)|*.DAE"),
							wxOPEN | wxMULTIPLE );

	/// @todo improve wildcard

	int retVal = dialog.ShowModal();
	
	if ( retVal == wxID_OK )
	{
		wxArrayString filenames;
		dialog.GetPaths( filenames );
		
		if ( clearScene )
		{
			getCurrentCanvas()->clearScene();
		}
		getCurrentCanvas()->appendToScene( filenames );
		getCurrentCanvas()->refresh();
	}
}



vgsdkViewer::myCanvas *App::getCurrentCanvas()
{
	return m_myCanvas;
}



bool App::OnInit()
{
	// Makes frame
	wxFrame *frame = new wxFrame( NULL, -1, _T("vgsdkViewer"), wxDefaultPosition, wxSize(800,600) );

	// Creation of the child GL canvas.
	m_myCanvas = new vgsdkViewer::myCanvas( frame );

	// Creates file menu
	wxMenu *fileMenu = new wxMenu;

	fileMenu->Append(wxID_NEW, "&New	CTRL+N", "Creates a new scene" );
	frame->Connect( wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(App::OnFileNew), 0, this );

	fileMenu->Append(wxID_OPEN, "&Open	CTRL+O", "Creates a new scene and adds 3d object(s) in the scene" );
	frame->Connect( wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(App::OnFileOpen), 0, this );

	fileMenu->Append(wxID_FILE_ADD, "&Add	CTRL+A", "Adds 3d object(s) in the scene" );
	frame->Connect( wxID_FILE_ADD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(App::OnFileAdd), 0, this );

	fileMenu->Append(wxID_FILE_RELOAD, "&Reload	F5", "Reloads the scene" );
	frame->Connect( wxID_FILE_RELOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(App::OnFileReload), 0, this );

	fileMenu->Append(wxID_EXIT, "E&xit", "Quit vgsdkViewer" );
	frame->Connect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(App::OnFileExit), 0, this );

	// Creates help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP, "&About", "About");
	frame->Connect( wxID_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(App::OnHelpAbout), 0, this  );

	// Makes a menubar	
	wxMenuBar* menuBar = new wxMenuBar;

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	// Associate the menu bar with the frame
	frame->SetMenuBar(menuBar);

	//
	frame->CreateStatusBar();
	SetTopWindow( frame );

	wxLayoutConstraints*		pLayoutConstraints	= new wxLayoutConstraints();
	pLayoutConstraints->left.SameAs(	frame, wxLeft	);
	pLayoutConstraints->right.SameAs(	frame, wxRight	);
	pLayoutConstraints->top.SameAs(		frame, wxTop	);
	pLayoutConstraints->bottom.SameAs(	frame, wxBottom );
	
	m_myCanvas->SetConstraints( pLayoutConstraints );
	
	//
	frame->Show( true );

	//
	wxApp::OnInit();

	return true;
}



void App::OnInitCmdLine( wxCmdLineParser& parser )
{
	parser.AddParam(	"path and filename of file to load (.trian, .trian2 and .dae)",
						wxCMD_LINE_VAL_STRING,
						wxCMD_LINE_PARAM_OPTIONAL	);
}



bool App::OnCmdLineParsed( wxCmdLineParser& parser )
{
	if ( parser.GetParamCount() == 1 )
	{
		wxString firstParameter = parser.GetParam(0);
	
		if ( !firstParameter.IsNull() )
		{
			getCurrentCanvas()->clearScene();
			getCurrentCanvas()->appendToScene( firstParameter );
			getCurrentCanvas()->refresh();
		}
	}

	return true;
}



void App::OnFileNew( wxCommandEvent& /*event*/ )
{
	getCurrentCanvas()->clearScene();
	getCurrentCanvas()->refresh();
}



void App::OnFileOpen( wxCommandEvent& /*event*/ )
{
	fileOpen( true );
}



void App::OnFileAdd( wxCommandEvent& /*event*/ )
{
	fileOpen( false );
}



void App::OnFileReload( wxCommandEvent& /*event*/ )
{
	getCurrentCanvas()->reloadScene();
}



void App::OnFileExit( wxCommandEvent& /*event*/ )
{
	getFrame()->Close();
}



void App::OnHelpAbout( wxCommandEvent& /*event*/ )
{
	wxMessageBox("vgsdkViewer version 0.4 by Nicolas Papier", "About vgsdkViewer");
}



wxFrame *App::getFrame() const
{
	wxFrame *frame = wxDynamicCast(GetTopWindow(), wxFrame);
	
	return frame;
}



} // namespace vgsdkViewer
