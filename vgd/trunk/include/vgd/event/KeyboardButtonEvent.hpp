// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_KEYBOARDBUTTONEVENT_H
#define _VGD_EVENT_KEYBOARDBUTTONEVENT_H


#include "vgd/vgd.hpp"
#include "vgd/event/ButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
/**
 * @brief	Implements a keyboard button event class.
 */
struct VGD_API KeyboardButtonEvent : public ButtonEvent
{
public:
	/**
	 * @brief	Constructor
	 * 
	 * @param	source	a pointer to the source fo the event
	 * @param	state	a button state
	 */
	KeyboardButtonEvent( Source *source, State state );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~KeyboardButtonEvent();
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_KEYBOARDBUTTONEVENT_H
