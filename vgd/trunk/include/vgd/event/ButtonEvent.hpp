// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_BUTTONEVENT_H
#define _VGD_EVENT_BUTTONEVENT_H


#include "vgd/event/Event.hpp"


namespace vgd
{
	
namespace event
{

	
/**
 * @brief	Implements a button event class.
 */
class ButtonEvent : public Event
{
public:
	/**
	 * @brief	Defines all possible states for a button.
	 */
	enum State { UP, DOWN, UNKOWN };
	
	/**
	 * @brief	Constructor
	 * 
	 * @param	source	a pointer to the source fo the event
	 * @param	state	a button state
	 */
	ButtonEvent( Source *source, State state );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~ButtonEvent();
	
	/**
	 * @brief	Retrieves the state of the related button.
	 * 
	 * @return	a button state
	 */
	State getState() const;
	
private:

	/**
	 * @brief	The state of the related button.
	 */
	State state;
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_BUTTONEVENT_H
