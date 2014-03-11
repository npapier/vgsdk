// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/JoystickButtonEvent.hpp"

#include "vgd/event/device/Joystick.hpp"



namespace vgd
{

namespace event
{



JoystickButtonEvent::JoystickButtonEvent( Source * source, const ButtonStateSet & buttonStates, const int32 buttonID, const State state )
:	ButtonEvent( source, buttonStates, buttonID, state )
{}



void JoystickButtonEvent::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
