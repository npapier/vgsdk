// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _BASICVIEWER_MYCANVAS_H
#define _BASICVIEWER_MYCANVAS_H

#include <vgWX/BasicManipulator.hpp>



namespace basicViewer
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
					const wxString& name = _T("BasicVGSDK"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );
					
	void initialize();
};



} // namespace basicViewer

#endif // #ifndef _BASICVIEWER_MYCANVAS_H
