// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/Source.hpp"

#include "vgd/event/Listener.hpp"


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
	for(	ListenerContainer::iterator i = this->listeners.begin();
			i != this->listeners.end();
			++i )
	{
		Listener *listener = *i;
		listener->onEvent( event );
	}
}


} // namespace event
	
} // namespace vgd
