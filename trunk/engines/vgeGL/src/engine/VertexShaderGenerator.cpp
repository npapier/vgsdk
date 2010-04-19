// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
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
	m_decl += "#version 120\n";

	// Test if custom program must be installed
	if ( state.isEnabled( GLSLState::PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		assert( program );

		std::string shaderStr;
		program->getShader( vgd::node::Program::VERTEX, shaderStr );

		m_code1 = shaderStr;

		return true;
	}

	// DECLARATIONS
	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
			m_decl += GLSLHelpers::generate_lightAccumulators( state ) + "\n";
		}
		else
		{
			if ( state.isEnabled( GLSLState::FLAT_SHADING ) )
			{
				m_decl += 
				"flat varying vec4 ecPosition;\n" // @todo really flat ?
				"flat varying vec3 ecNormal;\n\n";
			}
			else
			{
				m_decl += 
				"varying vec4 ecPosition;\n"
				"varying vec3 ecNormal;\n\n";

				/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
				{
					m_decl += "varying vec4 mglColor;\n\n";
				}*/
			}
		}
	}
	// else nothing to do

	const bool has_ftexgen = state.getNumTexture() > 0;	// @todo Should be the number of texCoord in VertexShape

	std::pair< std::string, std::string > code_ftexgen;
	if ( has_ftexgen )
	{
		code_ftexgen = GLSLHelpers::generateFunction_ftexgen(state);
		m_decl += code_ftexgen.first;
	}

	// FUNCTIONS
	m_code1 += GLSLHelpers::generateFunction_fnormal( state );

	if ( has_ftexgen )	m_code1 += code_ftexgen.second;

	if ( state.isLightingEnabled() && state.isPerVertexLightingEnabled() )
	{
		m_code1 += GLSLHelpers::generate_lights( state ) + "\n";
		m_code1 += GLSLHelpers::generateFunction_flight( state ) + "\n";
	}


// @todo generateFunction_fVertexAttrib()  and generate_vertexAttribDeclaration()

	// MAIN
	m_code2 +=
	"\n"
	"void main( void )\n"
	"{\n";

	if ( state.isLightingEnabled() == false || state.isPerVertexLightingEnabled() )
	{
		m_code2 += 
		"	vec4	ecPosition;\n"		// Eye-coordinate position of vertex
		"	vec3	ecNormal;\n"
		"\n";
	}
	// else nothing

	m_code2 +=
	"	gl_Position	= ftransform();\n"
	"\n";

	m_code2 +=
	"	ecPosition	= gl_ModelViewMatrix * gl_Vertex;\n"
	"	ecNormal	= fnormal();\n"
	"\n";

	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
			// Calls flight()
			m_code2 += 
			"	flight( ecPosition, ecNormal );\n"
			"\n"
			"	gl_FrontColor			= vec4(accumColor.rgb, gl_FrontMaterial.diffuse.a);\n"
//			"	gl_FrontColor			= vec4(accumColor.rgb, gl_Color.a);\n"
			"	gl_FrontSecondaryColor	= vec4(accumSecondaryColor.rgb, 0.0);\n";

			if ( state.isTwoSidedLightingEnabled() )
			{
				m_code2 +=
				"	gl_BackColor			= vec4(accumBackColor.rgb, gl_FrontMaterial.diffuse.a);\n"				
//				"	gl_BackColor			= vec4(accumBackColor.rgb, gl_Color.a);\n"
				"	gl_BackSecondaryColor	= vec4(accumBackSecondaryColor.rgb, 0.0);\n";
			}
		}
		else
		{
			/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
			{
				// pixel lighting and VertexShape::color4, so gl_Color must be transfered to fragment program.
				// m_code2 += "	mglColor = gl_Color;\n";
			}*/

			m_code2 +=	
			"	gl_FrontColor			= gl_FrontMaterial.diffuse;\n";
//			"	gl_FrontColor			= gl_Color;\n"
//			"	gl_FrontSecondaryColor	= vec4(gl_SecondaryColor.rgb, 0.0);\n";

			if ( state.isTwoSidedLightingEnabled() )
			{
				m_code2 +=
				"	gl_BackColor			= gl_FrontMaterial.diffuse;\n";
//				"	gl_BackColor			= gl_Color;\n"
//				"	gl_BackSecondaryColor	= vec4(gl_SecondaryColor.rgb, 0.0);\n";
			}
//			// else nothing to do
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

	if ( has_ftexgen )
	{
		m_code2 += "	ftexgen( ecPosition, ecNormal );\n";
	}


	/*if (	glIsEnabled(GL_CLIP_PLANE0) || glIsEnabled(GL_CLIP_PLANE1) ||
		glIsEnabled(GL_CLIP_PLANE2) || glIsEnabled(GL_CLIP_PLANE3) ||
		glIsEnabled(GL_CLIP_PLANE4) || glIsEnabled(GL_CLIP_PLANE5)	)*/
	if ( state.isEnabled( GLSLState::CLIPPING_PLANE ) )
	{
		m_code2 += "	gl_ClipVertex = ecPosition;\n";
	}

	// POINT SIZE
	if ( state.isEnabled( GLSLState::POINT_STYLE ) )
	{
		m_code1 += GLSLHelpers::generate_fpoint( state ) + "\n";
		m_code2 += "	gl_PointSize = fpoint( length(ecPosition) );\n"; // , 1.0 );\n";
	}

	m_code2 += "}\n";

	if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
	{
		boost::algorithm::replace_all( m_code1, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
		boost::algorithm::replace_all( m_code2, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
	}

	return true;
}



} // namespace engine

} // namespace vgeGL
