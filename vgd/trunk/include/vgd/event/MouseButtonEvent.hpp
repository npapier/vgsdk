// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_MOUSEBUTTONEVENT_H
#define _VGD_EVENT_MOUSEBUTTONEVENT_H


#include "vgd/event/ButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
/**
 * @brief	Implements a keyboard button event class.
 */
class MouseButtonEvent : public ButtonEvent
{
public:
	/**
	 * @brief	Constructor
	 * 
	 * @param	source	a pointer to the source fo the event
	 * @param	state	a button state
	 */
	MouseButtonEvent( Source *source, State state );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~MouseButtonEvent();
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_MOUSEBUTTONEVENT_H
