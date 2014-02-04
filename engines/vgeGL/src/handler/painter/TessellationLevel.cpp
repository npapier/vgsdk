// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
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
	}


	// TESSELLATION CONTROL SHADER PART
	//	methods:
	//		UNIFORM see TessellationControlShaderGenerator FUNCTIONS section
	//		PIXELS_PER_EDGE see TessellationControlShaderGenerator FUNCTIONS section

	const vgd::field::Enum composeMode = tessLevel->getComposeMode();

	switch ( tessLevel->getMethod().value() )
	{
		// UNIFORM
		case vgd::node::TessellationLevel::UNIFORM:
			switch ( composeMode.value() )
			{
				case vgd::node::TessellationLevel::REPLACE:
					glslState.resetShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION );
					break;
				case vgd::node::TessellationLevel::PREPEND:
					glslState.prependShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, glslState.getShaderStageDefault(GLSLState::TCS_TESSLEVEL_COMPUTATION) );
					break;
				case vgd::node::TessellationLevel::APPEND:
					glslState.appendShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, glslState.getShaderStageDefault(GLSLState::TCS_TESSLEVEL_COMPUTATION) );
					break;
				default:
					vgAssertN( false, "Unexpected value for TessellationLevel.composeMode" );
			}
			break;

		// PIXELS_PER_EDGE
		case vgd::node::TessellationLevel::PIXELS_PER_EDGE:
			switch ( composeMode.value() )
			{
				case vgd::node::TessellationLevel::REPLACE:
					glslState.setShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, "	tessellationLevelMethodPIXELS_PER_EDGE(tessLevelOuter, tessLevelInner );\n" );
					break;
				case vgd::node::TessellationLevel::PREPEND:
					glslState.prependShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, "	tessellationLevelMethodPIXELS_PER_EDGE(tessLevelOuter, tessLevelInner );\n" );
					break;
				case vgd::node::TessellationLevel::APPEND:
					glslState.appendShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, "	tessellationLevelMethodPIXELS_PER_EDGE(tessLevelOuter, tessLevelInner );\n" );
					break;
				default:
					vgAssertN( false, "Unexpected value for TessellationLevel.composeMode" );
			}
			break;

		// CUSTOM
		case vgd::node::TessellationLevel::CUSTOM:
		{
			//	customDeclarations and customMethod
			const std::string& declarationsStr	= tessLevel->getCustomDeclarations();
			const std::string& customCodeStr	= tessLevel->getCustomCode();

			switch ( composeMode.value() )
			{
				case vgd::node::TessellationLevel::REPLACE:
					if ( declarationsStr.size() > 0 )	glslState.setShaderStage( GLSLState::TCS_DECLARATIONS, declarationsStr );
					if ( customCodeStr.size() > 0 )		glslState.setShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, customCodeStr );
					break;
				case vgd::node::TessellationLevel::PREPEND:
					if ( declarationsStr.size() > 0 )	glslState.prependShaderStage( GLSLState::TCS_DECLARATIONS, declarationsStr );
					if ( customCodeStr.size() > 0 )		glslState.prependShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, customCodeStr );
					break;
				case vgd::node::TessellationLevel::APPEND:
					if ( declarationsStr.size() > 0 )	glslState.appendShaderStage( GLSLState::TCS_DECLARATIONS, declarationsStr );
					if ( customCodeStr.size() > 0 )		glslState.appendShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION, customCodeStr );
					break;
				default:
					vgAssertN( false, "Unexpected value for TessellationLevel.composeMode" );
			}
			break;
		}
		break;

		default:
			vgAssertN( false, "Unknown value for tessellationLevel.method field %i", tessLevel->getMethod().value() );
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
