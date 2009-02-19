// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgd/event/KeyboardButtonEvent.hpp"


#include "vgd/event/ButtonStateSet.hpp"



namespace vgd
{

namespace event
{



KeyboardButtonEvent::KeyboardButtonEvent( Source *source, const ButtonStateSet& buttonStates, const int32 buttonID, const State state) :
	ButtonEvent( source, buttonStates, buttonID, state )
{}


KeyboardButtonEvent::~KeyboardButtonEvent()
{}


void KeyboardButtonEvent::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace event
