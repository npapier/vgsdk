//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Transform.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/Transform.hpp>
//#include <vge/handler/Transform.hpp>
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
//META_HANDLER_CPP( Transform );
//
//
//
//const vge::service::List Transform::getServices() const
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
//const vge::handler::Handler::TargetVector Transform::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::Transform::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void Transform::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(pEngine) != 0 );
//	vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::Transform* >(pNode) != 0 );
//	vgd::node::Transform *pCastedNode = dynamic_cast< vgd::node::Transform* >(pNode);
//
//	vge::handler::Transform::apply( pEngine, pCastedNode );
//
//	paint( pGLEngine, pCastedNode );
//}
//
//
//
//void Transform::unapply ( vge::engine::Engine* , vgd::node::Node* )
//{
//}
//
//
//
///**
// * @todo What to set/unset in this method ?
// */
//void Transform::setToDefaults()
//{
//}
//
//
//
//void Transform::paint( vgeGLBase::engine::Engine *pGLEngine, vgd::node::Transform *pNode )
//{
//	// GEOMETRICAL MATRIX
//	// Gets the transformation
//	vgm::MatrixR& current( pGLEngine->getGeometricalMatrix().getTop() );
//
//	glMatrixMode( GL_MODELVIEW );
//
//	// Updates OpenGL
//	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
//
//	// Validates node
//	pNode->getDirtyFlag(pNode->getDFNode())->validate();
//
//// OpenGL version
////	glMatrixMode( GL_MODELVIEW );
////	if ( !pTransform->getComposeMatrix() )
////	{
////		glLoadIdentity();
////	}
////	//else nothing to do.
////
////	// T * C * R * Sorientation * Sfactor * -Sorientation * -C
////	vgm::Vec3f	translation 		= pTransform->getTranslation();
////	glTranslatef( translation[0], translation[1], translation[2] );
////	
////	const vgm::Vec3f	center		= pTransform->getCenter();
////	glTranslatef( center[0], center[1], center[2] );
////	
////	vgm::Rotation	rotation	= pTransform->getRotation();
////	vgm::Vec3f	axis;
////	float		angle;
////	rotation.getValue( axis, angle );
////	angle = vgm::Utilities::rad2deg( angle );
////	glRotatef( angle, axis[0], axis[1], axis[2] );
////	
////	rotation						= pTransform->getScaleOrientation();
////	rotation.getValue( axis, angle );
////	angle = vgm::Utilities::rad2deg( angle );
////	glRotatef( angle, axis[0], axis[1], axis[2] );
////	
////	vgm::Vec3f scaleFactor			= pTransform->getScaleFactor();
////	glScalef( scaleFactor[0], scaleFactor[1], scaleFactor[2] );
////	
////	glRotatef( -angle, axis[0], axis[1], axis[2] );
////	
////	glTranslatef( -center[0], -center[1], -center[2] );
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