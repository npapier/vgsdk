// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKVIEWER_MYCANVAS_HPP
#define _VGSDKVIEWER_MYCANVAS_HPP

#include <wx/arrstr.h>
#include <wx/defs.h>

#include <vgWX/BasicManipulator.hpp>



namespace vgsdkViewer
{



class myCanvas : public vgWX::BasicManipulator
{
	DECLARE_EVENT_TABLE();

public:

	/**
	 * @brief Constructor
	 *
	 * @param	parent		a pointer to the parent window
	 */
	myCanvas(
					wxWindow *parent,
					const wxString& name = _T("myCanvas"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );

	/**
	 * @brief Constructor
	 *
	 * @param	parent		a pointer to the parent window
	 */					
	myCanvas(		wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name = _T("myCanvas"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );					



	/**
	 * @name Overrided methods
	 */
	//@{
						
	void initialize();

	/**
	 * @todo Use wxAcceleratorTable
	 */
	void OnChar( wxKeyEvent& event );
	
	//@}



	/**
	 * @name Scene management methods
	 */
	//@{

	void		clearScene();

	const bool	appendToScene( const wxString& pathfilename, const bool mustCallViewAll = true  );
	const bool	appendToScene( wxArrayString pathfilenames, const bool mustCallViewAll = true );
	const bool	reloadScene();

	//@}



private:
	/**
	 * @name Loading methods
	 */
	//@{
	
	const bool load( std::string pathfilename );

	const bool loadTrian( std::string pathfilename );
	const bool loadTrian2( std::string pathfilename );
	const bool loadCollada( std::string pathfilename );

	//@}

	/**
	 * @brief Files currently loaded
	 */
	wxArrayString m_filenames;
	
	// Forward type declaration
	class DnDFile;
};



} // namespace vgsdkViewer

#endif // #ifndef _VGSDKVIEWER_MYCANVAS_HPP
