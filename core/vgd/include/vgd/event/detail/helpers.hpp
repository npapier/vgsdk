// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGD_EVENT_DETAIL_HELPERS_HPP_
#define _VGD_EVENT_DETAIL_HELPERS_HPP_

#include <string>

#include "vgd/vgd.hpp"
#include "vgd/event/ButtonEvent.hpp"
#include "vgd/event/HatEvent.hpp"
#include "vgd/event/MouseWheelEvent.hpp"



namespace vgd
{

namespace event
{

namespace detail
{



/**
 * @brief	Retrieves the name of the given ButtonEvent::State flag.
 *
 * @param	state	a button state
 *
 * @return	a string containing the button state's name
 */
VGD_API const std::string toString( const ButtonEvent::State state );



/**
 * @brief	Retrieves the name of the given button.
 *
 * @param	button	a button
 *
 * @return	a string containing the given button's name
 *
 * @see		ButtonEvent, JoystickButtonEvent, KeyboardButtonEvent, MouseButtonEvent
 */
VGD_API const std::string toString( const int32 button );



/**
 * @brief	Retrieves the name of a given HatEvent::State flag.
 *
 * @param	state	a hat state
 *
 * @return	a string containing the hat state's name
 */
VGD_API const std::string toString( const HatEvent::State state );



/**
 * @brief	Retrieves the name of the given MouseWheelEvent::Axis flag.
 *
 * @param	axis	a mouse wheel axis
 *
 * @return	a string containing the mouse wheel's name
 */
VGD_API const std::string toString( const MouseWheelEvent::Axis axis );



} // namespace detail

} // namespace event

} // namespace vgd




#endif /*_VGD_EVENT_DETAIL_HELPERS_HPP_*/
