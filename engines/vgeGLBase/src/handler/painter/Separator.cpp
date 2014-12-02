//// VGSDK - Copyright (C) 2004, 2009, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Separator.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/Separator.hpp>
//#include <vge/service/Painter.hpp>
//#include <vge/service/ProcessEvent.hpp>
//
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/engine/GLSLState.hpp"
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
//META_HANDLER_CPP( Separator );
//
//
//
//const vge::service::List Separator::getServices() const
//{
//	vge::service::List list;
//
//	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );
//	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::ProcessEvent) );
//
//	return list;
//}
//
//
//
//const vge::handler::Handler::TargetVector Separator::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::Separator::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
///**
// * @todo Check overflow in stack.
// */
//void Separator::apply( vge::engine::Engine* engine, vgd::node::Node *node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	//assert( dynamic_cast< vgd::node::Separator* >(node) != 0 );
//	//vgd::node::Separator *separator = static_cast< vgd::node::Separator* >(node);
//
//	//
//	//vge::handler::Separator::apply( engine, separator );
//	glEngine->getGLStateStack().push();
//	glEngine->pushGLSLState();
//	// Push OpenGL part.
//	glPushAttrib( GL_ALL_ATTRIB_BITS );
//
//	// Validates node
//	node->getDirtyFlag(node->getDFNode())->validate();
//}
//
//
//
//void Separator::unapply ( vge::engine::Engine* engine, vgd::node::Node* node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	//assert( dynamic_cast< vgd::node::Separator* >(node) != 0 );
//	//vgd::node::Separator *separator = static_cast< vgd::node::Separator* >(node);
//
//	// Pop OpenGL part.
//	glPopAttrib();
//	glEngine->popGLSLState();
//	glEngine->getGLStateStack().pop();
//	//vge::handler::Separator::unapply( glEngine, separator );
//}
//
//
//
//void Separator::setToDefaults()
//{
//	// Nothing to do
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