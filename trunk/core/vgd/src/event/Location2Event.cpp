// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/Location2Event.hpp"

#include <limits>



namespace vgd
{

namespace event
{
	

	
Location2Event::Location2Event(	Source * source, const ButtonStateSet& buttonStates, const Location& location, const Location& previousLocation,
								const Size& size, const unsigned int deviceId )
:	Location2( location, size),
	Event( source, buttonStates ),
	m_previous( previousLocation ),
	m_deviceId(deviceId)
{}


Location2Event::~Location2Event()
{}


const Location2Event::Location& Location2Event::getPreviousLocation() const
{
	return this->m_previous;
}


const Location2Event::LocationDelta Location2Event::getDelta() const
{
	if ( this->m_previous == vgm::Vec2f( std::numeric_limits<float>::max(), std::numeric_limits<float>::max() ) )
	{
		return ( vgm::Vec2f(0.f, 0.f) );
	}
	else
	{
		LocationDelta delta = this->m_location - this->m_previous;
		return ( delta );
	}
}

unsigned int Location2Event::getDeviceId() const
{
	return m_deviceId;
}


void Location2Event::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
