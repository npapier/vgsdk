// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgd/event/KeyboardButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
	
KeyboardButtonEvent::KeyboardButtonEvent( Source *source, State state, Key k )
: ButtonEvent( source, state ),
  key( k )
{}


KeyboardButtonEvent::~KeyboardButtonEvent()
{}


KeyboardButtonEvent::Key KeyboardButtonEvent::getKey() const
{
	return this->key;
}


} // namespace event

} // namespace event
