// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/event/TimerEventProcessor.hpp"

#include <vgd/event/TimerCallback.hpp>
#include <vgd/event/TimerEvent.hpp>
#include "vgeGL/engine/SceneManager.hpp"



namespace vgeGL
{

namespace event
{



TimerEventProcessor::TimerEventProcessor( ::vgeGL::engine::SceneManager *sceneManager ) 
:	EventProcessor( sceneManager )
{}



void TimerEventProcessor::add( vgd::Shp< vgd::event::TimerCallback > callback )
{
	assert( callback != 0 );

	if ( ! has( callback ) )
	{
		m_callbacks.insert( callback );
	}
}



void TimerEventProcessor::remove( vgd::Shp< vgd::event::TimerCallback > callback )
{
	assert( callback != 0 );

	TimerCallbackContainer::iterator found = m_callbacks.find( callback );

	if ( found != m_callbacks.end() )
	{
		m_callbacks.erase( found );
	}
}



const bool TimerEventProcessor::has( vgd::Shp< vgd::event::TimerCallback > callback ) const
{
	assert( callback != 0 );

	TimerCallbackContainer::const_iterator found = m_callbacks.find( callback );

	return found != m_callbacks.end();
}



const uint TimerEventProcessor::count() const
{
	return m_callbacks.size();
}



const bool TimerEventProcessor::onEvent( vgd::Shp<vgd::event::Event> event )
{
	// onEvent() is called only when isEnabled() returns true.
	assert( isEnabled() );

	using ::vgd::event::TimerEvent;
	vgd::Shp< TimerEvent > timerEvent = vgd::dynamic_pointer_cast< TimerEvent >( event );

	//vgLogDebug("TimerEventProcessor::onEvent:%s", typeid(*event.get()).name() );

	if ( timerEvent )
	{
		// Incoming event is a timer event
		onTimerEvent( timerEvent );

		return true;
	}
	else
	{
		// Incoming event is not a timer event
		return false;
	}
}



void TimerEventProcessor::onTimerEvent( vgd::Shp<vgd::event::TimerEvent> event )
{
	// First stage : executes callbacks
	typedef std::list< vgd::Shp< vgd::event::TimerCallback > > TimerCallbackList;
	TimerCallbackList toBeRemoved;

	for(	TimerCallbackContainer::iterator	i		= m_callbacks.begin(),
												iEnd	= m_callbacks.end();
			i != iEnd;
			++i )
	{
		vgd::Shp< vgd::event::TimerCallback > callback = *i;
		assert( (*i) != 0 );

		const bool shouldBeRemoved = (*callback)( event );
		if ( shouldBeRemoved )
		{
			toBeRemoved.push_back( callback );
		}
	}

	// Second stage : removes callback that should be removed.
	while ( toBeRemoved.size() > 0 )
	{
		vgd::Shp< vgd::event::TimerCallback > callback = *toBeRemoved.begin();
		toBeRemoved.pop_front();

		assert( has(callback) && "Internal error : Callback not in timer event processor" );
		remove( callback );
	}
}



} // namespace event

} // namespace vgeGL
