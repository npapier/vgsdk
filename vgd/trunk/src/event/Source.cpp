// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/Listener.hpp"
#include "vgd/event/Source.hpp"

namespace vgd
{
	
namespace event
{
	
	
Source::Source()
{}

	
Source::~Source()
{}


void Source::attachEventListener( Listener *listener )
{
	this->listeners.insert( listener );
}


void Source::detachEventListener( Listener *listener )
{
	this->listeners.erase( listener );
}


void Source::fireEvent( vgd::Shp<vgd::event::Event> event )
{
	ListenerContainer::iterator	iterator;
	for( iterator = this->listeners.begin(); iterator != this->listeners.end(); iterator++ )
	{
		Listener *listener = *iterator;
		listener->onEvent( event );
	}
}


} // namespace event
	
} // namespace vgd
