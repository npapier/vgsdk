// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/ButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	


ButtonEvent::ButtonEvent( Source *source, const ButtonStateSet& buttonStates, const int32 buttonID, const State state ) :
	Event		(	source, buttonStates	),
	m_buttonID	(	buttonID	),
	m_state		(	state		)
{}


ButtonEvent::~ButtonEvent()
{}


const int32 ButtonEvent::getButtonID() const
{
	return m_buttonID;
}


const ButtonEvent::State ButtonEvent::getState() const
{
	return m_state;
}



} // namespace event

} // namespace event
