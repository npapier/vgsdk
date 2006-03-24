// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGWX_EVENT_KEYBOARD_HPP
#define _VGWX_EVENT_KEYBOARD_HPP

#include <vgd/event/Keyboard.hpp>
#include <wx/event.h>

#include "vgWX/vgWX.hpp"



namespace vgWX
{
	
namespace event
{

/**
 * @brief	Defines a wxWidget keyboard keyboard device.
 * 
 * This class is an event handler that can be pushed to any window's event
 * handler queue.
 */
struct VGWX_API Keyboard : public wxEvtHandler, public vgd::event::Keyboard
{
	/**
	 * @brief	Constructor.
	 */
	Keyboard();
	
protected:

	DECLARE_EVENT_TABLE()
	
	/**
	 * @brief	Handles a key down event.
	 * 
	 * @param	event	the event to process
	 */
	void onKeyDown( wxKeyEvent& event );
	
	/**
	 * @brief	Handles a key up event.
	 * 
	 * @param	event	the event to process
	 */
	void onKeyUp( wxKeyEvent& event );
};


} // namespace event

} // namespace vgWX


#endif // _VGWX_EVENT_KEYBOARD_HPP
