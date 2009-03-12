// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_TIMEREVENT_HPP
#define _VGD_EVENT_TIMEREVENT_HPP

#include "vgd/basic/Time.hpp"
#include "vgd/event/Event.hpp"



namespace vgd
{

namespace event
{



/**
 * @brief	Implements a timer event class.
 *
 * @ingroup g_time
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
	 * @brief Returns the time point of the creation of this event
	 */
	const vgd::basic::Time& getTime() const;

	/**
	 * @name Overridden methods
	 */
	//@{
	void accept( vgd::event::EventVisitor& eventVisitor );
	//@}

private:
	vgd::basic::Time m_time;	///<  the time point of the creation of this event
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_TIMEREVENT_HPP
