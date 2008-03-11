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
	 * @brief	Defines joystick button identifers
	 */
	enum
	{
		JOY_BUTTON_1 = 1024,JOY_BUTTON_2, JOY_BUTTON_3, JOY_BUTTON_4, JOY_BUTTON_5,
		JOY_BUTTON_6,  JOY_BUTTON_7,  JOY_BUTTON_8,  JOY_BUTTON_9,  JOY_BUTTON_10,
		JOY_BUTTON_11, JOY_BUTTON_12, JOY_BUTTON_13, JOY_BUTTON_14, JOY_BUTTON_15,
		JOY_BUTTON_16, JOY_BUTTON_17, JOY_BUTTON_18, JOY_BUTTON_19, JOY_BUTTON_20,
		JOY_BUTTON_21, JOY_BUTTON_22, JOY_BUTTON_23, JOY_BUTTON_24, JOY_BUTTON_25,
		JOY_BUTTON_26, JOY_BUTTON_27, JOY_BUTTON_28, JOY_BUTTON_29, JOY_BUTTON_30,
		JOY_BUTTON_31, JOY_BUTTON_32
	};

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
