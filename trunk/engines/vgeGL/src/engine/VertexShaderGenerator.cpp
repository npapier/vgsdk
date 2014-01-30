// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/VertexShaderGenerator.hpp"

#include <vgd/node/Program.hpp>
#include "vgeGL/engine/Engine.hpp"

// @todo generates all shaders from one function to avoid multiple if



namespace vgeGL
{

namespace engine
{



// VertexShaderGenerator 
VertexShaderGenerator::VertexShaderGenerator()
:	ShaderGenerator( glo::GLSLProgram::VERTEX )
{
}



const bool VertexShaderGenerator::generate( vgeGL::engine::Engine * engine )
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

	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "out", "TexCoords", "outTexCoord", false, true );
	std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	m_decl += code_samplers.first;

	// INPUTS
	m_decl += "// INPUTS\n";

	// BEGIN: VERTEX SHADER SPECIFIC
	const std::string vertexIndexStr	= vgd::basic::toString( vgeGL::engine::VERTEX_INDEX );
	const std::string normalIndexStr	= vgd::basic::toString( vgeGL::engine::NORMAL_INDEX );
	const std::string tangentIndexStr	= vgd::basic::toString( vgeGL::engine::TANGENT_INDEX );
	const std::string colorIndexStr		= vgd::basic::toString( vgeGL::engine::COLOR_INDEX );

	const std::string texCoord0IndexStr	= vgd::basic::toString( vgeGL::engine::TEXCOORD_INDEX );
	const std::string texCoord1IndexStr	= vgd::basic::toString( vgeGL::engine::TEXCOORD1_INDEX );
	const std::string texCoord2IndexStr	= vgd::basic::toString( vgeGL::engine::TEXCOORD2_INDEX );

	m_decl += "layout(location = " + vertexIndexStr +	") in vec4 mgl_Vertex;\n";
	m_decl += "layout(location = " + normalIndexStr +	") in vec3 mgl_Normal;\n";
	m_decl += "layout(location = " + tangentIndexStr +	") in vec3 mgl_Tangent;\n";
	m_decl += "layout(location = " + colorIndexStr +	") in vec4 mgl_Color;\n";
	m_decl += "\n";

	m_decl += "layout(location = " + texCoord0IndexStr + ") in vec4 mgl_MultiTexCoord0;\n";
	m_decl += "layout(location = " + texCoord1IndexStr + ") in vec4 mgl_MultiTexCoord1;\n";
	m_decl += "layout(location = " + texCoord2IndexStr + ") in vec4 mgl_MultiTexCoord2;\n\n";
	m_decl += "\n";

	if ( state.isEnabled( vgeGL::engine::GEOMORPH ) )
	{
		const std::string vertexIndexStr	= vgd::basic::toString( vgeGL::engine::VERTEX1_INDEX );
		const std::string normalIndexStr	= vgd::basic::toString( vgeGL::engine::NORMAL1_INDEX );
		const std::string tangentIndexStr	= vgd::basic::toString( vgeGL::engine::TANGENT1_INDEX );

		m_decl += "layout(location = " + vertexIndexStr +	") in vec4 mgl_Vertex1;\n";
		m_decl += "layout(location = " + normalIndexStr +	") in vec3 mgl_Normal1;\n";
		m_decl += "layout(location = " + tangentIndexStr +	") in vec3 mgl_Tangent1;\n";
		m_decl += "\n";
	}

	// END: VERTEX SHADER SPECIFIC

	// OUTPUTS
	m_decl += "// OUTPUTS\n";
	if ( state.isTessellationEnabled() == false )
	{
		// out vec4 gl_Position;
		m_decl +=
				"// VARIANCE QUALIFIER (for out vec4 gl_Position;)\n"
/*				"out gl_PerVertex\n"
				"{\n"
				"	vec4 gl_Position;\n"
				"};\n"*/
				"invariant gl_Position;\n"
				"\n";
	}

	// VERTEX_DECLARATIONS
	const std::string vertexDeclaration = state.getShaderStage( GLSLState::VERTEX_DECLARATIONS );
	if ( !vertexDeclaration.empty() )	m_decl += vertexDeclaration + "\n";

	// declarations for lighting
	if ( state.isLightingEnabled() || state.isTessellationEnabled() )
	{
		if ( state.isEnabled( FLAT_SHADING ) ) m_decl +=  "flat ";
		m_decl += "out vec4 ecPosition;\n";

		if ( state.isEnabled( FLAT_SHADING ) ) m_decl +=  "flat ";
		m_decl += "out vec3 ecNormal;\n"; // @todo not if bump
	}
	// else nothing to do

	if ( state.isEnabled( FLAT_SHADING ) ) m_decl +=  "flat ";
	m_decl += "out vec4 vaColor;\n\n";

	if ( has_ftexgen )
	{
		m_decl += code_ftexgen.first;
		m_decl += "#define mgl_TexCoordShadow	outTexCoord.mgl_TexCoordShadow\n";
	}

	// declarations for bumpmapping
	if ( state.isBumpMappingEnabled() )
	{
		m_decl += GLSLHelpers::generate_declarationsForBumpmapping();
		m_decl +=	"// Bumpmapping parameters\n"
					"out vec3 ecTangent;\n";
		if ( !state.isTessellationEnabled() )	m_decl += "out BumpMappingParameters bumpParams;\n";
	}

	// LOCAL VARIABLES

	// FUNCTIONS
	m_code1 +=
		"\n"
		"// FUNCTIONS\n";

