// VGSDK - Copyright (C) 2012, Alexandre Di Pino, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino
// Author Nicolas Papier

#include "vgeGL/engine/TessellationControlShaderGenerator.hpp"

#include <vgd/node/Program.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{


TessellationControlShaderGenerator::TessellationControlShaderGenerator()
:	ShaderGenerator( glo::GLSLProgram::TESSELLATION_CONTROL )
{}



const bool TessellationControlShaderGenerator::generate( vgeGL::engine::Engine * engine )
{
	// Retrieves the GLSL state
	GLSLState& state = engine->getGLSLState();

	// Clears the code repository
	m_decl.clear();
	m_code1.clear();
	m_code2.clear();

	// DECLARATIONS
	m_decl += GLSLHelpers::getVersionDecl( state );
	m_decl += GLSLHelpers::getDefines( state );

	// UNIFORMS
	m_decl += GLSLHelpers::getVGSDKUniformDecl();

	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape

	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "in", "In[]", true );
	//std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	//m_decl += code_samplers.first;

	//
	std::string inputs;
	std::string outputs;

	// declaration for lighting
	if ( state.isLightingEnabled() )
	{
		if ( !state.isPerVertexLightingEnabled() )
		{
			if ( state.isEnabled( FLAT_SHADING ) )
			{
				inputs +=	"flat in vec3 ecNormal[];\n";
				outputs +=	"flat out vec3 myNormal[3];\n";
				if ( state.isBumpMappingEnabled() )
				{
					inputs += "flat in vec3 tsTangent[];\n";
					outputs += "flat out vec3 myTangent[3];\n";
				}
			}
			else
			{
				inputs +=	"in vec3 ecNormal[];\n";
				outputs +=	"out vec3 myNormal[3];\n";
				if ( state.isBumpMappingEnabled() )
				{
					inputs += "in vec3 tsTangent[];\n";
					outputs += "out vec3 myTangent[3];\n";
				}
			}
		}
		// else nothing to do
	}
	// else nothing to do

	// INPUTS
	m_decl +=
		"// INPUTS\n"
		"\n"
		"// gl_in\n"
		"\n" +
		inputs;

	if ( has_ftexgen )	m_decl += "\n" + code_ftexgen.first;

	// OUTPUTS
	m_decl +=
		"// OUTPUTS\n"
		"layout(vertices = 3) out;\n"
		"\n"
		"// gl_out\n"
		"\n"
		"// User-defined per-vertex output variables\n"
		"struct PhongPatch\n"
		"{\n"
		"	float termIJ;\n"
		"	float termJK;\n"
		"	float termIK;\n"
		"};\n"
		"\n"
		"out PhongPatch iPhongPatch[3];\n"
		"\n" +
		outputs +
		"\n";

	if ( has_ftexgen )
	{
		m_decl += "out vec4 oMultiTexCoord0[];\n\n";
	}

	// LOCAL VARIABLES

	// FUNCTIONS
	m_code1 +=
		"\n"
		"// FUNCTIONS\n"
		"float PIi(int i, vec3 q)\n"
		"{\n"
		"	vec3 q_minus_p = q - gl_in[i].gl_Position.xyz;\n"
		"	return q[gl_InvocationID] - dot(q_minus_p, ecNormal[i]) * ecNormal[i][gl_InvocationID];\n"
		"}\n"
		"\n";

	// MAIN
	m_code2 +=
		"\n"
		"// MAIN function\n"
		"void main()\n"
		"{\n"
		"	// tessellation level\n"
		"	gl_TessLevelOuter[0] = tessValue;\n"
		"	gl_TessLevelOuter[1] = tessValue;\n"
		"	gl_TessLevelOuter[2] = tessValue;\n"
		"	gl_TessLevelInner[0] = tessValue;\n"
		"\n"
		"	// gl_out\n"
		"	gl_out[gl_InvocationID].gl_Position =  gl_in[gl_InvocationID].gl_Position;\n"
		"\n"
		"	// Out\n"
		"	// iPhongPatch\n"
		"	iPhongPatch[gl_InvocationID].termIJ = PIi(0,gl_in[1].gl_Position.xyz) + PIi(1,gl_in[0].gl_Position.xyz);\n"
		"	iPhongPatch[gl_InvocationID].termJK = PIi(1,gl_in[2].gl_Position.xyz) + PIi(2,gl_in[1].gl_Position.xyz);\n"
		"	iPhongPatch[gl_InvocationID].termIK = PIi(2,gl_in[0].gl_Position.xyz) + PIi(0,gl_in[2].gl_Position.xyz);\n"
		"\n"
		"	myNormal[gl_InvocationID] = ecNormal[gl_InvocationID];\n";
	if ( state.isBumpMappingEnabled() )
	{
		m_code2 +=
		"	myTangent[gl_InvocationID] = tsTangent[gl_InvocationID];\n";
	}


	m_code2 +=
	"}\n";

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		vgAssert( program != 0 );

		if ( program->getTessellationUse() )
		{
			std::string	shaderStr = program->getTessellationControl();
			m_decl.clear();
			m_code1 = shaderStr;
			m_code2.clear();
			return true;
		}
	}

	return true;
}


} // namespace engine

} // namespace vgeGL
