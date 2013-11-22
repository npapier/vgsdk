// VGSDK - Copyright (C) 2012, 2013, Alexandre Di Pino, Nicolas Papier.
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
	m_decl += GLSLHelpers::getVGSDKUniformDecl( state );

	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape

	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "in", "TexCoords", "inTexCoord[]", true );
	//std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	//m_decl += code_samplers.first;

	// INPUTS
	std::string inputs;
	std::string outputs;
// @todo #define SHADEMODEL flat or
	// declaration for lighting
	if ( state.isLightingEnabled() )
	{
		if ( state.isEnabled( FLAT_SHADING ) ) inputs +=  "flat ";
		inputs +=	"in vec3 ecNormal[];\n";
		if ( state.isEnabled( FLAT_SHADING ) ) outputs +=  "flat ";
		outputs +=	"out vec3 myNormal[];\n";
	}
	// else nothing to do

	m_decl +=
		"// INPUTS\n"
		"\n"
		"// gl_in[gl_MaxPatchVertices]\n"
		"\n" +
		inputs;

	if ( has_ftexgen )
	{
		m_decl += "\n" + code_ftexgen.first;

		std::string tmp = boost::algorithm::replace_first_copy(code_ftexgen.first, "in ", "out ");
		boost::algorithm::replace_first( tmp, "inTexCoord", "outTexCoord" );
		outputs += "\n" + tmp;
	}

	// declarations for bumpmapping
	if ( state.isBumpMappingEnabled() )
	{
		m_decl +=	"// Bumpmapping parameters\n"
					"in vec3 ecTangent[];\n\n";
		outputs += "out vec3 myTangent[];\n";
	}

	// OUTPUTS
	m_decl +=
		"// OUTPUTS\n"
		"layout(vertices = 3) out;\n"
		"\n"
		"// patch out float gl_TessLevelOuter[4];\n"
		"// patch out float gl_TessLevelInner[2];\n"
		"// gl_out[]\n"
		"\n"
		"// User-defined per-vertex output variables\n"
		"struct PhongPatch\n"
		"{\n"
		"	float termIJ;\n"
		"	float termJK;\n"
		"	float termIK;\n"
		"};\n"
		"\n"
		"out PhongPatch iPhongPatch[];\n"
		"\n" +
		outputs +
		"\n";

	// LOCAL VARIABLES

	// FUNCTIONS
	m_code1 +=
		"\n"
		"// FUNCTIONS\n"
		"float PIi(int i, vec3 q)\n"		// @todo replace q by int j and with q = gl_in[j].gl_Position.xyz ?
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
		"	// gl_out[]\n"
		"	gl_out[gl_InvocationID].gl_Position =  gl_in[gl_InvocationID].gl_Position;\n"
		"\n"
		"	// iPhongPatch\n"
		"	iPhongPatch[gl_InvocationID].termIJ = PIi(0,gl_in[1].gl_Position.xyz) + PIi(1,gl_in[0].gl_Position.xyz);\n"
		"	iPhongPatch[gl_InvocationID].termJK = PIi(1,gl_in[2].gl_Position.xyz) + PIi(2,gl_in[1].gl_Position.xyz);\n"
		"	iPhongPatch[gl_InvocationID].termIK = PIi(2,gl_in[0].gl_Position.xyz) + PIi(0,gl_in[2].gl_Position.xyz);\n"
		"\n"
		"	myNormal[gl_InvocationID] = ecNormal[gl_InvocationID];\n";

	if ( has_ftexgen )
	{
		// @todo array assign ?
		m_code2 +=	"	// mgl_TexCoord\n"
					"	int iMax = inTexCoord[gl_InvocationID].mgl_TexCoord.length();\n"
					"	for( int i = 0; i < iMax; ++i )\n"
					"	{\n"
					"		outTexCoord[gl_InvocationID].mgl_TexCoord[i] = inTexCoord[gl_InvocationID].mgl_TexCoord[i];\n"
					"	}\n";
		m_code2 +=	"	// mgl_TexCoordShadow\n"
					"	iMax = inTexCoord[gl_InvocationID].mgl_TexCoordShadow.length();\n"
					"	for( int i = 0; i < iMax; ++i )\n"
					"	{\n"
					"		outTexCoord[gl_InvocationID].mgl_TexCoordShadow[i] = inTexCoord[gl_InvocationID].mgl_TexCoordShadow[i];\n"
					"	}\n";
	}

	if ( state.isBumpMappingEnabled() ) m_code2 += "\n	myTangent[gl_InvocationID] = ecTangent[gl_InvocationID];\n";

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
			m_code1 = shaderStr;
			return true;
		}
	}

	return true;
}


} // namespace engine

} // namespace vgeGL
