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
	enum {
		MOUSE_BUTTON_1 = 512, /*!< First mouse button */
		MOUSE_BUTTON_2,
		MOUSE_BUTTON_3
	};

	/**
	 * @brief	Constructor
	 * 
	 * @param	source			a pointer to the source fo the event
	 * @param	buttonStates	a reference to the button state set
	 * @param	buttonID			a mouse button
	 * @param	state				a button state
	 */
	MouseButtonEvent( Source *source, const ButtonStateSet& buttonStates, const int32 buttonID, const State state );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~MouseButtonEvent();

	// overridden method
	void accept( vgd::event::EventVisitor& eventVisitor );
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_MOUSEBUTTONEVENT_H
