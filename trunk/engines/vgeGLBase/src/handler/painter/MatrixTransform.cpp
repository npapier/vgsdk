//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/MatrixTransform.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/MatrixTransform.hpp>
//#include <vge/handler/MatrixTransform.hpp>
//#include <vge/service/Painter.hpp>
//#include <vge/service/ProcessEvent.hpp>
//
//#include "vgeGL/engine/Engine.hpp"
//
//
//
//namespace vgeGL
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
//META_HANDLER_CPP( MatrixTransform );
//
//
//
//const vge::service::List MatrixTransform::getServices() const
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
//const vge::handler::Handler::TargetVector MatrixTransform::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::MatrixTransform::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void MatrixTransform::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::MatrixTransform* >(pNode) != 0 );
//	vgd::node::MatrixTransform *pCastedNode = dynamic_cast< vgd::node::MatrixTransform* >(pNode);
//
//	vge::handler::MatrixTransform::apply( pEngine, pCastedNode );
//
//	paint( pGLEngine, pCastedNode );
//}
//
//
//
//void MatrixTransform::unapply ( vge::engine::Engine* , vgd::node::Node*  )
//{
//}
//
//
//
//void MatrixTransform::setToDefaults()
//{
//	glMatrixMode( GL_MODELVIEW );
//	glLoadIdentity();
//}
//
//
//
//void MatrixTransform::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::MatrixTransform *pNode )
//{
//	// GEOMETRICAL MATRIX
//	// Gets the transformation.
//	vgm::MatrixR& current( pGLEngine->getGeometricalMatrix().getTop() );
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
//} // namespace vgeGL
//