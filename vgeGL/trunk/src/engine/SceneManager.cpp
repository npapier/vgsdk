// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/SceneManager.hpp"

#include <vgDebug/Global.hpp>

#include "vgeGL/event/DefaultEventProcessor.hpp"
#include "vgeGL/technique/Main.hpp"
#include "vgeGL/technique/RayCasting.hpp"



namespace vgeGL
{

namespace engine
{



SceneManager::SceneManager( vgd::Shp< vgeGL::engine::Engine > pEngine ) :
	::vge::engine::SceneManager	(	pEngine	),
	m_GLEngine					(	pEngine	),
	m_bCallInitialize			(	false	)
{
	using ::vgeGL::event::IEventProcessor;
	using ::vgeGL::event::DefaultEventProcessor;

	vgd::Shp< IEventProcessor > eventProcessor( new DefaultEventProcessor(this) );
	
	insertEventProcessor( eventProcessor );
}



void SceneManager::initialize()
{
	m_bCallInitialize = true;
}



void SceneManager::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	::vge::engine::SceneManager::paint( size, bUpdateBoundingBox );

	vgeGL::technique::Main main;
	getEngine()->resetEval();
	main.apply( getEngine().get(), getNodeCollector().getTraverseElements() );
}



void SceneManager::resize( const vgm::Vec2i )
{
}



void SceneManager::onEvent( vgd::Shp<vgd::event::Event> event )
{
	for(	EventProcessorContainer::iterator	i	= m_eventProcessors.begin(),
												iEnd= m_eventProcessors.end();
			i != iEnd;
			++i )
	{
		vgd::Shp< vgeGL::event::IEventProcessor > iEventProcessor = *i;
		
		bool stop = iEventProcessor->onEvent( event );
		if ( stop )
		{
			break;
		}
	}
}



void SceneManager::insertEventProcessor(	vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor,
											const uint32 index )
{
	assert( index <= getNumEventProcessors() && "Invalid index.");
	
	EventProcessorContainer::iterator iter = m_eventProcessors.begin() + index;
	
	m_eventProcessors.insert( iter, eventProcessor );
}



void SceneManager::removeEventProcessor( const uint32 index )
{
	assert( index < getNumEventProcessors() && "Invalid index.");
		
	EventProcessorContainer::iterator iter = m_eventProcessors.begin() + index;
	
	m_eventProcessors.erase( iter );
}



const bool SceneManager::removeEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor )
{
	int32 index = findEventProcessor( eventProcessor );
	
	if ( index != -1 )
	{
		// Founded
		removeEventProcessor( index );
		
		return true;
	}
	else
	{
		return false;
	}
}



int32 SceneManager::findEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor ) const
{
	int32 retVal = 0;
	
	for(	EventProcessorContainer::const_iterator	i	= m_eventProcessors.begin(),
													iEnd= m_eventProcessors.end();
			i != iEnd;
			++i )
	{
		ElementOfEventProcessorContainer currentEventProcessor = *i;
		
		if ( currentEventProcessor == eventProcessor )
		{
			return ( retVal);
		}
		
		++retVal;
	}
	
	return ( -1 );
}



vgd::Shp< ::vgeGL::event::IEventProcessor > SceneManager::getEventProcessor( const uint32 index  ) const
{
	assert( index < getNumEventProcessors() && "Invalid index.");
	
	return ( m_eventProcessors[index] );
}



const uint32 SceneManager::getNumEventProcessors() const
{
	return ( m_eventProcessors.size() );
}



vgd::node::Node* SceneManager::castRay( const int32 x, const int32 y )
{
	// CAST A RAY
	getNodeCollector().reset();
	getRoot()->traverse( getNodeCollector() );

	vgeGL::technique::RayCasting raycasting;
	getEngine()->resetEval();
	raycasting.apply(	getEngine().get(), getNodeCollector().getTraverseElements(), x, y );

	if ( raycasting.getHitsSize() == 0 )
	{
		return ( 0 );
	}
	else
	{
		return ( raycasting.getNearestHitNode() );
	}
}



const bool SceneManager::isGLContextCurrent() const
{
	return ( m_GLEngine->isGLContextCurrent() );
}



vgd::Shp< vgeGL::engine::Engine > SceneManager::getGLEngine()
{
	return ( m_GLEngine );
}



} // namespace engine

} // namespace vgeGL
