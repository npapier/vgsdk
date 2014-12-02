//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Kits.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/NullDragger.hpp>
//#include <vgd/node/Scale1Dragger.hpp>
//#include <vgd/node/TransformDragger.hpp>
//#include <vge/service/Painter.hpp>
//
//#include "vgeGLBase/engine/Engine.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace handler
//{
//
//namespace painter
//{
//
//
//
//META_HANDLER_CPP( Kits );
//
//
//
//const vge::service::List Kits::getServices() const
//{
//	vge::service::List list;
//	
//	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );
//
//	return ( list );
//}
//
//
//
//const vge::handler::Handler::TargetVector Kits::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//	
//	targets.reserve(3);
//
//	targets.push_back( vgd::node::NullDragger::getClassIndexStatic() );
//	targets.push_back( vgd::node::Scale1Dragger::getClassIndexStatic() );
//	targets.push_back( vgd::node::TransformDragger::getClassIndexStatic() );		
//
//	return ( targets );
//}
//
//
//
//void Kits::apply ( vge::engine::Engine*, vgd::node::Node *pNode )
//{
//	//assert( dynamic_cast< vgeGLBase::engine::Engine* >(pEngine) != 0 );
//	//vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::Kit* >(pNode) != 0 );
//	//vgd::node::Kit *pCastedNode = static_cast< vgd::node::Kit* >(pNode);
//
//	// Validate node
//	pNode->getDirtyFlag(pNode->getDFNode())->validate();
//}										
//
//
//
//void Kits::unapply ( vge::engine::Engine* , vgd::node::Node* )
//{
//}
//
//
//
///**
// * @todo What to set/unset in this method ?
// */
//void Kits::setToDefaults()
//{
//}
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGLBase
//