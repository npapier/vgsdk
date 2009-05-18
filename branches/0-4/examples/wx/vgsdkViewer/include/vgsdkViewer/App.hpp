// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKVIEWER_APP_HPP
#define _VGSDKVIEWER_APP_HPP

#include <wx/app.h>



namespace vgsdkViewer
{

class myCanvas;

/**
 * @brief The application class.
 */
class App : public wxApp
{
	vgsdkViewer::myCanvas *m_myCanvas; ///< a reference on my canvas

	void fileOpen( const bool clearScene );

	vgsdkViewer::myCanvas *getCurrentCanvas();

//	DECLARE_EVENT_TABLE();

public:

	enum {
		wxID_FILE_ADD = wxID_HIGHEST + 2048,		///@todo Not very dynamic !
		wxID_FILE_RELOAD,
	};

	bool OnInit();

	void OnInitCmdLine( wxCmdLineParser& /*parser*/ );
	bool OnCmdLineParsed( wxCmdLineParser& /*parser*/ );


	void OnFileNew( wxCommandEvent& /*event*/ );
	void OnFileOpen( wxCommandEvent& /*event*/ );
	void OnFileAdd( wxCommandEvent& /*event*/ );
	void OnFileReload( wxCommandEvent& /*event*/ );
	void OnFileExit( wxCommandEvent& /*event*/ );

	void OnHelpAbout( wxCommandEvent& /*event*/ );



	wxFrame *getFrame() const;
};



} // namespace vgsdkViewer

#endif // #ifndef _VGSDKVIEWER_APP_HPP
