// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker


#include "vgd/event/ButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
	
ButtonEvent::ButtonEvent( Source *source, State state )
: Event( source ),
  state( state )
{}


ButtonEvent::~ButtonEvent()
{}


} // namespace event

} // namespace event
