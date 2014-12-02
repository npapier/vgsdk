//// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2011, 2013, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/engine/SceneManager.hpp"
//
//#ifdef __USE_VGALG__
//#include <vgAlg/intersect/helpers.hpp>
//#endif
//
//#include <vgd/basic/Time.hpp>
//#include <vgd/basic/TimeDuration.hpp>
//#include <vgd/node/LayerPlan.hpp>
//#include <vgd/node/VertexShape.hpp>
//
//#include <vge/service/Painter.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/event/DefaultEventProcessor.hpp"
//#include "vgeGLBase/event/TimerEventProcessor.hpp"
//#include "vgeGLBase/technique/ForwardRendering.hpp"
//#include "vgeGLBase/technique/RayCasting.hpp"
//
//
// 
//namespace vgeGLBase
//{
//
//namespace engine
//{
//
//
//
//SceneManager::SceneManager( vgd::Shp< vgeGLBase::engine::Engine > engine ) :
//	::vge::engine::SceneManager		(	engine										),
//	m_GLEngine						(	engine										),
//	//m_requestedGLContextProperties
//	m_hasCurrentGLContextProperties	(	false										),
//	//m_currentGLContextProperties
//	m_paintTechnique			(	new vgeGLBase::technique::ForwardRendering()	),
//	m_bCallInitialize			(	false										)
//{
//	// Initializes event processor subsystem.
//	using ::vgeGLBase::event::IEventProcessor;
//	using ::vgeGLBase::event::DefaultEventProcessor;
//	using ::vgeGLBase::event::TimerEventProcessor;
//
//	m_timerEventProcessor.reset( new TimerEventProcessor(this) );
//	vgd::Shp< IEventProcessor > defaultEventProcessor( new DefaultEventProcessor(this) );
//
//	insertEventProcessor( defaultEventProcessor );
//	insertEventProcessor( m_timerEventProcessor );
//}
//
//
//
//void SceneManager::initialize()
//{
//	m_bCallInitialize = true;
//}
//
//
//
//void SceneManager::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
//{
//	// Calls paint() provided by vge
//	::vge::engine::SceneManager::paint( size, bUpdateBoundingBox );
//
//	// Updates node collector if not done by vge
//	if ( bUpdateBoundingBox == false )
//	{
//		updateNodeCollector();
//	}
//
//	// RENDERING
//	vgd::Shp< vgeGLBase::technique::Technique > paintTechnique = getPaintTechnique();
//
//	//	Underlay
//	vgd::Shp< vgeGLBase::itf::IUnderlay > iunderlay = vgd::dynamic_pointer_cast< vgeGLBase::itf::IUnderlay >( paintTechnique );
//	if ( iunderlay )
//	{
//		// Underlay rendering is supported by the current paint technique
//		// So assigns the canvas underlay to the rendering technique
//		iunderlay->setUnderlay( getUnderlay() );
//	}
//
//	// Rendering of all OffscreenRendering nodes followed by the main rendering of the canvas scene graph (getRoot())
//	paintTechnique->setParameters( getGLEngine().get(), getNodeCollector().getTraverseElements(), this );
//	paintTechnique->apply( getGLEngine().get(), getNodeCollector().getTraverseElements() );
//
//	//	Overlay
//	if ( getOverlay() )
//	{
//		vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
//		getGLEngine()->evaluate( paint, getOverlay().get(), true, false );
//	}
//}
//
//
//
//void SceneManager::resize( const vgm::Vec2i size )
//{
//	// Calls resize() provided by vge
//	::vge::engine::SceneManager::resize( size );
//}
//
//
//
//void SceneManager::onEvent( vgd::Shp<vgd::event::Event> event )
//{
//	for(	EventProcessorContainer::iterator	i	= m_eventProcessors.begin(),
//												iEnd= m_eventProcessors.end();
//			i != iEnd;
//			++i )
//	{
//		vgd::Shp< vgeGLBase::event::IEventProcessor > iEventProcessor = *i;
//		
//		if ( iEventProcessor->isEnabled() )
//		{
//			const bool stop = iEventProcessor->onEvent( event );
//	
//			if ( stop )
//			{
//				break;
//			}
//		}
//	}
//}
//
//
//
//void SceneManager::insertEventProcessor(	vgd::Shp< ::vgeGLBase::event::IEventProcessor > eventProcessor,
//											const int32 index )
//{
//	assert( 0 <= index && "Invalid index.");	
//	assert( index <= getNumEventProcessors() && "Invalid index.");
//	
//	EventProcessorContainer::iterator iter = m_eventProcessors.begin() + index;
//	
//	m_eventProcessors.insert( iter, eventProcessor );
//}
//
//
//
//void SceneManager::pushBackEventProcessor( vgd::Shp< ::vgeGLBase::event::IEventProcessor > eventProcessor )
//{
//	m_eventProcessors.push_back( eventProcessor );
//}
//
//
//
//void SceneManager::removeEventProcessor( const int32 index )
//{
//	assert( 0 <= index && "Invalid index.");
//	assert( index < getNumEventProcessors() && "Invalid index.");
//		
//	EventProcessorContainer::iterator iter = m_eventProcessors.begin() + index;
//	
//	m_eventProcessors.erase( iter );
//}
//
//
//
//void SceneManager::popBackEventProcessor()
//{
//	assert( getNumEventProcessors() >= 1 && "Empty event processor containers" );
//
//	m_eventProcessors.pop_back();
//}
//
//
//
//const bool SceneManager::removeEventProcessor( vgd::Shp< ::vgeGLBase::event::IEventProcessor > eventProcessor )
//{
//	const int32 index = findEventProcessor( eventProcessor );
//	
//	if ( index != getNumEventProcessors() )
//	{
//		// Found
//		removeEventProcessor( index );
//		
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//
//
//const int32 SceneManager::findEventProcessor( ::vgeGLBase::event::IEventProcessor *eventProcessor ) const
//{
//	int32 retVal = 0;
//	
//	for(	EventProcessorContainer::const_iterator	i	= m_eventProcessors.begin(),
//													iEnd= m_eventProcessors.end();
//			i != iEnd;
//			++i )
//	{
//		ElementOfEventProcessorContainer currentEventProcessor = *i;
//		
//		if ( currentEventProcessor.get() == eventProcessor )
//		{
//			return retVal;
//		}
//		
//		++retVal;
//	}
//	
//	return getNumEventProcessors();
//}
//
//
//
//const int32 SceneManager::findEventProcessor( vgd::Shp< ::vgeGLBase::event::IEventProcessor > eventProcessor ) const
//{
//	const int32 retVal = findEventProcessor( eventProcessor.get() );
//
//	return retVal;
//}
//
//
//
//vgd::Shp< ::vgeGLBase::event::IEventProcessor > SceneManager::getEventProcessor( const int32 index  ) const
//{
//	assert( 0 <= index && "Invalid index.");
//	assert( index < getNumEventProcessors() && "Invalid index.");
//
//	return m_eventProcessors[index];
//}
//
//
//
//const int32 SceneManager::getNumEventProcessors() const
//{
//	return static_cast<int32>(m_eventProcessors.size());
//}
//
//
//
//vgd::Shp< ::vgeGLBase::event::TimerEventProcessor > SceneManager::getTimerEventProcessor()
//{
//	return m_timerEventProcessor;
//}
//
//
//
//const vgeGLBase::basic::Hit* SceneManager::castRayForHit( const int32 x, const int32 y )
//{
//	if ( !startVGSDK() )
//	{
//		vgLogDebug("vgeGLBase::engine::SceneManager::castRayForHit(): startVGSDK fails !");
//		return 0;
//	}
//
//	// CAST A RAY
//	updateNodeCollector();
//
//	m_rayCasting.setParameters( getGLEngine().get(), getNodeCollector().getTraverseElements() );
//	m_rayCasting.apply(	getGLEngine().get(), getNodeCollector().getTraverseElements(), x, y );
//
//	if ( m_rayCasting.getHitsSize() == 0 )
//	{
//		return 0;
//	}
//	else
//	{
//		return &m_rayCasting.getNearestHit();
//	}
//}
//
//
//
//const vgeGLBase::basic::Hit* SceneManager::castRayForHit( const vgm::Vec3f raySourceW, const vgm::Vec3f rayDirectionW )
//{
//	if ( !startVGSDK() )
//	{
//		vgLogDebug("vgeGLBase::engine::SceneManager::castRayForHit(): startVGSDK fails !");
//		return 0;
//	}
//
//	// CAST A RAY
//	updateNodeCollector();
//
//	m_rayCasting.setParameters( getGLEngine().get(), getNodeCollector().getTraverseElements() );
//	m_rayCasting.apply(	getGLEngine().get(), getNodeCollector().getTraverseElements(), raySourceW, rayDirectionW );
//
//	if ( m_rayCasting.getHitsSize() == 0 )
//	{
//		return 0;
//	}
//	else
//	{
//		return &m_rayCasting.getNearestHit();
//	}
//}
//
//
//
//vgd::node::Node* SceneManager::castRay( const int32 x, const int32 y )
//{
//	const vgeGLBase::basic::Hit* hit = castRayForHit( x, y );
//
//	if ( hit == 0 )
//	{
//		return 0;
//	}
//	else
//	{
//		return m_rayCasting.getNearestHitNode();
//	}
//}
//
//
//vgd::node::VertexShape * SceneManager::castRay(	const int32 x, const int32 y,
//												vgm::TriangleExt& oABCP )
//{
//#ifndef __USE_VGALG__
//	#pragma message("SceneManager::castRay() disabled.")
//	vgAssert(false);
//	return 0;
//#else
//	// cast ray
//	vgd::node::VertexShape * hitShape = dynamic_cast< vgd::node::VertexShape *>(castRay(x, y));
//
//	if ( hitShape )
//	{
//		// Hit
//		const vgeGLBase::basic::Hit& hit = getRayCastingTechnique().getNearestHit();
//
//		// Compute picked triangle
//		float oDistance;
//		const bool found = vgAlg::intersect::getTriangle( hit.nearestVertexO(), hitShape, oABCP, oDistance );
//
//		if ( found )
//		{
//			return hitShape;
//		}
//		else
//		{
//			vgAssert( false );
//			return 0;
//		}
//	}
//	else
//	{
//		return 0;
//	}
//#endif
//}
//
//
//vgd::node::VertexShape * SceneManager::castRay( const vgm::Vec3f raySourceW, const vgm::Vec3f rayDirectionW, vgm::TriangleExt& oABCP )
//{
//#ifndef __USE_VGALG__
//	#pragma message("SceneManager::castRay() disabled.")
//	vgAssert(false);
//	return 0;
//#else
//	// cast ray
//	const vgeGLBase::basic::Hit * hit = castRayForHit(raySourceW, rayDirectionW);
//
//	if ( hit )
//	{
//		vgd::node::VertexShape * hitShape = dynamic_cast< vgd::node::VertexShape *>(getRayCastingTechnique().getNearestHitNode());
//
//		// Compute picked triangle
//		float oDistance;
//		const bool found = vgAlg::intersect::getTriangle( hit->nearestVertexO(), hitShape, oABCP, oDistance );
//
//		if ( found )
//		{
//			//vgLogDebug("hit triangle (%i %i %i)", iABC[0], iABC[1], iABC[2]);
//			//vgLogDebug("(u,v)=%f %f", barycentricCoordHitPoint[0], barycentricCoordHitPoint[1] );
//			return hitShape;
//		}
//		else
//		{
//			vgAssert( false );
//			return 0;
//		}
//	}
//	else
//	{
//		return 0;
//	}
//#endif
//}
//
//
//vgd::node::VertexShape * SceneManager::getNearestHitNode()
//{
//	vgd::node::VertexShape * shape = dynamic_cast< vgd::node::VertexShape *>(getRayCastingTechnique().getNearestHitNode());
//	return shape;
//}
//
//const vgeGLBase::basic::Hit SceneManager::getNearestHit()
//{
//	const vgeGLBase::basic::Hit& hit = getRayCastingTechnique().getNearestHit();
//	return hit;
//}
//
//
//vgeGLBase::technique::RayCasting& SceneManager::getRayCastingTechnique()
//{
//	return m_rayCasting;
//}
//
//
//void SceneManager::setRequestedGLContextProperties( const GLContextProperties properties )
//{
//	m_requestedGLContextProperties = properties;
//}
//
//
//
//const bool SceneManager::getGLContextProperties( GLContextProperties& properties ) const
//{
//	if ( m_hasCurrentGLContextProperties )
//	{
//		properties = m_currentGLContextProperties;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//
//
//const bool SceneManager::isGLContextCurrent() const
//{
//	return m_GLEngine->isGLContextCurrent();
//}
//
//
//
//vgd::Shp< vgeGLBase::engine::Engine > SceneManager::getGLEngine()
//{
//	return m_GLEngine;
//}
//
//
//
//vgd::Shp< vgeGLBase::engine::Engine > SceneManager::getGLEngine() const
//{
//	return m_GLEngine;
//}
//
//
//
//vgd::Shp< vgeGLBase::technique::Technique > SceneManager::getPaintTechnique() const
//{
//	return m_paintTechnique;
//}
//
//
//
//void SceneManager::setPaintTechnique( vgd::Shp< vgeGLBase::technique::Technique > technique )
//{
//	m_paintTechnique = technique;
//}
//
//
//
//void SceneManager::setOverlay( vgd::Shp< vgd::node::LayerPlan > overlay )
//{
//	m_overlay = overlay;
//}
//
//
//
//vgd::Shp< vgd::node::LayerPlan > SceneManager::getOverlay()
//{
//	return m_overlay;
//}
//
//
//
//void SceneManager::setUnderlay( vgd::Shp< vgd::node::LayerPlan > underlay )
//{
//	m_underlay = underlay;
//}
//
//
//
//vgd::Shp< vgd::node::LayerPlan > SceneManager::getUnderlay()
//{
//	return m_underlay;
//}
//
//
//
//} // namespace engine
//
//} // namespace vgeGLBase
//