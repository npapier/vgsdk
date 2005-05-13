// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _BASICGL_FRAME_H
#define _BASICGL_FRAME_H

#include <wx/defs.h>
#include <wx/frame.h>



namespace basicGL
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



} //namespace basicGL

#endif // #ifndef _BASICGL_FRAME_H
