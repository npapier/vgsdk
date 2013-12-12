// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/TessellationLevel.hpp"

#include <vgd/node/TessellationLevel.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( TessellationLevel );



const TessellationLevel::TargetVector TessellationLevel::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::TessellationLevel::getClassIndexStatic() );

	return targets;
}


void TessellationLevel::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::TessellationLevel* >(node) != 0 );
	vgd::node::TessellationLevel *tessLevel = dynamic_cast< vgd::node::TessellationLevel* >(node);

	// Retrieves GLSL state
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = glEngine->getGLSLState();


	// Updates GLSL state
	if ( glslState.isDisabled(vgeGL::engine::TESSELLATION_LEVEL) )
	{
		glslState.setEnabled(vgeGL::engine::TESSELLATION_LEVEL);

		static const std::string uniforms = "// tessellation level\n"
											"uniform vec4 uTessLevelParameter4f0;\n"
											"uniform vec4 uTessLevelParameter4f1;\n";
		glslState.appendShaderStage( GLSLState::UNIFORM_DECLARATIONS, uniforms );
	}

	// TESSELLATION CONTROL SHADER PART
	//	methods:
	//		UNIFORM see TessellationControlShaderGenerator FUNCTIONS section
	//		PIXELS_PER_EDGE see TessellationControlShaderGenerator FUNCTIONS section
	switch ( tessLevel->getMethod().value() )
	{
		case vgd::node::TessellationLevel::UNIFORM:
			glslState.resetShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION );
			break;

		case vgd::node::TessellationLevel::PIXELS_PER_EDGE:
			glslState.setShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, "	tessellationLevelMethodPIXELS_PER_EDGE(tessLevelOuter, tessLevelInner );\n" );
			break;

		case vgd::node::TessellationLevel::CUSTOM:
		{
			//	customDeclarations
			const std::string& declarationsStr = tessLevel->getCustomDeclarations();
			if ( declarationsStr.size() > 0 )	glslState.setShaderStage( GLSLState::TCS_DECLARATIONS, declarationsStr );

			//	customMethod
			const std::string& customCodeStr = tessLevel->getCustomCode();
			if ( customCodeStr.size() > 0 )	glslState.setShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, customCodeStr );
		}
		break;

		default:
			vgAssertN( false, "Unknown value for tessellationLevel.method field %i", tessLevel->getMethod().value() );
	}


	// Updates uniforms

	//	parameter4f0
	vgd::node::TessellationLevel::Parameter4f0ValueType parameter4f0;
	const bool hasParameter4f0 = tessLevel->getParameter4f0( parameter4f0 );

	if ( hasParameter4f0 )
	{
		glEngine->getUniformState().sethUniform( "uTessLevelParameter4f0", parameter4f0 );
	}

	//	parameter4f1
	vgd::node::TessellationLevel::Parameter4f0ValueType parameter4f1;
	const bool hasParameter4f1 = tessLevel->getParameter4f1( parameter4f1 );

	if ( hasParameter4f1 )
	{
		glEngine->getUniformState().sethUniform( "uTessLevelParameter4f1", parameter4f1 );
	}
}



void TessellationLevel::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void TessellationLevel::setToDefaults()
{
	// nothing to do
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
