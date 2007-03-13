// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKVIEWER_MYCANVAS_HPP
#define _VGSDKVIEWER_MYCANVAS_HPP

#include <wx/defs.h>
#include <wx/dnd.h>

#include <vgWX/BasicManipulator.hpp>



namespace vgsdkViewer
{



class myCanvas : public vgWX::BasicManipulator
{
	DECLARE_EVENT_TABLE();

public:

	/**
	 * @brief Constructor.
	 *
	 * @param	pParent		A pointer to the parent window.
	 */
	myCanvas(
					wxWindow *parent,
					const wxString& name = _T("BasicManipulator"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );
					
	myCanvas(
					wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name = _T("BasicManipulator"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );					



	/**
	 * @name Overrided methods.
	 */
	//@{
						
	void initialize();

	void OnChar			( wxKeyEvent& event );
	
	wxMenu *createContextualMenu( const int32 xMouse, const int32 yMouse ) /*const*/;

	//void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );
	//@}






	/**
	 * @name Loading methods.
	 */
	//@{
	bool load( std::string pathfilename );
	
	bool loadTrian( std::string pathfilename );
	bool loadTrian2( std::string pathfilename );
	
	void reload();	
	//@}

	/**
	 * @brief Files loaded.
	 */
	std::vector< std::string >			m_filenames;
};



class DnDFile : public wxFileDropTarget
{
public:
    DnDFile( myCanvas* pOwner );

    virtual bool OnDropFiles(	wxCoord x, wxCoord y,
                             	const wxArrayString& filenames);

private:
    myCanvas *m_pOwner;
};



} // namespace vgsdkViewer

#endif // #ifndef _VGSDKVIEWER_MYCANVAS_HPP
