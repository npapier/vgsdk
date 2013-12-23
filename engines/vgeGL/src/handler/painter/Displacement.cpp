// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Displacement.hpp"

#include <vgd/node/Displacement.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Displacement );



const Displacement::TargetVector Displacement::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::Displacement::getClassIndexStatic() );

	return targets;
}


void Displacement::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::Displacement* >(node) != 0 );
	vgd::node::Displacement *displacement = dynamic_cast< vgd::node::Displacement* >(node);


	// Retrieves GLSL state
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = glEngine->getGLSLState();


	// Updates GLSL state
	if ( glslState.isDisabled(vgeGL::engine::DISPLACEMENT) )
	{
		glslState.setEnabled(vgeGL::engine::DISPLACEMENT);

		static const std::string uniforms = "// displacement\n"
											"uniform vec4 uDisplacementParameter4f0;\n"
											"uniform vec4 uDisplacementParameter4f1;\n";
		glslState.appendShaderStage( GLSLState::UNIFORM_DECLARATIONS, uniforms );
	}

	// VERTEX SHADER PART
	static std::string displacementAlongNormalVS = "position += uDisplacementParameter4f0.x * vec4(normal,0);\n";

	vgd::node::Displacement::PredefinedDisplacementValueType function;
	const bool hasDisplacementFunctionVS = displacement->getDisplacementFunctionVS( function );

	if ( hasDisplacementFunctionVS )
	{
		switch ( function.value() )
		{
			case vgd::node::Displacement::NONE:
				glslState.resetShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT );
				break;

			case vgd::node::Displacement::ALONG_NORMAL:
				glslState.setShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementAlongNormalVS );
				break;

			case vgd::node::Displacement::CUSTOM:
			{
				//	declarationsVS
				const std::string& declarationsVSStr = displacement->getDeclarationsVS();
				if ( declarationsVSStr.size() > 0 )
				{
					glslState.setShaderStage( GLSLState::VERTEX_DECLARATIONS, declarationsVSStr );
				}

				//	displacementVS
				const std::string& displacementVSStr = displacement->getDisplacementVS();
				if ( displacementVSStr.size() > 0 )
				{
					glslState.setShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementVSStr );
				}
			}
			break;

			default:
				vgAssertN( false, "Unknown value for displacement.displacementFunctionVS field %i", function.value() );
		}
	}
	// else do nothing


	// TESSELLATION EVALUATION SHADER PART
	static std::string displacementAlongNormalTES = "position += uDisplacementParameter4f0.y * vec4(ecNormal,0);\n";

	const bool hasDisplacementFunctionTES = displacement->getDisplacementFunctionTES( function );

	if ( hasDisplacementFunctionTES )
	{
		switch ( function.value() )
		{
			case vgd::node::Displacement::NONE:
				glslState.resetShaderStage( GLSLState::TES_POSITION_DISPLACEMENT );
				break;

			case vgd::node::Displacement::ALONG_NORMAL:
				glslState.setShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementAlongNormalTES );
				break;

			case vgd::node::Displacement::CUSTOM:
			{
				//	declarationsTES
				const std::string& declarationsTESStr = displacement->getDeclarationsTES();
				if ( declarationsTESStr.size() > 0 )
				{
					glslState.setShaderStage( GLSLState::TES_DECLARATIONS, declarationsTESStr );
				}

				//	displacementTES
				const std::string& displacementTESStr = displacement->getDisplacementTES();
				if ( displacementTESStr.size() > 0 )
				{
					glslState.setShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementTESStr );
				}
			}
			break;

			default:
				vgAssertN( false, "Unknown value for displacement.displacementFunctionTES field %i", function.value() );
		}
	}
	// else do nothing


	// Updates uniforms
	//	parameter4f0
	vgd::node::Displacement::Parameter4f0ValueType parameter4f0;
	const bool hasParameter4f0 = displacement->getParameter4f0( parameter4f0 );

	if ( hasParameter4f0 )		glEngine->getBuiltinUniformState().sethUniform( "uDisplacementParameter4f0", parameter4f0 );

	//	parameter4f1
	vgd::node::Displacement::Parameter4f0ValueType parameter4f1;
	const bool hasParameter4f1 = displacement->getParameter4f1( parameter4f1 );

	if ( hasParameter4f1 )		glEngine->getBuiltinUniformState().sethUniform( "uDisplacementParameter4f1", parameter4f1 );
}



void Displacement::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void Displacement::setToDefaults()
{
	// nothing to do
}



} // namespace basic

} // namespace handler

} // namespace vgeGL
