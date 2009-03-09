// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgd/event/SizeEvent.hpp"

#include <limits>



namespace vgd
{

namespace event
{



SizeEvent::SizeEvent( Source * source, const ButtonStateSet & buttonStates, const vgm::Vec2i & size )
:	Event( source, buttonStates ),
	m_size( size )
{}



SizeEvent::~SizeEvent()
{}



const vgm::Vec2i& SizeEvent::getSize() const
{
	return m_size;
}



void SizeEvent::accept( vgd::event::EventVisitor& eventVisitor )
{
	eventVisitor.apply( this );
}



} // namespace event

} // namespace vgd
