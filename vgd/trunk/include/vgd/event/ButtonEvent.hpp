// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_BUTTONEVENT_H
#define _VGD_EVENT_BUTTONEVENT_H


#include "vgd/vgd.hpp"
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
	 * @param	source			a pointer to the source of the event
	 * @param	buttonStates	a reference to the button state set
	 * @param	buttonID			a button identifier
	 * @param	state				a button state
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

	/**
	 * @brief Implements the accept operation that takes a visitor as an argument (DP Visitor).
	 * 
	 * @param eventVisitor	a reference to a visitor
	 */
	virtual void accept( vgd::event::EventVisitor& eventVisitor )=0;
	
	
private:

	/**
	 * @brief	The state of the related button.
	 */
	State m_state;
	
	/**
	 * @brief	The identifier of the related button.
	 */
	int32	m_buttonID;
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_BUTTONEVENT_H
