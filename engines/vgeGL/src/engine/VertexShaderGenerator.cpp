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

	//
	m_code.clear();

	// DECLARATIONS
	if ( state.isPerVertexLightingEnabled() )
	{
		m_code += GLSLHelpers::generate_lightAccumulators();
	}
	else
	{
		m_code += 
		"varying vec4 ecPosition;\n"
		"varying vec3 ecNormal;\n";
	}

	// FUNCTIONS
	m_code += GLSLHelpers::generateFunction_fnormal( state.isLightingEnabled() );

	if ( state.isPerVertexLightingEnabled() )	m_code += GLSLHelpers::generate_lights();

	if ( ftexgen )	m_code += "\n" + GLSLHelpers::generateFunction_ftexgen(state);

	// LIGHTING
	if ( state.isPerVertexLightingEnabled() )
	{
		m_code += GLSLHelpers::generateFunction_flight( state );
	}

	// MAIN
	m_code +=
	"\n"
	"void main( void )\n"
	"{\n";

	if ( state.isPerVertexLightingEnabled() )
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
	"\n"
	"	ecPosition	= gl_ModelViewMatrix * gl_Vertex;\n"
	"	ecNormal	= fnormal();\n";

	if ( state.isLightingEnabled() && state.isPerVertexLightingEnabled() )
	{
		// Calls flight()
		m_code += "	flight( ecPosition, ecNormal );\n";

		//
		m_code +=
		"\n"
		"	vec4 color =	gl_FrontLightModelProduct.sceneColor +\n"
		"					Ambient * gl_FrontMaterial.ambient +\n"
		"					Diffuse * gl_FrontMaterial.diffuse;\n";

		m_code += 
//		"	gl_FrontSecondaryColor = clamp( Specular * gl_FrontMaterial.specular, 0.0, 1.1 );\n"; // GL_SEPARATE_SPECULAR_COLOR
		"	gl_FrontSecondaryColor = Specular * gl_FrontMaterial.specular;\n"; // GL_SEPARATE_SPECULAR_COLOR
		// GL_SEPARATE_SPECULAR_COLOR == false => "	 color += Specular * gl_FrontMaterial.specular;\n"

		m_code +=
		//"	gl_FrontColor = clamp(color, 0.0, 1.0);\n";// * alphaFade;\n";
		"	gl_FrontColor = color;\n";// * alphaFade;\n";
	}
	/*else
	{
		m_code += "	gl_FrontColor = gl_Color;\n";
	}*/

	/*if ( glIsEnabled(GL_FOG) )
	{
		m_code += "	gl_FogFragCoord = ffog( ecPosition.z );\n";
	}*/

	if ( ftexgen )
	{
		m_code += 
		"\n"
		"	ftexgen( ecPosition, ecNormal );\n";
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
