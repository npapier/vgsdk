// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/VertexShaderGenerator.hpp"

#include "vgeGL/engine/Engine.hpp"



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

	//
	const bool ftexgen = state.getNumTexture() > 0;	// @todo Should be the number of texCoord in VertexShape

	// Clears the code repository
	m_code.clear();

	// DECLARATIONS
	if ( state.isLightingEnabled() )
	{
		if ( state.isPerVertexLightingEnabled() )
		{
			m_code += GLSLHelpers::generate_lightAccumulators( state ) + "\n";
		}
		else
		{
			m_code += 
			"varying vec4 ecPosition;\n"
			"varying vec3 ecNormal;\n"
			"\n";
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

	if ( ftexgen )
		m_code += GLSLHelpers::generateFunction_ftexgen(state) + "\n";

	// MAIN
	m_code +=
	"\n"
	"void main( void )\n"
	"{\n";

	if ( state.isLightingEnabled() == false || state.isPerVertexLightingEnabled() )
	{
		m_code += 
		//"	float	alphaFade = 1.0;\n"
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
			"	gl_FrontColor			= accumColor;\n"			// * alphaFace
			"	gl_FrontSecondaryColor	= accumSecondaryColor;\n";

			if ( state.isTwoSidedLightingEnabled() )
			{
				m_code +=
				"	gl_BackColor			= accumBackColor;\n"
				"	gl_BackSecondaryColor	= accumBackSecondaryColor;\n";
			}
		}
		// else per pixel lighting, so nothing to do
	}
	else
	{
		// no lighting
		m_code +=
		"	gl_FrontColor			= gl_Color;\n"
		"	gl_FrontSecondaryColor	= gl_SecondaryColor;\n";

		if ( state.isTwoSidedLightingEnabled() )
		{
			m_code +=
			"	gl_BackColor			= gl_Color;\n"
			"	gl_BackSecondaryColor	= gl_SecondaryColor;\n";
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
