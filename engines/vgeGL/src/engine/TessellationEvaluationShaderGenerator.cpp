// VGSDK - Copyright (C) 2012, Alexandre Di Pino, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino
// Author Nicolas Papier

#include "vgeGL/engine/TessellationEvaluationShaderGenerator.hpp"

#include <vgd/node/Program.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{


TessellationEvaluationShaderGenerator::TessellationEvaluationShaderGenerator()
:	ShaderGenerator( glo::GLSLProgram::TESSELLATION_EVALUATION )
{}



const bool TessellationEvaluationShaderGenerator::generate( vgeGL::engine::Engine * engine )
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
				inputs +=	"flat in vec3 myNormal[];\n";
				outputs +=	"flat out vec4 ecPosition;\n"
							"flat out vec3 ecNormal;\n";
				if ( state.isBumpMappingEnabled() )
				{
					inputs += "flat in vec3 myTangent[];\n";
				}
			}
			else
			{
				inputs +=	"in vec3 myNormal[];\n";
				outputs +=	"out vec4 ecPosition;\n"
							"out vec3 ecNormal;\n";
				if ( state.isBumpMappingEnabled() )
				{
					inputs += "in vec3 myTangent[];\n";
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
		"layout(triangles, fractional_even_spacing, ccw) in;\n"		// equal_spacing
		"\n"
		"struct PhongPatch\n"
		"{\n"
		"	float termIJ;\n"
		"	float termJK;\n"
		"	float termIK;\n"
		"};\n"
		"\n"
		"in PhongPatch iPhongPatch[];\n"
		"\n" +
		inputs +
		"\n";

	// OUTPUTS
	m_decl +=
		"// OUTPUTS\n"
		"\n"
		"// gl_out\n"
		"\n" +
		outputs;

	// LOCAL VARIABLES
	// FUNCTIONS

	// MAIN
	m_code2 += 
	"\n"
	"// MAIN function\n"
	"void main()\n"
	"{\n"
	"	// tessellation\n"
	"	vec3 tc1 = gl_TessCoord;\n"
	"	vec3 tc2 = gl_TessCoord * gl_TessCoord;\n"
	"\n"
	"	vec3 termIJ = vec3(	iPhongPatch[0].termIJ,\n"
	"						iPhongPatch[1].termIJ,\n"
    "						iPhongPatch[2].termIJ);\n"
	"	vec3 termJK = vec3(	iPhongPatch[0].termJK,\n"
	"						iPhongPatch[1].termJK,\n"
	"						iPhongPatch[2].termJK);\n"
	"	vec3 termIK = vec3(	iPhongPatch[0].termIK,\n"
	"						iPhongPatch[1].termIK,\n"
	"						iPhongPatch[2].termIK);\n"
	"\n"
	"	vec3 phongPos   = tc2[0]*gl_in[0].gl_Position.xyz\n"
	"					+ tc2[1]*gl_in[1].gl_Position.xyz\n"
	"					+ tc2[2]*gl_in[2].gl_Position.xyz\n"
	"					+ tc1[0]*tc1[1]*termIJ\n"
	"					+ tc1[1]*tc1[2]*termJK\n"
	"					+ tc1[2]*tc1[0]*termIK;\n"
	"	vec3 barPos = tc1[0] * gl_in[0].gl_Position.xyz\n"
	"				+ tc1[1] * gl_in[1].gl_Position.xyz\n"
	"				+ tc1[2] * gl_in[2].gl_Position.xyz;\n"
	"\n"
	"	// position is a 'copy of mgl_Vertex' for vertex texturing. mgl_Vertex is computed implicitly by the next line.\n"
	"	vec4 position = vec4((1.0 - tessBias) * barPos + tessBias * phongPos, 1.0);\n"
	"\n"
	"	// gl_out\n" +
	//	gl_Position = gl_ModelViewProjectionMatrix * position;
	state.getShaderStage( GLSLState::VERTEX_GL_POSITION_COMPUTATION ) +
	"\n"
	"	// Out\n" +
	// ecPosition	= gl_ModelViewMatrix * position;
	state.getShaderStage( GLSLState::VERTEX_ECPOSITION_COMPUTATION ) +
	"\n"
	"	vec3 normal	= tc1[0] * myNormal[0]\n"
	"				+ tc1[1] * myNormal[1]\n"
	"				+ tc1[2] * myNormal[2];\n"
	"\n"
	"	ecNormal = /*normalize*/( gl_NormalMatrix * normal );\n";

	m_code2 += "}\n";

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		vgAssert( program != 0 );

		if ( program->getTessellationUse() )
		{
			std::string	shaderStr = program->getTessellationEvaluation();
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
