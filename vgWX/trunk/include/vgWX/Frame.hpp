// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_FRAME_H
#define _VGWX_FRAME_H

#include <wx/defs.h>
#include <wx/frame.h>

#include "vgWX/vgWX.hpp"



namespace vgWX
{



/**
 * @brief The vgWX specialized frame window class.
 *
 * @todo doc.
 * 
 * ...This class will create a child GL canvas window occuping the whole client area...
 */
struct VGWX_API Frame : public wxFrame
{
private:
	DECLARE_EVENT_TABLE();

public:

	/**
	 * Default constructor.
	 */
	Frame(	wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, 
				const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = _T("vgWX::Frame"));
};



} //namespace vgWX

#endif // #ifndef _VGWX_FRAME_H
