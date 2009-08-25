// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/engine/Engine.hpp"

#include <vgd/node/Camera.hpp>
#include <vgDebug/Global.hpp>

#include "vge/handler/Handler.hpp"
#include "vge/handler/HandlerRegistry.hpp"
#include "vge/service/Service.hpp"



namespace vge
{

namespace engine
{



Engine::Engine()
:	m_drawingSurfaceSize(0, 0),
	m_isTextureMappingEnabled(true)
{
	reset();
}



void Engine::reset()
{
	// Handlers
	resetHandlers();

	//
	setTextureMappingEnabled();

	//	
	resetEval();
}



void Engine::resetEval()
{	
	// States
	resetStateStack();
	
	// Matrices
	resetMatrices();
}



void Engine::evaluate(	const vgd::Shp< vge::service::Service >service,
						vgd::node::Node *pNode, 
						const bool isPreTraverse,
						const bool bTrace )
{
	const int32 indexService( service->getClassIndex() );
	const int32 indexNode	( pNode->getClassIndex() );
	
	if ( m_regarded[indexNode] )
	{
		vge::handler::Handler *pHandler;
		
		pHandler = m_dispatch[indexService][indexNode].get();
		
		if ( pHandler != 0 )
		{
			if ( isPreTraverse )
			{
				// pretraverse
				//vgDebug::get().logTrace( "preTraverse %s", pNode->getName().c_str() );
				if ( bTrace )
				{
					setStateStackTop( pNode );
				}
				pHandler->apply( this, pNode );
			}
			else
			{
				// posttraverse
				//vgDebug::get().logTrace( "postTraverse %s", pNode->getName().c_str() );
				pHandler->unapply( this, pNode );
			}
		}
		else
		{
			// No installed handler for this node, do nothing.
			return;
		}
	}
	// nothing to do, handler not regarded.
}



const bool Engine::isTextureMappingEnabled() const
{
	return m_isTextureMappingEnabled;
}



void Engine::setTextureMappingEnabled( const bool enabled )
{
	m_isTextureMappingEnabled = enabled;
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
	const vge::service::List						services = shpHandler->getServices();
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



void Engine::regard()
{
	for(	uint32		i		= 0,
						iEnd	= static_cast<uint32>(m_regarded.size());
			i != iEnd;
			++i )
	{
		m_regarded[ i ] = true;
	}
}



void Engine::disregard()
{
	for(	uint32		i		= 0,
						iEnd	= static_cast<uint32>(m_regarded.size());
			i != iEnd;
			++i )
	{
		m_regarded[ i ] = false;
	}
}






void Engine::resetStateStack()
{
	clearStateStack();
	initializeStateStack();
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
	return static_cast<uint32>(m_state.size());
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
	State& top(	m_state.back()	);
	
	m_state.push_back( top );
}



bool Engine::popStateStack()
{
	if ( m_state.size() > 0 )
	{
		m_state.pop_back();
		return ( true );
	}
	else
	{
		return ( false );
	}
}






void Engine::resetMatrices()
{
	getProjectionMatrix().resize(	1 );
	//getProjectionMatrix().setMatrixStackSizeHint( 1 );
											
	getTextureMatrix().resize( getMaxTexUnits() );
	//getTextureMatrix().setMatrixStackSizeHint( 1 );

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



const vgm::Vec2i Engine::getDrawingSurfaceSize() const
{
	return m_drawingSurfaceSize;
}



void Engine::setDrawingSurfaceSize( const vgm::Vec2i drawingSurfaceSize )
{
	m_drawingSurfaceSize = drawingSurfaceSize;
}



const vgm::Rectangle2i Engine::getViewport() const
{
	vgm::Rectangle2i viewport;

	using vgd::node::Camera;
	const bool retVal = getStateStackTop< Camera, Camera::ViewportValueType >(
		Camera::getFViewport(), viewport );
	assert( retVal && "Internal error, because getStateStackTop<>() should never fail." );

	return viewport;
}



const int32 Engine::getMaxTexUnits() const
{ 
	return 0;
};



bool Engine::addField( vgd::field::AbstractField* pField )
{
	return ( vgd::field::FieldManager::addField( pField ) );
}



const int32 Engine::StateStack_SizeHint		= 4;



} // namespace engine

} // namespace vge
