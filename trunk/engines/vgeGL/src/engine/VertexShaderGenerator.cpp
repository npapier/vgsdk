// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/VertexShaderGenerator.hpp"

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

	const bool ftexgen = state.getNumTexture() > 0;	// @todo Should be the number of texCoord in VertexShape

	// Clears the code repository
	m_code.clear();
	m_code += "#version 120\n";

	// DECLARATIONS
	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
			m_code += GLSLHelpers::generate_lightAccumulators( state ) + "\n";
		}
		else
		{
			if ( state.isEnabled( GLSLState::FLAT_SHADING ) )
			{
				m_code += 
				"flat varying out vec4 ecPosition;\n" // @todo really flat ?
				"flat varying out vec3 ecNormal;\n\n";
			}
			else
			{
				m_code += 
				"varying vec4 ecPosition;\n"
				"varying vec3 ecNormal;\n\n";

				/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
				{
					m_code += "varying vec4 mglColor;\n\n";
				}*/
			}
		}
	}
	// else nothing to do

	// FUNCTIONS
	m_code += GLSLHelpers::generateFunction_fnormal( state );

	if ( state.isLightingEnabled() && state.isPerVertexLightingEnabled() )
	{
		m_code += GLSLHelpers::generate_lights( state ) + "\n";
		m_code += GLSLHelpers::generateFunction_flight( state ) + "\n";
	}

	if ( ftexgen )	m_code += GLSLHelpers::generateFunction_ftexgen(state) + "\n";

// @todo generateFunction_fVertexAttrib()  and generate_vertexAttribDeclaration()

	// MAIN
	m_code +=
	"\n"
	"void main( void )\n"
	"{\n";

	if ( state.isLightingEnabled() == false || state.isPerVertexLightingEnabled() )
	{
		m_code += 
		"	vec4	ecPosition;\n"		// Eye-coordinate position of vertex
		"	vec3	ecNormal;\n"
		"\n";
	}
	// else nothing

	m_code +=
	"	gl_Position	= ftransform();\n"
	"\n";

	m_code +=
	"	ecPosition	= gl_ModelViewMatrix * gl_Vertex;\n"
	"	ecNormal	= fnormal();\n"
	"\n";

	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
			// Calls flight()
			m_code += 
			"	flight( ecPosition, ecNormal );\n"
			"\n"
			"	gl_FrontColor			= vec4(accumColor.rgb, gl_Color.a);\n"
			"	gl_FrontSecondaryColor	= vec4(accumSecondaryColor.rgb, 0.0);\n";

			if ( state.isTwoSidedLightingEnabled() )
			{
				m_code +=
				"	gl_BackColor			= vec4(accumBackColor.rgb, gl_Color.a);\n"
				"	gl_BackSecondaryColor	= vec4(accumBackSecondaryColor.rgb, 0.0);\n";
			}
		}
		else
		{
			/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
			{
				// pixel lighting and VertexShape::color4, so gl_Color must be transfered to fragment program.
				// m_code += "	mglColor = gl_Color;\n";
			}*/

			m_code +=	
			"	gl_FrontColor			= gl_Color;\n"
			"	gl_FrontSecondaryColor	= vec4(gl_SecondaryColor.rgb, 0.0);\n";

			if ( state.isTwoSidedLightingEnabled() )
			{
				m_code +=
				"	gl_BackColor			= gl_Color;\n"
				"	gl_BackSecondaryColor	= vec4(gl_SecondaryColor.rgb, 0.0);\n";
			}
//			// else nothing to do
		}
	}
	else
	{
		// no lighting
		m_code +=
		"	gl_FrontColor			= gl_Color;\n"
		"	gl_FrontSecondaryColor	= vec4(gl_SecondaryColor.rgb, 0.0);\n";

		if ( state.isTwoSidedLightingEnabled() )
		{
			m_code +=
			"	gl_BackColor			= gl_Color;\n"
			"	gl_BackSecondaryColor	= vec4(gl_SecondaryColor.rgb, 0.0);\n";
		}
	}

	/*if ( glIsEnabled(GL_FOG) )
	{
		m_code += "	gl_FogFragCoord = ffog( ecPosition.z );\n";
	}*/

	if ( ftexgen )
	{
		m_code += "	ftexgen( ecPosition, ecNormal );\n";
	}


	/*if (	glIsEnabled(GL_CLIP_PLANE0) || glIsEnabled(GL_CLIP_PLANE1) ||
		glIsEnabled(GL_CLIP_PLANE2) || glIsEnabled(GL_CLIP_PLANE3) ||
		glIsEnabled(GL_CLIP_PLANE4) || glIsEnabled(GL_CLIP_PLANE5)	)*/
	if ( state.isEnabled( GLSLState::CLIPPING_PLANE ) )
	{
		m_code += "	gl_ClipVertex = ecPosition;\n";
	}

	m_code += "}\n";

	return true;
}



} // namespace engine

} // namespace vgeGL
