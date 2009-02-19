// VGSDK - Copyright (C) 2004-2006, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/ButtonStateSet.hpp"

#include "vgd/event/JoystickButtonEvent.hpp"
#include "vgd/event/KeyboardButtonEvent.hpp"
#include "vgd/event/MouseButtonEvent.hpp"



namespace vgd
{

namespace event
{



void ButtonStateSet::apply( const vgd::event::AxisEvent *pAxisEvent )
{
	assert( pAxisEvent != 0 );
}



void ButtonStateSet::apply( const vgd::event::HatEvent *pHatEvent )
{
	assert( pHatEvent != 0 );
}



void ButtonStateSet::apply( const vgd::event::JoystickButtonEvent *pJoystickButtonEvent )
{
	assert( pJoystickButtonEvent != 0 );

	if ( pJoystickButtonEvent->getState() == vgd::event::ButtonEvent::DOWN )
	{
		setDown( pJoystickButtonEvent->getButtonID() );
	}
	else if ( pJoystickButtonEvent->getState() == vgd::event::ButtonEvent::UP )
	{
		setUp( pJoystickButtonEvent->getButtonID() );
	}
}



void ButtonStateSet::apply( const vgd::event::KeyboardButtonEvent *pKeyboardButtonEvent )
{
	assert( pKeyboardButtonEvent != 0 );

	if ( pKeyboardButtonEvent->getState() == vgd::event::ButtonEvent::DOWN )
	{
		setDown( pKeyboardButtonEvent->getButtonID() );
	}
	else if ( pKeyboardButtonEvent->getState() == vgd::event::ButtonEvent::UP )
	{
		setUp( pKeyboardButtonEvent->getButtonID() );
	}
}



void ButtonStateSet::apply( const vgd::event::MouseButtonEvent *pMouseButtonEvent )
{
	assert( pMouseButtonEvent != 0 );

	if ( pMouseButtonEvent->getState() == vgd::event::ButtonEvent::DOWN )
	{
		setDown( pMouseButtonEvent->getButtonID() );
	}
	else if ( pMouseButtonEvent->getState() == vgd::event::ButtonEvent::UP )
	{
		setUp( pMouseButtonEvent->getButtonID() );
	}
}



void ButtonStateSet::apply( const vgd::event::Location2Event *  )
{
	// nothing to do.
}



void ButtonStateSet::apply( const vgd::event::Motion3Event * )
{
	// nothing to do.
}



void ButtonStateSet::apply( const vgd::event::MouseWheelEvent * )
{
	// nothing to do.
}



void ButtonStateSet::apply( const vgd::event::TimerEvent * )
{
	// nothing to do.
}



bool ButtonStateSet::isDown() const
{
	return ( m_down.size() >= 1 );
}



bool ButtonStateSet::isDown( const int32 idButton ) const
{
	ButtonIDSet::const_iterator iter;

	iter = m_down.find( idButton );

	return ( iter != m_down.end() );
}



void ButtonStateSet::setDown( const int32 idButton )
{
	m_down.insert( idButton );
}


void ButtonStateSet::setUp( const int32 idButton )
{
	m_down.erase( idButton );
}



void ButtonStateSet::setUp()
{
	m_down.clear();
}



uint32 ButtonStateSet::getNumDown() const
{
	return ( static_cast<uint32>(m_down.size()) );
}



bool ButtonStateSet::operator ==( const ButtonStateSet& other ) const
{
	return ( m_down == other.m_down );
}



bool ButtonStateSet::operator !=( const ButtonStateSet& other ) const
{
	return( m_down != other.m_down );
}



} // namespace event

} // namespace vgd
