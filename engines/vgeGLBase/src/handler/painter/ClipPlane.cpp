//// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/ClipPlane.hpp"
//
//#include <vgd/node/ClipPlane.hpp>
//
//#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/engine/GLSLState.hpp"
//#include "vgeGL/rc/TDisplayListHelper.hpp"
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
//META_HANDLER_CPP( ClipPlane );
//
//
//
//const vge::handler::Handler::TargetVector ClipPlane::getTargets() const
//{
//	TargetVector targets;
//
//	targets.reserve( 1 );
//	targets.push_back( vgd::node::ClipPlane::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void ClipPlane::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
//	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);
//
////	assert( dynamic_cast< vgd::node::ClipPlane* >(node) != 0 );
////	vgd::node::ClipPlane *pCastedNode = static_cast< vgd::node::ClipPlane* >(node);
//
//	if ( glEngine->isGLSLEnabled() )
//	{
//		using vgeGL::engine::GLSLState;
//		glEngine->getGLSLState().setEnabled( vgeGL::engine::CLIPPING_PLANE );
//	}
//
//	vgeGL::rc::applyUsingDisplayList< vgd::node::ClipPlane, ClipPlane >( engine, node, this );
//}
//
//
//
//void ClipPlane::unapply ( vge::engine::Engine*, vgd::node::Node* )
//{
//}
//
//
//
//void ClipPlane::setToDefaults()
//{
//}
//
//
//
//void ClipPlane::paint( vgeGL::engine::Engine * engine, vgd::node::ClipPlane * node )
//{
//	const int index = GL_CLIP_PLANE0 + node->getMultiAttributeIndex();
//
//	// ON and PLANE (if ON is true)
//	vgd::node::ClipPlane::OnValueType onValue;
//
//	const bool isDefined = node->getOn( onValue );
//
//	if ( isDefined )
//	{
//		if ( onValue )
//		{
//			glEnable( index );
//
//			// PLANE
//			vgd::node::ClipPlane::PlaneValueType planeValue = node->getPlane();
//
//			vgm::Vec4d planeEquation( planeValue.getNormal() );
//			planeEquation[3] = planeValue.getDistanceFromOrigin();
//
//			glClipPlane( index, planeEquation.getValue() );
//		}
//		else
//		{
//			glDisable( index );
//		}
//	}
//	// else nothing to do
//
//	// Validates node df
//	node->getDirtyFlag(node->getDFNode())->validate();
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