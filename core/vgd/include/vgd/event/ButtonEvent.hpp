// VGSDK - Copyright (C) 2004-2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_BUTTONEVENT_HPP
#define _VGD_EVENT_BUTTONEVENT_HPP

#include "vgd/event/Event.hpp"
#include "vgd/event/EventVisitor.hpp"



namespace vgd
{

namespace event
{

struct ButtonSet;

/**
 * @brief	Implements a button event class.
 *
 * @remarks When writting derived classes, be careful with the button identifier that must be unique.
 */
struct VGD_API ButtonEvent : public Event
{
	/**
	 * @brief	Defines all possible states for a button.
	 */
	enum State { DOWN, UP, DCLICK };

	/**
	 * @brief	Constructor
	 *
	 * @param	source		a pointer to the source of the event
	 * @param	buttonStates	a reference to the button state set
	 * @param	buttonID		a button identifier
	 * @param	state			a button state
	 */
	ButtonEvent( Source *source, const ButtonStateSet& buttonStates, const int32 buttonID, const State state );

	/**
	 * @brief	Destructor
	 */
	virtual ~ButtonEvent();

	/**
	 * @brief	Retrieves the identifier of the related button.
	 *
	 * @return	a button identifier
	 */
	const int32 getButtonID() const;

	/**
	 * @brief	Retrieves the state of the related button.
	 *
	 * @return	a button state
	 */
	const State getState() const;


private:

	int32	m_buttonID;	///< The identifier of the related button.
	State	m_state;	///< The state of the related button.
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_BUTTONEVENT_HPP

