// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/TimerEvent.hpp"



namespace vgd
{

namespace event
{



TimerEvent::TimerEvent( Source *source, const ButtonStateSet& buttonStates ) :
	Event( source, buttonStates )
{}


TimerEvent::~TimerEvent()
{}


void TimerEvent::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace event
