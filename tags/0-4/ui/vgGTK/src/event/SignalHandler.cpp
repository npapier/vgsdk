// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/event/SignalHandler.hpp"

#include <cassert>



namespace vgGTK
{

namespace event
{



SignalHandler::SignalHandler()
:	m_connectedWidget( 0 )
{
	assert( m_connectedWidget == 0 );
}



SignalHandler::~SignalHandler()
{
	doDisconnect();
}



void SignalHandler::connect( Gtk::Widget * widget )
{
	assert( m_connectedWidget == 0 );

	m_connectedWidget = widget;
}



void SignalHandler::disconnect()
{
	assert( m_connectedWidget != 0 );

	doDisconnect();
}



const bool SignalHandler::isConnected() const
{
	return m_connectedWidget != 0;
}



void SignalHandler::store( const ::sigc::connection & connection )
{
	m_connections.push_back( connection );
}



void SignalHandler::doDisconnect()
{
	ConnectionContainer::iterator	i;
	for( i = m_connections.begin(); i != m_connections.end(); ++i )
	{
		i->disconnect();
	}

	m_connections.clear();
	m_connectedWidget = 0;
}



} // namespace event

} // namespace vgGTK
