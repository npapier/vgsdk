// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/ButtonStateSet.hpp"

#include "vgd/event/KeyboardButtonEvent.hpp"
#include "vgd/event/MouseButtonEvent.hpp"


namespace vgd
{
	
namespace event
{

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
