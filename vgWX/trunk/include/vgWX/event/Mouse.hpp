// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGWX_EVENT_MOUSE_HPP
#define _VGWX_EVENT_MOUSE_HPP

#include <vgd/event/Mouse.hpp>
#include <vgm/Vector.hpp>
#include <wx/event.h>

#include "vgWX/vgWX.hpp"



namespace vgWX
{
	
namespace event
{
	

/**
 * @brief	Implements a mouse device that attach to a window to retrieve
 * 			mouse events.
 * 
 * This class is an event handler that can be pushed to any window's event
 * handler queue. Each window must have its own instance of this class, otherwise values returned by 
 * Location2Event::getDelta() would be wrong.
 */
struct VGWX_API Mouse : public wxEvtHandler, public vgd::event::Mouse
{
	/**
	 * @brief	Constructor.
	 */
	Mouse();
	
protected:

	DECLARE_EVENT_TABLE()
	
	/**
	 * @brief	Handles a left mouse button double click event.
	 * 
	 * @param	event	the event to process
	 */
	void onLeftDoubleClick( wxMouseEvent& event );
	
	/**
	 * @brief	Handles a left mouse button down event.
	 * 
	 * @param	event	the event to process
	 */
	void onLeftDown( wxMouseEvent& event );
	 
	/**
	 * @brief	Handles a left mouse button up event.
	 * 
	 * @param	event	the event to process
	 */
	void onLeftUp( wxMouseEvent& event );

	/**
	 * @brief	Handles a middle mouse button double click event.
	 * 
	 * @param	event	the event to process
	 */
	void onMiddleDoubleClick( wxMouseEvent& event );

	/**
	 * @brief	Handles a middle mouse button down event.
	 * 
	 * @param	event	the event to process
	 */
	void onMiddleDown( wxMouseEvent& event );
	 
	/**
	 * @brief	Handles a middle mouse button up event.
	 * 
	 * @param	event	the event to process
	 */
	void onMiddleUp( wxMouseEvent& event );

	/**
	 * @brief	Handles a right mouse button double click event.
	 * 
	 * @param	event	the event to process
	 */
	void onRightDoubleClick( wxMouseEvent& event );
	
	/**
	 * @brief	Handles a right mouse button down event.
	 * 
	 * @param	event	the event to process
	 */
	void onRightDown( wxMouseEvent& event );
	 
	/**
	 * @brief	Handles a right mouse button up event.
	 * 
	 * @param	event	the event to process
	 */
	void onRightUp( wxMouseEvent& event );
	
	/**
	 * @brief	Handles a mouse move event.
	 * 
	 * @param	event	the event to process
	 */
	void onMotion( wxMouseEvent& event );
	
	/**
	 * @brief	Handles a mouse wheel event.
	 * 
	 * @param	event	the event to process
	 */
	void onWheel( wxMouseEvent& event );


private:

	/**
	 * @brief Previous mouse position used to compute delta between two mouse positions.
	 */
	vgm::Vec2f		m_previousMousePosition;
};


} // namespace event

} // namespace vgWX

#endif // _VGWX_EVENT_MOUSE_HPP
