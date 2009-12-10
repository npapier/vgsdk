// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/SceneManager.hpp"

#include <vgd/basic/Time.hpp>
#include <vgd/basic/TimeDuration.hpp>
#include <vgd/node/LayerPlan.hpp>
#include <vgDebug/convenience.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/event/DefaultEventProcessor.hpp"
#include "vgeGL/event/TimerEventProcessor.hpp"
#include "vgeGL/technique/ForwardRendering.hpp"
#include "vgeGL/technique/RayCasting.hpp"


 
namespace vgeGL
{

namespace engine
{



SceneManager::SceneManager( vgd::Shp< vgeGL::engine::Engine > engine ) :
	::vge::engine::SceneManager	(	engine										),
	m_GLEngine					(	engine										),
	m_paintTechnique			(	new vgeGL::technique::ForwardRendering()	),
	m_bCallInitialize			(	false										)
{
	// Initializes event processor subsystem.
	using ::vgeGL::event::IEventProcessor;
	using ::vgeGL::event::DefaultEventProcessor;
	using ::vgeGL::event::TimerEventProcessor;

	m_timerEventProcessor.reset( new TimerEventProcessor(this) );
	vgd::Shp< IEventProcessor > defaultEventProcessor( new DefaultEventProcessor(this) );

	insertEventProcessor( defaultEventProcessor );
	insertEventProcessor( m_timerEventProcessor );
}



void SceneManager::initialize()
{
	m_bCallInitialize = true;
}



void SceneManager::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
//	vgLogDebug( "Begin SceneManager::paint:" );
	vgd::basic::Time paintTime;
	
	// Calls paint() provided by vge
	vgd::basic::Time time;
	::vge::engine::SceneManager::paint( size, bUpdateBoundingBox );
//	vgLogDebug2( "::vge::engine::SceneManager::paint(): %i", time.getElapsedTime().ms() );
//vgLogDebug2( "pt1: %i", paintTime.getElapsedTime().ms() );
	// Updates node collector if not done by vge
	if ( bUpdateBoundingBox == false )
	{
		vgd::basic::Time time;
		updateNodeCollector();
//		vgLogDebug2( "updateNodeCollector(): %i", time.getElapsedTime().ms() );
	}

	// Renders scene graph
	time.restart();
	vgd::Shp< vgeGL::technique::Technique > paintTechnique = getPaintTechnique();
	vgd::Shp< vgeGL::itf::IUnderlay > iunderlay = vgd::dynamic_pointer_cast< vgeGL::itf::IUnderlay >( paintTechnique );
	if ( iunderlay )
	{
		// Transferts underlay to the rendering technique
		iunderlay->setUnderlay( getUnderlay() );
	}
//	vgLogDebug2( "iunderlay: %i", time.getElapsedTime().ms() );
//vgLogDebug2( "pt2: %i", paintTime.getElapsedTime().ms() );

	//time.restart();
	//getGLEngine()->resetEval();
//	vgLogDebug2( "getGLEngine()->resetEval(): %i", time.getElapsedTime().ms() );
//vgLogDebug2( "pt3: %i", paintTime.getElapsedTime().ms() );

	time.restart();
	paintTechnique->apply( getGLEngine().get(), getNodeCollector().getTraverseElements() );
//	vgLogDebug2( "paintTechnique->apply(): %i", time.getElapsedTime().ms() );
//vgLogDebug2( "pt4: %i", paintTime.getElapsedTime().ms() );
	// Renders overlay
	if ( getOverlay() )
	{
		time.restart();
		vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
		getGLEngine()->evaluate( paint, getOverlay().get(), true, false );
//		vgLogDebug2( "getGLEngine()->evaluate() for overlay: %i", time.getElapsedTime().ms() );
	}
//vgLogDebug2( "pt5: %i", paintTime.getElapsedTime().ms() );
//	vgLogDebug2( "End SceneManager::paint: %i", paintTime.getElapsedTime().ms() );
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



vgd::Shp< ::vgeGL::event::TimerEventProcessor > SceneManager::getTimerEventProcessor()
{
	return m_timerEventProcessor;
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



void SceneManager::setOverlay( vgd::Shp< vgd::node::LayerPlan > overlay )
{
	m_overlay = overlay;
}



vgd::Shp< vgd::node::LayerPlan > SceneManager::getOverlay()
{
	return m_overlay;
}



void SceneManager::setUnderlay( vgd::Shp< vgd::node::LayerPlan > underlay )
{
	m_underlay = underlay;
}



vgd::Shp< vgd::node::LayerPlan > SceneManager::getUnderlay()
{
	return m_underlay;
}



} // namespace engine

} // namespace vgeGL
