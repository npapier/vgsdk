// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/Event.hpp"


namespace vgd
{
	
namespace event
{
	
	
Event::Event( Source *source, const ButtonStateSet& buttonStates ) : 
	m_pSource(source),
	m_buttonStates(buttonStates)
{}


Event::~Event()
{}


Source* Event::getSource() const
{
	return m_pSource;
}


const ButtonStateSet& Event::getButtonStates() const
{
	return m_buttonStates;
}


bool Event::isButtonDown( const int32 idButton ) const
{
	return ( m_buttonStates.isDown( idButton ) );
}


} // namespace event

} // namespace vgd
