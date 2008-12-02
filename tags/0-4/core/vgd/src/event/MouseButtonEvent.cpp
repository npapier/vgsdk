// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/MouseButtonEvent.hpp"

#include "vgd/event/ButtonStateSet.hpp"



namespace vgd
{
	
namespace event
{
	

	
MouseButtonEvent::MouseButtonEvent( Source *source, const ButtonStateSet& buttonStates, 
									const int32 buttonID, const State state,
									const Location& location, const Size& size )
:	Location2( location, size),					
	ButtonEvent( source, buttonStates, buttonID, state )
{}


MouseButtonEvent::~MouseButtonEvent()
{}


void MouseButtonEvent::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
