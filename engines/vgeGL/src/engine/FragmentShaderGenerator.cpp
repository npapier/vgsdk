// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/FragmentShaderGenerator.hpp"

#include <boost/lexical_cast.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{



// FragmentShaderGenerator
FragmentShaderGenerator::FragmentShaderGenerator()
:	ShaderGenerator( glo::GLSLProgram::FRAGMENT )
{
}



const bool FragmentShaderGenerator::generate( vgeGL::engine::Engine * engine )
{
	// Retrieves the GLSL state
	GLSLState& state = engine->getGLSLState();

	//
	const bool ftexgen = state.getNumTexture() > 0;	// @todo Should be the number of texCoord in VertexShape

	//
	m_code.clear();

	// DECLARATIONS
	if ( state.isPerPixelLightingEnabled() )
	{
		m_code += 
		"varying vec4 ecPosition;\n"
		"varying vec3 ecNormal;\n";

		m_code += GLSLHelpers::generate_lightAccumulators();
	}
	// else nothing

	if ( ftexgen )
	{
		for(	uint	i		= 0,
						iEnd	= state.getMaxTexture();
				i != iEnd;
				++i )
		{
			const std::string strUnit = boost::lexical_cast< std::string >( i );

			const glo::Texture * current = state.getTexture( i );

			if ( current ) // @todo Texturing is enabled if vertex shape contains tex coord and NOT when a texture is defined.
			{
				m_code +=
				"uniform sampler2D texUnit" + strUnit + ";\n";
			}
		}
	}

	// FUNCTIONS
	if ( state.isPerPixelLightingEnabled() )
	{
		m_code += GLSLHelpers::generate_lights();
	}

	// LIGHTING
	if ( state.isPerPixelLightingEnabled() )
	{
		m_code += GLSLHelpers::generateFunction_flight( state );
	}

	// MAIN
	m_code += 
	"\n"
	"void main( void )\n"
	"{\n";
	//"	float	alphaFade = 1.0;\n";

	//
	std::string textureLookup;

	if ( ftexgen )
	{
		for(	uint	i		= 0,
						iEnd	= state.getMaxTexture();
				i != iEnd;
				++i )
		{
			const std::string strUnit = boost::lexical_cast< std::string >( i );

			const glo::Texture * current = state.getTexture( i );

			if ( current ) // @todo Texturing is enabled if vertex shape contains tex coord and NOT when a texture is defined.
			{
				textureLookup +=
				"	color *= texture2D(texUnit" + strUnit + ", gl_TexCoord[" + strUnit + "].xy);\n";
			}
		}
	}

	if ( state.isPerVertexLightingEnabled() )
	{
		m_code +=
		"	vec4 color = gl_Color;\n" +
		textureLookup +
		"	color += gl_SecondaryColor;\n"
		"	gl_FragColor = color;\n"; //* alphaFade
		//"	gl_FragColor = clamp( color, 0.0, 1.0 ) ;\n";	// @todo removes clamp ?
	}
	//else nothing to do

	if ( state.isLightingEnabled() && state.isPerPixelLightingEnabled() )
	{
		m_code += 
		"	ecNormal = normalize(ecNormal);\n"
		"\n";

		// Calls flight()
		m_code += "	flight( ecPosition, ecNormal );\n";

		m_code +=
		"\n"
		"	vec4 color =	gl_FrontLightModelProduct.sceneColor +\n"
		"					Ambient * gl_FrontMaterial.ambient +\n"
		"					Diffuse * gl_FrontMaterial.diffuse;\n";

		m_code +=
		"	vec4 secondaryColor = Specular * gl_FrontMaterial.specular;\n"; // GL_SEPARATE_SPECULAR_COLOR
		// GL_SEPARATE_SPECULAR_COLOR == false => "	 color += Specular * gl_FrontMaterial.specular;\n"

		m_code +=
		textureLookup +
		"	color += secondaryColor;\n"
		"	gl_FragColor = color;\n";//clamp( color, 0.0, 1.0 ) * alphaFade;\n";
	}

	m_code += "}\n";

	// grid effect
	/*m_code +=
	"	if ( mod(gl_FragCoord.x, 2.0) > 1.0 && mod(gl_FragCoord.y, 2.0) > 1.0	)\n"
	"	{\n"
	"		gl_FragColor = vec4(0.5,0,1,0);\n"
	"		discard;\n"
	"	}\n"
	"	else\n"
	"	{\n"
	"		gl_FragColor = color;\n"
	"	}\n"*/

	return true;
}



} // namespace engine

} // namespace vgeGL
