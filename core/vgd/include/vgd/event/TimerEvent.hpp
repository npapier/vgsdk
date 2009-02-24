// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_TIMEREVENT_HPP
#define _VGD_EVENT_TIMEREVENT_HPP

#include "vgd/event/Event.hpp"


namespace vgd
{

namespace event
{



/**
 * @brief	Implements a timer event class.
 */
struct VGD_API TimerEvent : public Event
{

	/**
	 * @brief	Constructor
	 * 
	 * @param	source		a pointer to the source fo the event
	 * @param	buttonStates	a reference to the button state set
	 */
	TimerEvent( Source *source, const ButtonStateSet& buttonStates );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~TimerEvent();

	/**
	 * @name Overridden methods
	 */
	//@{
	void accept( vgd::event::EventVisitor& eventVisitor );
	//@}
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_TIMEREVENT_HPP