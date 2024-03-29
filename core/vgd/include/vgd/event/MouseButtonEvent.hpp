// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_MOUSEBUTTONEVENT_HPP
#define _VGD_EVENT_MOUSEBUTTONEVENT_HPP

#include "vgd/event/ButtonEvent.hpp"
#include "vgd/event/Location2.hpp"



namespace vgd
{

namespace event
{

/**
 * @brief	Implements a mouse button event.
 */
struct VGD_API MouseButtonEvent : public Location2, public ButtonEvent
{
	/**
	 * @brief	Defines all possible button on a mouse.
	 */
	enum {
		MOUSE_BUTTON_1 = 512, /*!< First mouse button */
		MOUSE_BUTTON_2,
		MOUSE_BUTTON_3,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5
	};

	/**
	 * @brief	Constructor
	 * 
	 * @param	source		a pointer to the source fo the event
	 * @param	buttonStates	a reference to the button state set
	 * @param	buttonID		a mouse button
	 * @param	state			a button state
	 * @param	location		a location to pass through the event
	 * @param	size			the size of the 'canvas' where Location2event occurs
	 */
	MouseButtonEvent(	Source *source, const ButtonStateSet& buttonStates, const int32 buttonID, const State state,
						const Location& location, const Size& size );

	/**
	 * @brief	Destructor
	 */
	virtual ~MouseButtonEvent();

	/**
	 * @brief	Overrides
	 */
	//@{
	void accept( vgd::event::EventVisitor& eventVisitor );
	//@}
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_MOUSEBUTTONEVENT_HPP
