// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Nicolas Papier.
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
	m_decl += GLSLHelpers::getVersionDecl();

	// UNIFORMS
	m_decl += GLSLHelpers::getVGSDKUniformDecl();

	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape
	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "out" );
	std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	m_decl += code_samplers.first;

	// INPUTS
	m_decl += "// INPUTS\n";

	// BEGIN: VERTEX SHADER SPECIFIC
	const std::string vertexIndexStr	= vgd::basic::toString( vgeGL::engine::VERTEX_INDEX );
	const std::string normalIndexStr	= vgd::basic::toString( vgeGL::engine::NORMAL_INDEX );
	const std::string texCoord0IndexStr	= vgd::basic::toString( vgeGL::engine::TEXCOORD_INDEX );
	const std::string texCoord1IndexStr	= vgd::basic::toString( vgeGL::engine::TEXCOORD_INDEX + 1 );
	const std::string texCoord2IndexStr	= vgd::basic::toString( vgeGL::engine::TEXCOORD_INDEX + 2 );

	m_decl += "layout(location = " + vertexIndexStr + ") in vec4 mgl_Vertex;\n";
	m_decl += "layout(location = " + normalIndexStr + ") in vec3 mgl_Normal;\n";
	m_decl += "layout(location = " + texCoord0IndexStr + ") in vec4 mgl_MultiTexCoord0;\n";
	m_decl += "layout(location = " + texCoord1IndexStr + ") in vec4 mgl_MultiTexCoord1;\n";
	m_decl += "layout(location = " + texCoord2IndexStr + ") in vec4 mgl_MultiTexCoord2;\n\n";
	// END: VERTEX SHADER SPECIFIC

	// OUTPUT
	m_decl += "// OUTPUTS\n";

	if ( has_ftexgen )	m_decl += code_ftexgen.first;

	// out vec4 gl_Position;
	m_decl += "// VARIANCE QUALIFIER\n";
	m_decl += "invariant gl_Position;\n\n";

	// VERTEX_DECLARATIONS
	const std::string vertexDeclaration = state.getShaderStage( GLSLState::VERTEX_DECLARATIONS );
	if ( !vertexDeclaration.empty() )	m_decl += vertexDeclaration + "\n";

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		assert( program );

		std::string shaderStr;
		program->getShader( vgd::node::Program::VERTEX, shaderStr );

		m_decl += "\n";
		m_code1 = shaderStr;

		return true;
	}

	// DECLARATIONS for lighting
	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
			m_decl += GLSLHelpers::generate_lightAccumulators( state ) + "\n";
		}
		else
		{
			if ( state.isEnabled( FLAT_SHADING ) )
			{
				m_decl += 
				"flat out vec4 ecPosition;\n" // @todo really flat ?
				"flat out vec3 ecNormal;\n\n";
			}
			else
			{
				m_decl += 
				"out vec4 ecPosition;\n"
				"out vec3 ecNormal;\n\n";

				/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
				{
					m_decl += "out vec4 mglColor;\n\n";
				}*/
			}
		}
	}
	// else nothing to do

	// FUNCTIONS
	m_code1 += GLSLHelpers::generateFunction_fnormal( state );

	if ( has_ftexgen )	m_code1 += code_ftexgen.second;

	if ( state.isLightingEnabled() && state.isPerVertexLightingEnabled() )
	{
		m_code1 += GLSLHelpers::generateFunctions_lights( state ) + "\n";
		m_code1 += GLSLHelpers::generateFunction_flight( state ) + "\n";
	}

// @todo generateFunction_fVertexAttrib()  and generate_vertexAttribDeclaration()

	// MAIN
	m_code2 +=
	"\n"
	"void main( void )\n"
	"{\n"
	"	// position is a copy of mgl_Vertex for vertex texturing (mgl_Vertex is read-only).\n"
	"	vec4 position = mgl_Vertex;\n"
	"\n";

	if ( state.isLightingEnabled() == false || state.isPerVertexLightingEnabled() )
	{
		m_code2 +=
		"	vec4	ecPosition;\n"		// Eye-coordinate position of vertex
		"	vec3	ecNormal;\n"
		"\n";
	}
	// else nothing

	// gl_Position = gl_ModelViewProjectionMatrix * position;
	m_code2 += state.getShaderStage( GLSLState::VERTEX_GL_POSITION_COMPUTATION );

	// ecPosition	= gl_ModelViewMatrix * position;
	m_code2 += state.getShaderStage( GLSLState::VERTEX_ECPOSITION_COMPUTATION );

	// ecNormal	= fnormal();
	m_code2 += state.getShaderStage( GLSLState::VERTEX_ECNORMAL_COMPUTATION ) + "\n";

	// TEXGEN
	if ( has_ftexgen )		m_code2 += "	ftexgen( ecPosition, ecNormal );\n";

	// TEXTURE LOOKUP
	if ( has_ftexgen )
	{
		// texture lookup
		const std::string textureLookup = GLSLHelpers::generate_vertexShader_texLookups( state );
		m_code2 += textureLookup;
	}

	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
// @todo removes gl_Front*Color
			// Calls flight()
			m_code2 += 
			"	flight( ecPosition, ecNormal );\n"
			"\n"
			"	gl_FrontColor			= vec4(accumColor.rgb, gl_FrontMaterial.diffuse.a);\n"
			"	gl_FrontSecondaryColor	= vec4(accumSecondaryColor.rgb, 1.0);\n";

			if ( state.isTwoSidedLightingEnabled() )
			{
				m_code2 +=
				"	gl_BackColor			= vec4(accumBackColor.rgb, gl_FrontMaterial.diffuse.a);\n"
				"	gl_BackSecondaryColor	= vec4(accumBackSecondaryColor.rgb, 1.0);\n";
			}
		}
		else
		{
			/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
			{
				// pixel lighting and VertexShape::color4, so gl_Color must be transfered to fragment program.
				// m_code2 += "	mglColor = gl_Color;\n";
			}*/

			/*m_code2 +=
			//"	gl_FrontColor			= gl_FrontMaterial.diffuse;\n";
			//"	gl_FrontSecondaryColor	= vec4(0.0, 0.0, 0.0, 1.0);\n";*/

			/*if ( state.isTwoSidedLightingEnabled() )
			{
				m_code2 +=
				"	gl_BackColor			= gl_FrontMaterial.diffuse;\n";
				//"	gl_BackSecondaryColor	= vec4(0.0, 0.0, 0.0, 1.0);\n";
			}*/
		}
	}
	else
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

	/*if ( state.isEnabled( COLOR4_BIND_PER_VERTEX ) )
	{
		boost::algorithm::replace_all( m_code1, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
		boost::algorithm::replace_all( m_code2, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
	}*/

	return true;
}



} // namespace engine

} // namespace vgeGL
