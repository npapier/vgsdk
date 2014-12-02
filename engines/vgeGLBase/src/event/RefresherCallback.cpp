// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/event/RefresherCallback.hpp"

#include <vgd/event/TimerEvent.hpp>


namespace vgeGL
{

namespace event
{



RefresherCallback::RefresherCallback()
{
	setExecutionDuration( 0 );
	setFrequency( 60 );
}


RefresherCallback::RefresherCallback( vgeGL::engine::SceneManager * sceneManager )
:	TimerCallback( sceneManager )
{
	setExecutionDuration( 0 );
	setFrequency( 60 );
}


RefresherCallback::RefresherCallback( vgd::Shp< vgd::node::Node > node, vgeGL::engine::SceneManager * sceneManager )
:	TimerCallback( node, sceneManager )
{
	setExecutionDuration( 0 );
	setFrequency( 60 );
}


void RefresherCallback::apply( const vgd::Shp< vgd::event::TimerEvent > event )
{
	event->scheduleRefreshForced();
}


} // namespace event

} // namespace vgeGL