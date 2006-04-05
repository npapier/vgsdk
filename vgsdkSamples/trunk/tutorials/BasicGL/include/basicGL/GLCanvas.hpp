// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _BASICGL_GLCANVAS_HPP
#define _BASICGL_GLCANVAS_HPP

#include <wx/wx.h>
#include <wx/defs.h>
#include <wx/glcanvas.h>



namespace basicGL
{



class GLCanvas : public wxGLCanvas
{
	DECLARE_EVENT_TABLE();

public:

	/**
	 * @brief Constructor.
	 *
	 * @param	pParent	:	A pointer to the parent window.
	 */
	GLCanvas(	wxWindow *parent, const wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition,
					const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = _T("GLCanvas"),
					int* gl_attrib = NULL);

private:

	/**
	 * @brief Handles \c EVT_PAINT events.
	 */
	void OnPaint( /*const*/ wxPaintEvent& event );

	/**
	 * @brief Handles \c EVT_SIZE events.
	 */
	void OnSize( /*const*/ wxSizeEvent& event );

	/**
	 * @brief Handles	\c EVT_ERASE_BACKGROUND.
	 */
	void OnEraseBackground( /*const*/ wxEraseEvent& event);
};



} // namespace basicGL

#endif // #ifndef _BASICGL_GLCANVAS_HPP
