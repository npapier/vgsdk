// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker


#include "vgd/event/KeyboardButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
	
KeyboardButtonEvent::KeyboardButtonEvent( Source *source, State state )
: ButtonEvent( source, state )
{}


KeyboardButtonEvent::~KeyboardButtonEvent()
{}


} // namespace event

} // namespace event
