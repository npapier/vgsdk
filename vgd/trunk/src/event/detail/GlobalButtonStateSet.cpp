// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/detail/GlobalButtonStateSet.hpp"



namespace vgd
{

namespace event
{

namespace detail
{


const vgd::event::ButtonStateSet& GlobalButtonStateSet::get()
{
	return ( m_states );
}



void GlobalButtonStateSet::update( const int32 buttonID, const bool isDown )
{
	if ( isDown )
	{
		m_states.setDown( buttonID );
	}
	else
	{
		m_states.setUp( buttonID );
	}
}


vgd::event::ButtonStateSet	GlobalButtonStateSet::m_states;



} // namespace detail

} // namespace event

} // namespace vgd
