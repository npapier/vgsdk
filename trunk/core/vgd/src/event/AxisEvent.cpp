// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/AxisEvent.hpp"

#include <cassert>



namespace vgd
{

namespace event
{



AxisEvent::AxisEvent( Source * source, const ButtonStateSet & buttonStates, const int index, const float value )
:	Event( source, buttonStates ),
	m_index( index ),
	m_value( value )
{
	assert( (value >= -1.f) && (value <= 1.f) && "Value must be in range [-1, 1]" );
}



const int AxisEvent::getIndex() const
{
	return m_index;
}



const float AxisEvent::getValue() const
{
	return m_value;
}



void AxisEvent::accept( vgd::event::EventVisitor & eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
