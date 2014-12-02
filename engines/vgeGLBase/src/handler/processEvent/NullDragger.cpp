//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/processEvent/NullDragger.hpp"
//
//#include <vgd/node/NullDragger.hpp>
//
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/technique/ProcessEvent.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace handler
//{
//
//namespace processEvent
//{
//
//
//
//META_HANDLER_CPP( NullDragger );
//
//
//
//const vge::handler::Handler::TargetVector NullDragger::getTargets() const
//{
//	TargetVector targets;
//	
//	targets.push_back( vgd::node::NullDragger::getClassIndexStatic() );
//	
//	return ( targets );
//}
//
//
//
//void NullDragger::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
//{
//	using vgd::node::NullDragger;
//		
//	assert( dynamic_cast< NullDragger* >(pNode) != 0 );
//	NullDragger *pDragger = static_cast< NullDragger* >(pNode);
//	
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(pEngine) != 0 );
//	vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(pEngine);
//
//	//
//	Dragger::preApply( pGLEngine, pDragger );
//	Dragger::apply();
//	Dragger::postApply();
//}
//
//
//
//void NullDragger::unapply( vge::engine::Engine *, vgd::node::Node * )
//{
//}
//
//
//
//void NullDragger::setToDefaults()
//{
//}
//
//
//
//} // namespace processEvent
//	
//} // namespace handler
//
//} // namespace vge
//