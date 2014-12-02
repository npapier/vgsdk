//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/TessellationProperties.hpp"
//
//#include <vgd/node/TessellationProperties.hpp>
//#include <vge/service/Painter.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/engine/GLSLState.hpp"
//#include <gle/OpenGLExtensionsGen.hpp>
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
//META_HANDLER_CPP( TessellationProperties );
//
//
//
//const TessellationProperties::TargetVector TessellationProperties::getTargets() const
//{
//	TargetVector targets;
//
//	targets.push_back( vgd::node::TessellationProperties::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//void TessellationProperties::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::TessellationProperties* >(node) != 0 );
//	vgd::node::TessellationProperties *tessProperties = dynamic_cast< vgd::node::TessellationProperties* >(node);
//
//
//	// Retrieves GLSL state
//	using vgeGLBase::engine::GLSLState;
//	GLSLState& state = glEngine->getGLSLState();
//
//
//	//	tessellation
//	vgd::node::TessellationProperties::TessellationValueType tessellationValue;
//	const bool hasTessellation = tessProperties->getTessellation( tessellationValue );
//
//	if ( hasTessellation )
//	{
//		state.setTessellationEnabled( tessellationValue != vgd::node::TessellationProperties::DISABLED );
//		state.setTessellation( tessellationValue );
//	}
//
//	//	phongBias
//	vgd::node::TessellationProperties::PhongBiasValueType phongBias;
//	const bool hasPhongBias = tessProperties->getPhongBias( phongBias );
//
//	if ( hasPhongBias )		glEngine->getBuiltinUniformState().sethUniform( "tessPhongBias", phongBias );
//
//	//	tessellationRange
//	vgd::node::TessellationProperties::RangeValueType range;
//	const bool hasRange = tessProperties->getRange( range );
//
//	if ( hasRange )			glEngine->getBuiltinUniformState().sethUniform( "tessRange", range );
//
//	//	pixelsPerEdge
//	float pixelsPerEdge;
//	const bool hasPixelsPerEdge = tessProperties->getPixelsPerEdge( pixelsPerEdge );
//
//	if ( hasPixelsPerEdge )	glEngine->getBuiltinUniformState().sethUniform( "tessPixelsPerEdge", pixelsPerEdge );
//}
//
//
//
//void TessellationProperties::unapply( vge::engine::Engine *, vgd::node::Node * )
//{
//	// nothing to do
//}
//
//
//
//void TessellationProperties::setToDefaults()
//{
//	// TESSELLATION
//	if ( isGL_ARB_tessellation_shader() )
//	{
//		glPatchParameteri(GL_PATCH_VERTICES, 3);
//
//		GLfloat innerLevel[] = { 3.f, 3.f };
//		GLfloat outerLevel[] = { 3.f, 3.f, 3.f, 3.f };
//		glPatchParameterfv( GL_PATCH_DEFAULT_INNER_LEVEL, innerLevel );
//		glPatchParameterfv( GL_PATCH_DEFAULT_OUTER_LEVEL, outerLevel );
//	}
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