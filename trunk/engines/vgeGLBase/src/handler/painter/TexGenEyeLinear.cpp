//// VGSDK - Copyright (C) 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/TexGenEyeLinear.hpp"
//
//#include <vgd/node/TexGenEyeLinear.hpp>
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
//META_HANDLER_CPP( TexGenEyeLinear );
//
//
//
//const vge::handler::Handler::TargetVector TexGenEyeLinear::getTargets() const
//{
//	TargetVector targets;
//
//	targets.reserve( 1 );
//	targets.push_back( vgd::node::TexGenEyeLinear::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void TexGenEyeLinear::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
//	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::TexGenEyeLinear* >(node) != 0 );
//	vgd::node::TexGenEyeLinear *texGen = static_cast< vgd::node::TexGenEyeLinear* >(node);
//
//	TexGen::apply( glEngine, texGen );
//
//	if ( glEngine->isTextureMappingEnabled() )
//	{
//		vgeGL::rc::applyUsingDisplayList< vgd::node::TexGenEyeLinear, TexGenEyeLinear >( engine, node, this );
//	}
//}
//
//
//
//void TexGenEyeLinear::unapply ( vge::engine::Engine*, vgd::node::Node* )
//{
//}
//
//
//
//void TexGenEyeLinear::setToDefaults()
//{
//}
//
//
//
//void TexGenEyeLinear::paint( vgeGL::engine::Engine * engine, vgd::node::TexGenEyeLinear * node )
//{
//	// PARAMETERS
//	if ( node->hasParameters() )
//	{
//		vgd::node::TexGenEyeLinear::ParametersValueType parameters;
//		/*isDefined = */node->getParameters( parameters );
//
//		// Activates the desired texture unit
//		const int texUnit = node->getMultiAttributeIndex();
//		engine->activeTexture( texUnit );
//
//		TexGen::paint( engine, node );
//		TexGen::paint( GL_EYE_LINEAR, GL_EYE_PLANE, parameters );
//	}
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