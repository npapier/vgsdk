// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/SceneManager.hpp"

#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/event/DefaultEventProcessor.hpp"
#include "vgeGL/technique/Main.hpp"
#include "vgeGL/technique/RayCasting.hpp"



namespace vgeGL
{

namespace engine
{



SceneManager::SceneManager( vgd::Shp< vgeGL::engine::Engine > engine ) :
	::vge::engine::SceneManager	(	engine							),
	m_GLEngine					(	engine							),
	m_paintTechnique			(	new vgeGL::technique::Main()	),
	m_bCallInitialize			(	false							)
{
	// Initializes event processor subsystem.
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
	// Calls paint() provided by vge
	::vge::engine::SceneManager::paint( size, bUpdateBoundingBox );

	// Updates node collector if not done by vge
	if ( bUpdateBoundingBox == false )
	{
		updateNodeCollector();
	}

	// Renders scene
	vgd::Shp< vgeGL::technique::Technique > paintTechnique = getPaintTechnique();
	getGLEngine()->resetEval();
	paintTechnique->apply( getGLEngine().get(), getNodeCollector().getTraverseElements() );
}



void SceneManager::resize( const vgm::Vec2i size )
{
	// Calls resize() provided by vge
	::vge::engine::SceneManager::resize( size );
}



void SceneManager::onEvent( vgd::Shp<vgd::event::Event> event )
{
	for(	EventProcessorContainer::iterator	i	= m_eventProcessors.begin(),
												iEnd= m_eventProcessors.end();
			i != iEnd;
			++i )
	{
		vgd::Shp< vgeGL::event::IEventProcessor > iEventProcessor = *i;
		
		if ( iEventProcessor->isEnabled() )
		{
			const bool stop = iEventProcessor->onEvent( event );
	
			if ( stop )
			{
				break;
			}
		}
	}
}



void SceneManager::insertEventProcessor(	vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor,
											const int32 index )
{
	assert( 0 <= index && "Invalid index.");	
	assert( index <= getNumEventProcessors() && "Invalid index.");
	
	EventProcessorContainer::iterator iter = m_eventProcessors.begin() + index;
	
	m_eventProcessors.insert( iter, eventProcessor );
}



void SceneManager::pushBackEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor )
{
	m_eventProcessors.push_back( eventProcessor );
}



void SceneManager::removeEventProcessor( const int32 index )
{
	assert( 0 <= index && "Invalid index.");
	assert( index < getNumEventProcessors() && "Invalid index.");
		
	EventProcessorContainer::iterator iter = m_eventProcessors.begin() + index;
	
	m_eventProcessors.erase( iter );
}



void SceneManager::popBackEventProcessor()
{
	assert( getNumEventProcessors() >= 1 && "Empty event processor containers" );

	m_eventProcessors.pop_back();
}



const bool SceneManager::removeEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor )
{
	const int32 index = findEventProcessor( eventProcessor );
	
	if ( index != getNumEventProcessors() )
	{
		// Found
		removeEventProcessor( index );
		
		return true;
	}
	else
	{
		return false;
	}
}



const int32 SceneManager::findEventProcessor( ::vgeGL::event::IEventProcessor *eventProcessor ) const
{
	int32 retVal = 0;
	
	for(	EventProcessorContainer::const_iterator	i	= m_eventProcessors.begin(),
													iEnd= m_eventProcessors.end();
			i != iEnd;
			++i )
	{
		ElementOfEventProcessorContainer currentEventProcessor = *i;
		
		if ( currentEventProcessor.get() == eventProcessor )
		{
			return retVal;
		}
		
		++retVal;
	}
	
	return getNumEventProcessors();
}



const int32 SceneManager::findEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor ) const
{
	const int32 retVal = findEventProcessor( eventProcessor.get() );

	return retVal;
}



vgd::Shp< ::vgeGL::event::IEventProcessor > SceneManager::getEventProcessor( const int32 index  ) const
{
	assert( 0 <= index && "Invalid index.");
	assert( index < getNumEventProcessors() && "Invalid index.");

	return m_eventProcessors[index];
}



const int32 SceneManager::getNumEventProcessors() const
{
	return static_cast<int32>(m_eventProcessors.size());
}



const vgeGL::basic::Hit* SceneManager::castRayForHit( const int32 x, const int32 y )
{
	// CAST A RAY
	updateNodeCollector();

	getGLEngine()->resetEval();
	m_rayCasting.apply(	getGLEngine().get(), getNodeCollector().getTraverseElements(), x, y );

	if ( m_rayCasting.getHitsSize() == 0 )
	{
		return 0;
	}
	else
	{
		return &m_rayCasting.getNearestHit();
	}
}



vgd::node::Node* SceneManager::castRay( const int32 x, const int32 y )
{
	const vgeGL::basic::Hit* hit = castRayForHit( x, y );
	
	if ( hit == 0 )
	{
		return 0;
	}
	else
	{
		return m_rayCasting.getNearestHitNode();
	}
}



const vgeGL::technique::RayCasting& SceneManager::getRayCastingTechnique() const
{
	return m_rayCasting;
}



const bool SceneManager::isGLContextCurrent() const
{
	return m_GLEngine->isGLContextCurrent();
}



vgd::Shp< vgeGL::engine::Engine > SceneManager::getGLEngine()
{
	return m_GLEngine;
}



vgd::Shp< vgeGL::engine::Engine > SceneManager::getGLEngine() const
{
	return m_GLEngine;
}



vgd::Shp< vgeGL::technique::Technique > SceneManager::getPaintTechnique() const
{
	return m_paintTechnique;
}



void SceneManager::setPaintTechnique( vgd::Shp< vgeGL::technique::Technique > technique )
{
	m_paintTechnique = technique;
}



} // namespace engine

} // namespace vgeGL
