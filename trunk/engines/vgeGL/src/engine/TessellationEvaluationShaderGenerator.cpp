// VGSDK - Copyright (C) 2012, 2013, 2014, Alexandre Di Pino, Nicolas Papier.
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
	m_decl += GLSLHelpers::getVGSDKUniformDecl( state );

	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape

	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "in", "TexCoords", "inTexCoord[]", true );
	std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	m_decl += code_samplers.first;

	// INPUTS/OUTPUTS precomputations
	std::string inputs;
	std::string outputs;

	// declarations for lighting
	if ( state.isLightingEnabled() || state.isTessellationEnabled() )
	{
		if ( state.isEnabled( FLAT_SHADING ) ) inputs +=  "flat ";
		inputs +=	"in vec3 myNormal[];\n";
		if ( state.isEnabled( FLAT_SHADING ) ) inputs +=  "flat ";
		inputs +=	"in vec4 myColor[];\n";

		if ( state.isEnabled( FLAT_SHADING ) ) outputs +=  "flat ";
		outputs +=	"out vec4 ecPosition;\n";
		if ( state.isEnabled( FLAT_SHADING ) ) outputs +=  "flat ";
		outputs +=	"out vec3 ecNormal;\n";
	}

	if ( state.isEnabled( FLAT_SHADING ) ) m_decl +=  "flat ";
	outputs += "out vec4 vaColor;\n\n";

	// declarations for bumpmapping
	if ( state.isBumpMappingEnabled() )
	{
		m_decl +=	"// Bumpmapping parameters\n"
					"in vec3 myTangent[];\n";
		if ( state.isEnabled( FLAT_SHADING ) ) outputs +=  "flat ";
		outputs += "out vec3 ecTangent;\n";
	}

	// INPUTS
	m_decl +=
		"// INPUTS\n"
		"\n"
		"// gl_in[gl_MaxPatchVertices]\n"
		"// in int gl_PatchVerticesIn;\n"
		"// in int gl_PrimitiveID;\n"
		"// in vec3 gl_TessCoord;\n"
		"// patch in float gl_TessLevelOuter[4];\n"
		"// patch in float gl_TessLevelInner[2];\n"
		"\n"
		"layout(triangles, fractional_odd_spacing, ccw) in;\n"
		"\n"
		"// User-defined per-vertex input variables\n"
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

	if ( has_ftexgen )
	{
		//
		m_decl += code_ftexgen.first;

		//
		std::string tmp = boost::algorithm::replace_first_copy(code_ftexgen.first, "in ", "out ");
		boost::algorithm::replace_first( tmp, "inTexCoord[]", "outTexCoord" );
		outputs += "\n" + tmp;
	}

	// DECLARATIONS for bumpmapping
	if ( state.isBumpMappingEnabled() )
	{
		m_decl += GLSLHelpers::generate_declarationsForBumpmapping();
		outputs += "out BumpMappingParameters bumpParams;\n";
	}

	// OUTPUTS
	m_decl +=
		"// OUTPUTS\n"
		"\n"
		"// gl_out\n"
		"\n" +
		outputs;

	// TES_DECLARATIONS
	m_decl += state.getShaderStage( GLSLState::TES_DECLARATIONS ) + "\n";

	// LOCAL VARIABLES

	// FUNCTIONS
	m_code1 +=	"\n"
				"vec3 emitNew( vec3 A, vec3 B, vec3 C )\n"
				"{\n"
				"	vec3 retVal	=	gl_TessCoord[0] * A +\n"
				"					gl_TessCoord[1] * B +\n"
				"					gl_TessCoord[2] * C;\n"
				"	return retVal;\n"
				"}\n"
				"\n"
				"vec4 emitNew( vec4 A, vec4 B, vec4 C )\n"
				"{\n"
				"	vec4 retVal	=	gl_TessCoord[0] * A +\n"
				"					gl_TessCoord[1] * B +\n"
				"					gl_TessCoord[2] * C;\n"
				"	return retVal;\n"
				"}\n\n";

	if ( state.isBumpMappingEnabled() )
	{
		static const std::string ftangent =
		"vec3 ftangent(void)\n"
		"{\n"
		"	//Compute the tangent\n"
		"	vec3 tangent = emitNew( myTangent[0], myTangent[1], myTangent[2] );\n"
		"	tangent = gl_NormalMatrix * tangent;\n"
		"	return normalize(tangent);\n"
		"}\n\n";
		m_code1 += ftangent;
		m_code1 += GLSLHelpers::generateFunction_eyeVectorRelated( state );
	}

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
	"	vec4 position = vec4((1.0 - tessPhongBias) * barPos + tessPhongBias * phongPos, 1.0);\n"
	"\n"
	"	vec3 normal = emitNew( myNormal[0], myNormal[1], myNormal[2] );\n"
	"	ecNormal = /*normalize*/( gl_NormalMatrix * normal );\n"
	"\n" +
	state.getShaderStage( GLSLState::TES_POSITION_DISPLACEMENT ) +
	"\n"
	"	// gl_out\n" +
	//	gl_Position = gl_ModelViewProjectionMatrix * position;
	state.getShaderStage( GLSLState::VERTEX_GL_POSITION_COMPUTATION ) +
	"\n" +
	// ecPosition	= gl_ModelViewMatrix * position;
	state.getShaderStage( GLSLState::VERTEX_ECPOSITION_COMPUTATION ) +
	"	vaColor = emitNew( myColor[0], myColor[1], myColor[2] );\n";

	if ( has_ftexgen )
	{
		m_code2 +=
		"\n"
		"	// texCoord\n"
		"	int iMax = inTexCoord[0].mgl_TexCoord.length();\n"
		"	for( int i = 0; i < iMax; ++i )\n"
		"	{\n"
		"		outTexCoord.mgl_TexCoord[i]= emitNew( inTexCoord[0].mgl_TexCoord[i], inTexCoord[1].mgl_TexCoord[i], inTexCoord[2].mgl_TexCoord[i] );\n"
		"	}\n"
		"	// mgl_TexCoordShadow\n"
		"	iMax = inTexCoord[0].mgl_TexCoordShadow.length();\n"
		"	for( int i = 0; i < iMax; ++i )\n"
		"	{\n"
		"		outTexCoord.mgl_TexCoordShadow[i]= emitNew( inTexCoord[0].mgl_TexCoordShadow[i], inTexCoord[1].mgl_TexCoordShadow[i], inTexCoord[2].mgl_TexCoordShadow[i] );\n"
		"	}\n";
	}

	// generate bump mapping computation
	if ( state.isBumpMappingEnabled() )
	{
		std::string tmp = GLSLHelpers::generate_bumpComputation( state ) + "\n";
		m_code2 += "	// bumpMapping\n" + tmp;
	}

	m_code2 += "}\n";

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		vgAssert( program != 0 );

		if ( program->getTessellationUse() )
		{
			std::string	shaderStr = program->getTessellationEvaluation();
			m_code1 = shaderStr;
			return true;
		}
	}

	return true;
}


} // namespace engine

} // namespace vgeGL
