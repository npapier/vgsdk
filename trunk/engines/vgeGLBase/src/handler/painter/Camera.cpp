//// VGSDK - Copyright (C) 2004, 2008, 2009, 2010, 2011, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Camera.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/Camera.hpp>
//#include "vge/service/ComputeBoundingBox.hpp"
//#include <vge/service/Painter.hpp>
//#include <vge/service/ProcessEvent.hpp>
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
//META_HANDLER_CPP( Camera );
//
//
//
//const vge::service::List Camera::getServices() const
//{
//	vge::service::List list;
//
//	list.push_back( vge::service::Painter::create()				);
//	list.push_back( vge::service::ProcessEvent::create()		);
//
//	return list;
//}
//
//
//
//const vge::handler::Handler::TargetVector Camera::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::Camera::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void Camera::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::Camera* >(node) != 0 );
//	vgd::node::Camera *pCastedNode = dynamic_cast< vgd::node::Camera* >(node);
//
//	vge::handler::Camera::apply( engine, pCastedNode );
//
//	// Updates engine state
//	if ( glEngine->isGLSLEnabled() )
//	{
//		// random
//		glEngine->setUniformRandom();
//
//		// time
//		glEngine->setUniformTime();
//
//		// nearFar and viewport
//		glEngine->setUniformNearFarAndViewport();
//	}
//
//	paint( glEngine, pCastedNode );
//}
//
//
//
//void Camera::unapply ( vge::engine::Engine*, vgd::node::Node*)
//{
//}
//
//
//void Camera::setToDefaults()
//{
////	glMatrixMode( GL_PROJECTION );
////	glLoadIdentity();
////
////	glMatrixMode( GL_MODELVIEW );
////	glLoadIdentity();
////	
////	glDisable( GL_SCISSOR_TEST );
//}
//
//
//
//void Camera::paint( vgeGLBase::engine::Engine *engine, vgd::node::Camera *node )
//{
//	const vge::engine::EyeUsagePolicy eyePolicy = engine->getEyeUsagePolicy();
//
//	// PROJECTION MATRIX
//	// Gets the transformation
//	vgm::MatrixR& currentProj = engine->getProjectionMatrix().getTop();
//
//	glMatrixMode( GL_PROJECTION );
//
//	// Updates OpenGL
//	glLoadMatrixf( reinterpret_cast<const float*>( currentProj.getValue() ) );
//
//
//
//	// GEOMETRICAL MATRIX
//	// Gets the transformation
//	vgm::MatrixR& currentGeom = engine->getGeometricalMatrix().getTop();
//
//	glMatrixMode( GL_MODELVIEW );
//
//	// Updates OpenGL
//	glLoadMatrixf( reinterpret_cast<const float*>( currentGeom.getValue() ) );
//
//
//
//	// VIEWPORT
//	const vgm::Rectangle2i& viewportValue = engine->getViewport();
//
//	glViewport(	viewportValue.x(), viewportValue.y(),
//				viewportValue.width(), viewportValue.height() );
//
//
//
//	// SCISSOR
//	bool bDefined;
//	vgm::Rectangle2i  scissorValue;
//
//	bDefined = node->getScissor( scissorValue );
//
//	if ( bDefined )
//	{
//		glEnable( GL_SCISSOR_TEST );
//
//		glScissor(
//			scissorValue.x(), scissorValue.y(),
//			scissorValue.width(), scissorValue.height()
//				);
//	}
//	else
//	{
//		glDisable( GL_SCISSOR_TEST );
//	}
//
//	// Validates node
//	node->getDirtyFlag(node->getDFNode())->validate();
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