// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/MouseWheelEvent.hpp"



namespace vgd
{
	
namespace event
{

	
	
MouseWheelEvent::MouseWheelEvent( Source *source, const ButtonStateSet& buttonStates, Axis a, int32 d, const unsigned int deviceId )
: Event( source, buttonStates ),
  axis( a ),
  delta( d ),
  m_deviceId(deviceId)
{}


const MouseWheelEvent::Axis MouseWheelEvent::getAxis() const
{
	return this->axis;
}


const int32 MouseWheelEvent::getDelta() const
{
	return this->delta;
}

unsigned int MouseWheelEvent::getDeviceId() const
{
	return m_deviceId;
}


void MouseWheelEvent::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
