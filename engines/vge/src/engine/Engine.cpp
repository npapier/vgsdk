// VGSDK - Copyright (C) 2004, 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/engine/Engine.hpp"

#include <vgd/node/Camera.hpp>

#include "vge/handler/Handler.hpp"
#include "vge/handler/HandlerRegistry.hpp"
#include "vge/service/Painter.hpp"
#include "vge/service/Service.hpp"



namespace vge
{

namespace engine
{



Engine::Engine()
:	//m_constructorTime(),
	m_drawingSurfaceSize(0, 0),
	m_camera( 0 ),
	m_paintService( new vge::service::Painter() ),
	m_trace( false )
{
	m_viewport.setInvalid();
	m_nearFar.setInvalid();
	m_bufferUsagePolicy	= BUP_NOT_DEFINED;
	m_eyeUsagePolicy	= vgd::node::Camera::DEFAULT_EYEUSAGEPOLICY;

	reset();
}



void Engine::reset()
{
	// Handlers
	resetHandlers();

	//
	resetEval();
}



void Engine::resetEval()
{
	// States
	resetStateStack();

	// Matrices
	resetMatrices();

	// Built-in state
	// m_drawingSurfaceSize
	m_camera = 0;
	m_viewport.setInvalid();
	m_nearFar.setInvalid();
	m_bufferUsagePolicy	= BUP_DEFAULT;
	m_eyeUsagePolicy	= vgd::node::Camera::DEFAULT_EYEUSAGEPOLICY;
}



void Engine::evaluate(	const vgd::Shp< vge::service::Service > service,
						vgd::node::Node * node, 
						const bool isPreTraverse,
						const bool bTrace )
{
	const int32 indexService( service->getClassIndex() );
	const int32 indexNode	( node->getClassIndex() );

	if ( m_regarded[indexNode] )
	{
		vge::handler::Handler *pHandler( m_dispatch[indexService][indexNode].get() );

		// Calling handler
		if ( pHandler )
		{
			if ( isPreTraverse )
			{
				// pretraverse
				//vgDebug::get().logTrace( "preTraverse %s", node->getName().c_str() );
				pHandler->apply( this, node );
			}
			else
			{
				// posttraverse
				//vgDebug::get().logTrace( "postTraverse %s", node->getName().c_str() );
				pHandler->unapply( this, node );
			}
		}
		// else no installed handler for this node

		// Trace if desired
		if ( m_trace && bTrace && isPreTraverse )
		{
			setStateStackTop( node );
		}
		// else nothing to do
	}
	// else nothing to do, handler not regarded.
}



void Engine::evaluate(	const vgd::Shp< vge::service::Service > service,
						const vge::visitor::TraverseElement & element,
						const bool bTrace )
{
	evaluate( service, element.first, element.second, bTrace );
}



void Engine::evaluate(	const vgd::Shp< vge::service::Service > service,
						vgd::Shp< vgd::node::Node > node,
						const bool isPreTraverse,
						const bool bTrace )
{
	evaluate( service, node.get(), isPreTraverse, bTrace );
}



void Engine::paint( const vge::visitor::TraverseElement & element, const bool bTrace )
{
	evaluate( m_paintService, element, bTrace );
}



void Engine::paint(		vgd::Shp< vgd::node::Node > node,
						const bool isPreTraverse,
						const bool bTrace )
{
	evaluate( m_paintService, node.get(), isPreTraverse, bTrace );
 }



void Engine::evaluate(	const vgd::Shp< vge::service::Service > service,
						vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2,
						const bool isPreTraverse,
						const bool bTrace )
{
	evaluate( service, node1, isPreTraverse, bTrace );
	evaluate( service, node2, isPreTraverse, bTrace );
}



void Engine::paint2( vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2,
					const bool isPreTraverse,
					const bool bTrace )
{
	evaluate( m_paintService, node1, node2, isPreTraverse, bTrace );
}



void Engine::evaluate(	const vgd::Shp< vge::service::Service > service,
						vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2, vgd::Shp< vgd::node::Node > node3,
						const bool isPreTraverse,
						const bool bTrace )
{
	evaluate( service, node1, isPreTraverse, bTrace );
	evaluate( service, node2, isPreTraverse, bTrace );
	evaluate( service, node3, isPreTraverse, bTrace );
}



void Engine::paint3( vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2, vgd::Shp< vgd::node::Node > node3,
					const bool isPreTraverse,
					const bool bTrace )
{
	evaluate( m_paintService, node1, node2, node3, isPreTraverse, bTrace );
}



void Engine::setTrace( const bool trace )
{
	m_trace = trace;
}



const bool Engine::isTraceEnabled() const
{
	return m_trace;
}



void Engine::resetHandlers()
{
	clearHandlers();
	initializeHandlers();
}



void Engine::clearHandlers()
{
	// STEP 1: clear dispatch matrix and adjust its size.
	
	// Update services.
	m_dispatch.clear();
	m_dispatch.resize( vge::service::Service::getClassRegistry().getNumRegistered() );

	// For each service, do an update of the handlers size.
	vgd::basic::ClassRegistry<vgd::node::Node>&	nodeRegistry(	vgd::node::Node::getClassRegistry() );
	
	for(	DispatchMatrix::iterator	i	= m_dispatch.begin(),
										ie	= m_dispatch.end();
			i != ie;
			++i )
	{
		DispatchRow& handlers = *i;
		handlers.resize( nodeRegistry.getNumRegistered() );
	}
	
	// STEP 2: clear regarded vector and adjust its size.
	m_regarded.clear();
	m_regarded.resize( nodeRegistry.getNumRegistered() );
}



void Engine::initializeHandlers()
{
	// STEP 1: fill dispatch matrix with handlers founded in HandlerRegistry.
	vge::handler::HandlerRegistry& handlerRegistry(	vge::handler::Handler::getClassRegistry() );

	// For each handler in registry, do install().
	vge::handler::HandlerRegistry::HandlersSet::iterator i_handler;
	vge::handler::HandlerRegistry::HandlersSet::iterator ie_handler;

	for(	boost::tie( i_handler, ie_handler ) = handlerRegistry.getIterators();
			i_handler != ie_handler;
			i_handler++ )
	{
		vgd::Shp<vge::handler::Handler> handler = *i_handler;
		
		install( handler );
	}
	
	// STEP 2: all nodes must be regarded (i.e. evaluate for all services).
	regard();
}



void Engine::install( vgd::Shp< vge::handler::Handler > shpHandler )
{
	const vge::service::List					services = shpHandler->getServices();
	const vge::handler::Handler::TargetVector	targets	= shpHandler->getTargets();
	
	// For each services, do
	vge::service::List::const_iterator i, ie;
	for(	i = services.begin(), ie = services.end();
			i != ie;
			++i )
	{
		vgd::Shp< vge::service::Service > shpService = *i;
		
		int32		serviceIndex(	shpService->getClassIndex() );

		assert( serviceIndex >= 0 );
		assert( serviceIndex < static_cast<int32>(m_dispatch.size()) );
		
		// for each target, do
		vge::handler::Handler::TargetVector::const_iterator iT, ieT;
		for(	iT = targets.begin(), ieT = targets.end();
				iT != ieT;
				++iT )
		{
			int32		target;
			target =	*iT;
			
			assert( target >= 0 );
			assert( target < static_cast<int32>(m_dispatch[serviceIndex].size()) );
			m_dispatch[ serviceIndex ][ target ] = shpHandler;
		}
	}
}



void Engine::regard( const bool enabled )
{
	for(	uint32		i		= 0,
						iEnd	= static_cast<uint32>(m_regarded.size());
			i != iEnd;
			++i )
	{
		m_regarded[ i ] = enabled;
	}
}



void Engine::disregard(  const bool disabled )
{
	for(	uint32		i		= 0,
						iEnd	= static_cast<uint32>(m_regarded.size());
			i != iEnd;
			++i )
	{
		m_regarded[ i ] = !disabled;
	}
}






void Engine::resetStateStack()
{
	if ( isTraceEnabled() )
	{
		clearStateStack();
		initializeStateStack();
	}
}



void Engine::clearStateStack()
{
	// STEP 1 : reset the stack of states.
	m_state.clear();
	m_state.reserve( StateStack_SizeHint );
	m_state.resize(1);

	resetState( m_state[0] );
}



void Engine::initializeStateStack()
{
	// STEP 2 : Initialize the top of the stack with nodes founded in vgd node registry (node with all fields initialized
	// to theirs defaults values).
	vgd::basic::ClassRegistry< vgd::node::Node >& nodeRegistry(	vgd::node::Node::getClassRegistry() );
	
	vgd::basic::ClassRegistry< vgd::node::Node >::ClassSet::iterator i, iend;
	for(	boost::tie( i, iend ) = nodeRegistry.getIterators();
			i != iend;
			++i )
	{
		vgd::Shp< vgd::node::Node > node = *i;

		setStateStackTop( node.get() );
	}
}



void Engine::resetState( State& state ) const
{
	state.clear();
	
	state.resize( vgd::node::Node::getClassRegistry().getNumRegistered() );
}



bool Engine::isStateStackEmpty() const
{
	return ( m_state.size() == 0 );
}



const uint Engine::sizeOfStateStack() const
{
	// state stack is disabled. @todo removes all call to this method

	if ( isTraceEnabled() )
	{
		return static_cast<uint32>(m_state.size());
	}
	else
	{
		return 1;
	}
}



void Engine::setStateStackTop( vgd::node::Node *pNode )
{
	State& 				topState					( m_state.back() );
	
	const int32			indexNode				( pNode->getClassIndex() );
	MultiState&			multiState				( topState[indexNode] );
	
	const int32			indexMultiAttribute	( pNode->getMultiAttributeIndex() );

	std::pair< MultiState::iterator, bool >
			retVal = multiState.insert( MultiStatePair(indexMultiAttribute, NodeList()) );

	MultiState::iterator& multiStateIter = retVal.first;
	multiStateIter->second.push_back( pNode );
}



void Engine::pushStateStack()
{
	if ( isTraceEnabled() )
	{
		State& top( m_state.back() );
		m_state.push_back( top );
	}
	// else nothing to do
}



bool Engine::popStateStack()
{
	if ( isTraceEnabled() )
	{
		if ( m_state.size() > 0 )
		{
			m_state.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}






void Engine::resetMatrices()
{
	getProjectionMatrix().resize( 1 );
	getProjectionMatrix().setMatrixStackSizeHint( 8 );

// @todo size of 0, 1 or 2 by default and resize/add at runtime if needed
	getTextureMatrix().resize( getMaxTexUnits() );
	getTextureMatrix().setMatrixStackSizeHint( 8 );

	getGeometricalMatrix().resize( 1 );
	getGeometricalMatrix().setMatrixStackSizeHint( 8 );
}



MultiMatrixStack& Engine::getProjectionMatrix()
{
	return m_projections; 
}



MultiMatrixStack& Engine::getGeometricalMatrix()
{
	return m_geometricals;
}



MultiMatrixStack& Engine::getTextureMatrix()
{
	return m_textures;
}



const vgd::basic::TimeDuration Engine::getElapsedTime() const
{
	return m_constructorTime.getElapsedTime();
}



const vgm::Vec2i Engine::getDrawingSurfaceSize() const
{
	return m_drawingSurfaceSize;
}

void Engine::setDrawingSurfaceSize( const vgm::Vec2i drawingSurfaceSize )
{
	m_drawingSurfaceSize = drawingSurfaceSize;
}


const vgd::node::Camera * Engine::getCamera() const
{
	return m_camera;
}

void Engine::setCamera( const vgd::node::Camera * camera )
{
	m_camera = camera;
}


const vgm::Rectangle2i& Engine::getViewport() const
{
	return m_viewport;
}

void Engine::setViewport( const vgm::Rectangle2i& viewport )
{
	m_viewport = viewport;
}


const vgm::Vec2f Engine::getNearFar() const
{
	return m_nearFar;
}

void Engine::setNearFar( const vgm::Vec2f nearFar )
{
	m_nearFar = nearFar;
}


const BufferUsagePolicy Engine::getBufferUsagePolicy() const
{
	return m_bufferUsagePolicy;
}


void Engine::setBufferUsagePolicy( const BufferUsagePolicy policy )
{
	m_bufferUsagePolicy = policy;
}



const EyeUsagePolicy Engine::getEyeUsagePolicy() const
{
	return m_eyeUsagePolicy;
}


void Engine::setEyeUsagePolicy( const EyeUsagePolicy policy )
{
	m_eyeUsagePolicy = policy;
}



void Engine::push()
{
	pushStateStack();

	getGeometricalMatrix().pushAll();
	getProjectionMatrix().pushAll();
	getTextureMatrix().pushAll();
}


void Engine::pop()
{
	getTextureMatrix().popAll();
	getProjectionMatrix().popAll();
	getGeometricalMatrix().popAll();

	popStateStack();
}



bool Engine::addField( vgd::field::AbstractField* pField )
{
	return ( vgd::field::FieldManager::addField( pField ) );
}



const int32 Engine::StateStack_SizeHint		= 1;



} // namespace engine

} // namespace vge
