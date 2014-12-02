//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/SurroundScale.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/SurroundScale.hpp>
//#include <vge/handler/SurroundScale.hpp>
//#include <vge/service/Painter.hpp>
//#include <vge/service/ProcessEvent.hpp>
//#include <vgm/Utilities.hpp>
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
//META_HANDLER_CPP( SurroundScale );
//
//
//
//const vge::service::List SurroundScale::getServices() const
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
//const vge::handler::Handler::TargetVector SurroundScale::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::SurroundScale::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void SurroundScale::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(pEngine) != 0 );
//	vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::SurroundScale* >(pNode) != 0 );
//	vgd::node::SurroundScale *pCastedNode = dynamic_cast< vgd::node::SurroundScale* >(pNode);
//
//	vge::handler::SurroundScale::apply( pEngine, pCastedNode );
//
//	paint( pGLEngine, pCastedNode );
//}
//
//
//
//void SurroundScale::unapply ( vge::engine::Engine* , vgd::node::Node* )
//{
//}
//
//
//
///**
// * @todo What to set/unset in this method ?
// */
//void SurroundScale::setToDefaults()
//{
//}
//
//
//
//void SurroundScale::paint( vgeGLBase::engine::Engine *pGLEngine, vgd::node::SurroundScale *pNode )
//{
//	// GEOMETRICAL MATRIX
//	// Gets the transformation
//	vgm::MatrixR& 		current(	
//		pGLEngine->getGeometricalMatrix().getTop() 
//		);
//
//	glMatrixMode( GL_MODELVIEW );
//
//	// Updates OpenGL
//	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
//
//	// Validates node
//	pNode->getDirtyFlag(pNode->getDFNode())->validate();
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