	if ( state.isBumpMappingEnabled() && !state.isTessellationEnabled() )
	{
		m_code1 += GLSLHelpers::generateFunction_ftangent( state );
		m_code1 += GLSLHelpers::generateFunction_eyeVectorRelated( state );
	}

	if ( has_ftexgen )	m_code1 += code_ftexgen.second;

// @todo generateDeclaration_vertexAttrib() and generateFunction_vertexAttrib()

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		vgAssert( program != 0 );

		if ( program->getVertexUse() )
		{
			m_code1 = program->getVertex();
			return true;
		}
	}

	// MAIN
	m_code2 +=
	"\n"
	"// MAIN function\n"
	"void main( void )\n"
	"{\n"
	"	// position is a copy of mgl_Vertex for vertex displacement (mgl_Vertex is read-only).\n"
	"	vec4 position = mgl_Vertex;\n"		// @todo rename position => vertex
	"	// normal is a copy of mgl_Normal\n"
	"	vec3 normal = mgl_Normal;\n"
	"	// tangent is a copy of mgl_Tangent\n"
	"	vec3 tangent = mgl_Tangent;\n"
	"\n";

	m_code2 += state.getShaderStage( GLSLState::VERTEX_POSITION_COMPUTATION ) + "\n";
	m_code2 += state.getShaderStage( GLSLState::VERTEX_NORMAL_COMPUTATION ) + "\n";
	m_code2 += state.getShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT ) + "\n";

	if ( !state.isLightingEnabled() && !state.isTessellationEnabled() )
	{
		m_code2 +=
		"	vec4	ecPosition;\n"		// Eye-coordinate position of vertex
		"	vec3	ecNormal;\n"
		"\n";
	}
	// else nothing

	// gl_Position	= gl_ModelViewProjectionMatrix * position;
	// ecPosition	= gl_ModelViewMatrix * position;
	// ecNormal		= normalize( gl_NormalMatrix * normal ); <=> ecNormal	= fnormal();
	if ( state.isTessellationEnabled() )
	{
		m_code2 +=	"	gl_Position = position;\n"
					"	ecPosition	= gl_ModelViewMatrix * position;\n"
					"	ecNormal	= normal;\n";
	}
	else
	{
		m_code2 += state.getShaderStage( GLSLState::VERTEX_GL_POSITION_COMPUTATION );
		m_code2 += state.getShaderStage( GLSLState::VERTEX_ECPOSITION_COMPUTATION ) + "\n";
		m_code2 += state.getShaderStage( GLSLState::VERTEX_ECNORMAL_COMPUTATION ) + "\n";
	}

	m_code2 += "	#ifdef COLOR_BIND_PER_VERTEX\n"
					"		vaColor = mgl_Color;\n"
					"	#else\n"
					"		vaColor = gl_FrontMaterial.diffuse;\n"
					"	#endif\n\n";

	// ftexgen() => mgl_TexCoord[...] = ...
	if ( has_ftexgen )
	{
		m_code2 +=	"\n"
					"	ftexgen( ecPosition, ecNormal );\n\n";
	}

	// generate bump mapping function
	if ( state.isBumpMappingEnabled() )
	{
		if ( state.isTessellationEnabled() )
		{
			m_code2 += "	ecTangent = tangent;\n\n";
		}
		else
		{
			m_code2 += GLSLHelpers::generate_bumpComputation( state ) + "\n";
		}
	}

	// TEXTURE LOOKUP
	if ( has_ftexgen )
	{
		// texture lookup
		const std::string textureLookup = GLSLHelpers::generate_vertexShader_texLookups( state );
		m_code2 += textureLookup;
	}

	if ( !state.isLightingEnabled() )
	{
		// no lighting
		m_code2 +=
		"	gl_FrontColor			= gl_FrontMaterial.diffuse;\n"
		"	gl_FrontSecondaryColor	= vec4(0.0, 0.0, 0.0, 1.0);\n";

		if ( state.isTwoSidedLightingEnabled() )
		{
			m_code2 +=
			"	gl_BackColor			= gl_FrontMaterial.diffuse;\n"
			"	gl_BackSecondaryColor	= vec4(0.0, 0.0, 0.0, 1.0);\n";
		}
	}
	// else nothing to do

	/*if ( glIsEnabled(GL_FOG) )
	{
		m_code2 += "	gl_FogFragCoord = ffog( ecPosition.z );\n";
	}*/


	/*if (	glIsEnabled(GL_CLIP_PLANE0) || glIsEnabled(GL_CLIP_PLANE1) ||
		glIsEnabled(GL_CLIP_PLANE2) || glIsEnabled(GL_CLIP_PLANE3) ||
		glIsEnabled(GL_CLIP_PLANE4) || glIsEnabled(GL_CLIP_PLANE5)	)*/
	if ( state.isEnabled( CLIPPING_PLANE ) )
	{
		m_code2 += "	gl_ClipVertex = ecPosition;\n";
	}

	// POINT SIZE
	if ( state.isEnabled( POINT_STYLE ) )
	{
		m_code1 += GLSLHelpers::generate_fpoint( state ) + "\n";
		m_code2 += "	gl_PointSize = fpoint( length(ecPosition) );\n";
	}

	m_code2 += "}\n";

	/*if ( state.isEnabled( COLOR_BIND_PER_VERTEX ) )
	{
		boost::algorithm::replace_all( m_code1, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
		boost::algorithm::replace_all( m_code2, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
	}*/

	return true;
}



} // namespace engine

} // namespace vgeGL
