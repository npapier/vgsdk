// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_MOUSEBUTTONEVENT_H
#define _VGD_EVENT_MOUSEBUTTONEVENT_H


#include "vgd/vgd.hpp"
#include "vgd/event/ButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
/**
 * @brief	Implements a keyboard button event class.
 */
struct VGD_API MouseButtonEvent : public ButtonEvent
{
	/**
	 * @brief	Defines all possible button on a mouse.
	 */
	enum Button { BUTTON_1, BUTTON_2, BUTTON_3	};
	
	/**
	 * @brief	Constructor
	 * 
	 * @param	source	a pointer to the source fo the event
	 * @param	state	a button state
	 * @param	button	a mouse button
	 */
	MouseButtonEvent( Source *source, State state, Button button );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~MouseButtonEvent();
	
	/**
	 * @brief	Retrieves the mouse button.
	 * 
	 * @return	a mouse button
	 */
	Button getButton() const;
	
private:
	/**
	 * @brief	a mouse button
	 */
	Button button;
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_MOUSEBUTTONEVENT_H
