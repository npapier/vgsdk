// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker


#include "vgd/event/MouseButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
	
MouseButtonEvent::MouseButtonEvent( Source *source, State state, Button btn )
: ButtonEvent( source, state ),
  button( btn )
{}


MouseButtonEvent::~MouseButtonEvent()
{}


MouseButtonEvent::Button MouseButtonEvent::getButton() const
{
	return this->button;
}


} // namespace event

} // namespace event
