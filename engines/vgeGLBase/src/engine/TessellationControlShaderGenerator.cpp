//// VGSDK - Copyright (C) 2012, 2013, 2014, Alexandre Di Pino, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Alexandre Di Pino
//// Author Nicolas Papier
//
//#include "vgeGL/engine/TessellationControlShaderGenerator.hpp"
//
//#include <vgd/node/EngineProperties.hpp>
//#include <vgd/node/Program.hpp>
//#include "vgeGL/engine/Engine.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace engine
//{
//
//
//TessellationControlShaderGenerator::TessellationControlShaderGenerator()
//:	ShaderGenerator( glo::GLSLProgram::TESSELLATION_CONTROL )
//{}
//
//
//
//const bool TessellationControlShaderGenerator::generate( vgeGL::engine::Engine * engine )
//{
//	// Retrieves the GLSL state
//	GLSLState& state = engine->getGLSLState();
//
//	// Clears the code repository
//	m_decl.clear();
//	m_code1.clear();
//	m_code2.clear();
//
//	// DECLARATIONS
//	m_decl += GLSLHelpers::getVersionDecl( state );
//	m_decl += GLSLHelpers::getDefines( state );
//
//	// UNIFORMS
//	m_decl += GLSLHelpers::getVGSDKUniformDecl( state );
//
//	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape
//
//	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "in", "TexCoords", "inTexCoord[]", true );
//	std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );
//
//	m_decl += code_samplers.first;
//
//	// INPUTS
//	std::string inputs;
//	std::string outputs;
//// @todo #define SHADEMODEL flat or
//	// declaration for lighting
//	if ( state.isLightingEnabled() || state.isTessellationEnabled() )
//	{
//		if ( state.isEnabled( FLAT_SHADING ) ) inputs +=  "flat ";
//		inputs +=	"in vec4 ecPosition[];\n";
//
//		if ( state.isEnabled( FLAT_SHADING ) ) inputs +=  "flat ";
//		inputs +=	"in vec3 ecNormal[];\n";
//		if ( state.isEnabled( FLAT_SHADING ) ) outputs +=  "flat ";
//		outputs +=	"out vec3 myNormal[];\n";
//
//	}
//	// else nothing to do
//
//	if ( state.isEnabled( FLAT_SHADING ) ) inputs +=  "flat ";
//	inputs +=	"in vec4 vaColor[];\n\n";
//	if ( state.isEnabled( FLAT_SHADING ) ) outputs +=  "flat ";
//	outputs +=	"out vec4 myColor[];\n";
//
//	m_decl +=
//		"// INPUTS\n"
//		"\n"
//		"// gl_in[gl_MaxPatchVertices]\n"
//		"\n" +
//		inputs;
//
//	if ( has_ftexgen )
//	{
//		m_decl += "\n" + code_ftexgen.first;
//
//		std::string tmp = boost::algorithm::replace_first_copy(code_ftexgen.first, "in ", "out ");
//		boost::algorithm::replace_first( tmp, "inTexCoord", "outTexCoord" );
//		outputs += "\n" + tmp;
//	}
//
//	// declarations for bumpmapping
//	if ( state.isBumpMappingEnabled() )
//	{
//		m_decl +=	"// Bumpmapping parameters\n"
//					"in vec3 ecTangent[];\n\n";
//		outputs += "out vec3 myTangent[];\n";
//	}
//
//	// OUTPUTS
//	m_decl +=
//		"// OUTPUTS\n"
//		"layout(vertices = 3) out;\n"
//		"\n"
//		"// patch out float gl_TessLevelOuter[4];\n"
//		"// patch out float gl_TessLevelInner[2];\n"
//		"// gl_out[]\n"
//		"\n"
//		"// User-defined per-vertex output variables\n"
//		"struct PhongPatch\n"
//		"{\n"
//		"	float termIJ;\n"
//		"	float termJK;\n"
//		"	float termIK;\n"
//		"};\n"
//		"\n"
//		"out PhongPatch iPhongPatch[];\n"
//		"\n" +
//		outputs +
//		"\n";
//
//	// TCS_DECLARATIONS
//	m_decl += state.getShaderStage( GLSLState::TCS_DECLARATIONS ) + "\n";
//
//	// LOCAL VARIABLES
//
//	// FUNCTIONS
//	static std::string pixelsPerEdgeDeclarationsTCS =
//		"float computeScreenSphereSize( vec4 v1, vec4 v2, vec2 viewport )\n"
//		"{\n"
//		"	float d = distance(v1, v2);\n"
//		"	vec4 p1 = (v1 + v2) * 0.5;\n"
//		"	vec4 p2 = p1;\n"
//		"	p2.y += d;\n"
//		"\n"
//		"	// transformed to screen space\n"
//		"	p1 = p1 / p1.w;\n"
//		"	p2 = p2 / p2.w;\n"
//		"\n"
//		"	float sphereSizeInPixels = length( (p1.xy - p2.xy) * viewport * 0.5 );\n"
//		"	return sphereSizeInPixels;\n"
//		"}\n"
//		"\n"
//		"float computeTessLevel( float sphereSizeInPixels, float pixelsPerEdge )\n"
//		"{\n"
//		"	float numSubdivision = sphereSizeInPixels / pixelsPerEdge;\n"
//		"	return clamp( numSubdivision, TESS_RANGE_MIN, TESS_RANGE_MAX );\n"
//		"}\n"
//		"\n";
//
//	static std::string uniformMethodTCS = 
//		"void tessellationLevelMethodUNIFORM( out vec4 tessLevelOuter, out vec2 tessLevelInner )\n"
//		"{\n"
//		"	tessLevelOuter = vec4(TESS_RANGE_MAX);\n"
//		"	tessLevelInner = vec2(TESS_RANGE_MAX);\n"
//		"}\n";
//
//	static std::string pixelsPerEdgeMethodTCS =
//		"void tessellationLevelMethodPIXELS_PER_EDGE( out vec4 tessLevelOuter, out vec2 tessLevelInner )\n"
//		"{\n"
//		"	vec4 cpC0 = gl_ModelViewProjectionMatrix * gl_in[0].gl_Position;\n"
//		"	vec4 cpC1 = gl_ModelViewProjectionMatrix * gl_in[1].gl_Position;\n"
//		"	vec4 cpC2 = gl_ModelViewProjectionMatrix * gl_in[2].gl_Position;\n"
//		"\n"
//		"	vec2 viewport = vec2(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);\n"
//		"	float l0 = computeScreenSphereSize(cpC0, cpC1, viewport);\n"
//		"	float l1 = computeScreenSphereSize(cpC1, cpC2, viewport);\n"
//		"	float l2 = computeScreenSphereSize(cpC2, cpC0, viewport);\n"
//		"\n"
//		"	tessLevelOuter[0] = computeTessLevel( l1, tessPixelsPerEdge );\n"
//		"	tessLevelOuter[1] = computeTessLevel( l2, tessPixelsPerEdge );\n"
//		"	tessLevelOuter[2] = computeTessLevel( l0, tessPixelsPerEdge );\n"
//		"	tessLevelOuter[3] = 0;\n"
//		"	tessLevelInner[0] = max( max(tessLevelOuter[0], tessLevelOuter[1]) ,tessLevelOuter[2] );\n"
//		"	tessLevelInner[1] = 0;\n"
//		"}\n";
//
//	m_code1 += pixelsPerEdgeDeclarationsTCS + uniformMethodTCS + pixelsPerEdgeMethodTCS;
//
//	// Phong tessellation
//	m_code1 +=
//		"\n"
//		"// FUNCTIONS\n"
//		"float PIi(int i, vec3 q)\n"		// @todo replace q by int j and with q = gl_in[j].gl_Position.xyz ?
//		"{\n"
//		"	vec3 q_minus_p = q - gl_in[i].gl_Position.xyz;\n"
//		"	return q[gl_InvocationID] - dot(q_minus_p, ecNormal[i]) * ecNormal[i][gl_InvocationID];\n"
//		"}\n"
//		"\n";
//
//	// MAIN
//	m_code2 +=
//		"\n"
//		"// MAIN function\n"
//		"void main()\n"
//		"{\n"
//		"	if (gl_InvocationID == 0 )\n"
//		"	{\n"
//		"		vec4 tessLevelOuter;\n"
//		"		vec2 tessLevelInner;\n" +
//				state.getShaderStage( GLSLState::TCS_TESSLEVEL_COMPUTATION ) +
//		"		gl_TessLevelOuter[0] = tessLevelOuter[0];\n"
//		"		gl_TessLevelOuter[1] = tessLevelOuter[1];\n"
//		"		gl_TessLevelOuter[2] = tessLevelOuter[2];\n"
//		"		gl_TessLevelOuter[3] = tessLevelOuter[3];\n"
//		"		gl_TessLevelInner[0] = tessLevelInner[0];\n"
//		"		gl_TessLevelInner[1] = tessLevelInner[1];\n"
//		"	}\n"
//		"\n"
//		"	// gl_out[]\n"
//		"	gl_out[gl_InvocationID].gl_Position =  gl_in[gl_InvocationID].gl_Position;\n\n";
//
//	static std::string phongMainComputation =
//		"	// iPhongPatch\n"
//		"	iPhongPatch[gl_InvocationID].termIJ = PIi(0,gl_in[1].gl_Position.xyz) + PIi(1,gl_in[0].gl_Position.xyz);\n"
//		"	iPhongPatch[gl_InvocationID].termJK = PIi(1,gl_in[2].gl_Position.xyz) + PIi(2,gl_in[1].gl_Position.xyz);\n"
//		"	iPhongPatch[gl_InvocationID].termIK = PIi(2,gl_in[0].gl_Position.xyz) + PIi(0,gl_in[2].gl_Position.xyz);\n"
//		"\n";
//	m_code2 += phongMainComputation;
//
//	m_code2 +=
//		"\n"
//		"	myNormal[gl_InvocationID] = ecNormal[gl_InvocationID];\n"
//		"	myColor[gl_InvocationID] = vaColor[gl_InvocationID];\n"
//		"\n";
//
//	if ( has_ftexgen )
//	{
//		// @todo array assign ?
//		m_code2 +=	"	// mgl_TexCoord\n"
//					"	int iMax = inTexCoord[gl_InvocationID].mgl_TexCoord.length();\n"
//					"	for( int i = 0; i < iMax; ++i )\n"
//					"	{\n"
//					"		outTexCoord[gl_InvocationID].mgl_TexCoord[i] = inTexCoord[gl_InvocationID].mgl_TexCoord[i];\n"
//					"	}\n";
//		m_code2 +=	"	// mgl_TexCoordShadow\n"
//					"	iMax = inTexCoord[gl_InvocationID].mgl_TexCoordShadow.length();\n"
//					"	for( int i = 0; i < iMax; ++i )\n"
//					"	{\n"
//					"		outTexCoord[gl_InvocationID].mgl_TexCoordShadow[i] = inTexCoord[gl_InvocationID].mgl_TexCoordShadow[i];\n"
//					"	}\n";
//	}
//
//	if ( state.isBumpMappingEnabled() ) m_code2 += "\n	myTangent[gl_InvocationID] = ecTangent[gl_InvocationID];\n";
//
//	m_code2 +=
//	"}\n";
//
//	// Test if custom program must be installed
//	if ( state.isEnabled( PROGRAM ) )
//	{
//		vgd::node::Program * program = state.getProgram();
//		vgAssert( program != 0 );
//
//		if ( program->getTessellationUse() )
//		{
//			std::string	shaderStr = program->getTessellationControl();
//			m_code1 = shaderStr;
//			return true;
//		}
//	}
//
//	return true;
//}
//
//
//} // namespace engine
//
//} // namespace vgeGL
//