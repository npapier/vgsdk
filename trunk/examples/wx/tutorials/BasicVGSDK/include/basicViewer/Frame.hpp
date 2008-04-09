// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _BASICVIEWER_FRAME_HPP
#define _BASICVIEWER_FRAME_HPP

#include <wx/defs.h>
#include <wx/frame.h>



namespace basicViewer
{



/**
 * @brief	The application's frame window class.
 *
 * This class will create a child GL canvas window occuping the whole client area.
 */
class Frame : public wxFrame
{
	DECLARE_EVENT_TABLE();

public:

	/**
	 * Default constructor.
	 */
	Frame();
};



} //namespace basicViewer

#endif // #ifndef _BASICVIEWER_FRAME_HPP
