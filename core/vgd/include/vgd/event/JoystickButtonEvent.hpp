// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_JOYSTICKBUTTONEVENT_HPP_
#define _VGD_EVENT_JOYSTICKBUTTONEVENT_HPP_

#include "vgd/vgd.hpp"
#include "vgd/event/ButtonEvent.hpp"



namespace vgd
{

namespace event
{



struct Joystick;



/**
 * @brief	Implements the button event for joysticks
 */
struct VGD_API JoystickButtonEvent : public ButtonEvent
{

	/**
	 * @brief	Constructor
	 *
	 * @param	source			a pointer to the source joystick of the event
	 * @param	buttonStates	a reference to the button state set
	 * @param	buttonID		a button identifier
	 * @param	state			a button state
	 */
	JoystickButtonEvent( Joystick * source, const ButtonStateSet & buttonStates, const int32 buttonID, const State state );


	/**
	 * @brief	Retrieves the emitter joystick.
	 *
	 * @return	a pointer to a joystick
	 */
	Joystick * getJoystick() const;


	/**
	 * @name	Overrides
	 */
	//@{
	void accept( vgd::event::EventVisitor& eventVisitor );
	//@}


private:

	Joystick * m_joystick;	///< A pointer to the source joystick.
};

} // namespace event

} // namespace vgd



#endif /*_VGD_EVENT_JOYSTICKBUTTONEVENT_HPP_*/
