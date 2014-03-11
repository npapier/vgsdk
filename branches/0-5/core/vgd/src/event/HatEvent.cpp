// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgd/event/HatEvent.hpp"



namespace vgd
{

namespace event
{



HatEvent::HatEvent( Source * source, const ButtonStateSet & buttonStates, const int index, const State state )
:	Event( source, buttonStates ),
	m_index( index ),
	m_state( state )
{}



const int HatEvent::getIndex() const
{
	return m_index;
}



const HatEvent::State HatEvent::getState() const
{
	return m_state;
}



void HatEvent::accept( vgd::event::EventVisitor & eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
