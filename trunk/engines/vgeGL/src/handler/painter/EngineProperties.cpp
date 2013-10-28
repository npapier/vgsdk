// VGSDK - Copyright (C) 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/EngineProperties.hpp"

#include <vgd/node/EngineProperties.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( EngineProperties );



const vge::service::List EngineProperties::getServices() const
{
	vge::service::List list;

	list.push_back( vge::service::Painter::create() );

	return list;
}



/*const Handler::TargetVector EngineProperties::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::EngineProperties::getClassIndexStatic() );

	return targets;
}*/


void EngineProperties::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	vge::handler::basic::EngineProperties::apply( engine, node );

	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::EngineProperties* >(node) != 0 );
	vgd::node::EngineProperties *engineProperties = dynamic_cast< vgd::node::EngineProperties* >(node);

	// Retrieves GLSL state
	using vgeGL::engine::GLSLState;
	GLSLState& state = glEngine->getGLSLState();

	// TESSELLATION
	const bool hasTessellation = engineProperties->getTessellation();
	state.setTessellationEnabled( hasTessellation );
	if ( hasTessellation )
	{
		const vgd::node::EngineProperties::TessellationFactorValueType	tessellationValue	= engineProperties->getTessellationFactor();
		glEngine->getUniformState().addUniform( "tessValue", tessellationValue );

		const vgd::node::EngineProperties::TessellationBiasValueType	tessellationBias	= engineProperties->getTessellationBias();
		glEngine->getUniformState().addUniform( "tessBias", tessellationBias );
	}
}



void EngineProperties::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void EngineProperties::setToDefaults()
{
	// TESSELLATION
	if ( isGL_ARB_tessellation_shader() )
	{
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		GLfloat level[] = { 3.f, 3.f, 3.f };
		glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, level);
		glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, level);
	}
}



} // namespace basic

} // namespace handler

} // namespace vge
