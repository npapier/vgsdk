// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGD_EVENT_HATEVENT_HPP_
#define _VGD_EVENT_HATEVENT_HPP_

#include "vgd/event/Event.hpp"



namespace vgd
{

namespace event
{



/**
 * @brief	Implements an event notifiying changes about a directionnal hat on a device (like a joystick).
 */
struct VGD_API HatEvent : public Event
{
	/**
	 * @brief	Defines possible hat states.
	 */
	typedef enum
	{
		CENTERED	= 0,
		UP			= 1 << 0,
		RIGHT		= 1 << 1,
		DOWN		= 1 << 2,
		LEFT		= 1 << 3,
		UP_RIGHT	= UP|RIGHT,
		DOWN_RIGHT	= DOWN|RIGHT,
		DOWN_LEFT	= DOWN|LEFT,
		UP_LEFT		= UP|LEFT
	} State;


	/**
	 * @brief	Constructor
	 *
	 * @param	source		a pointer to a device that emitted the event
	 * @param	buttonStates	the state of the buttons at the time the event has been generated
	 * @param	index			the hat's index
	 * @param	state			the hat's state
	 */
	HatEvent( Source * source, const ButtonStateSet & buttonStates, const int index, const State state );


	/**
	 * @name	Accessors
	 */
	//@{
	/**
	 * @brief	Retrieves the index of the hat.
	 *
	 * @return	the hat's index
	 */
	const int getIndex() const;

	/**
	 * @brief	Retrieves the state of the hat.
	 *
	 * @return	the hat's state
	 */
	const State getState() const;
	//@}


	/**
	 * @name	Overrides
	 */
	//@{
	void accept( vgd::event::EventVisitor & eventVisitor );
	//@}

private:

	const int	m_index;	///< The index of the hat
	const State	m_state;	///< The state of the hat
};



} // namespace event

} // namespace vgd



#endif /*_VGD_EVENT_HATEVENT_HPP_*/
