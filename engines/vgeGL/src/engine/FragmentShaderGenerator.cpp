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

	// Clears the code repository
	m_code.clear();

	// DECLARATIONS
	if ( state.isPerPixelLightingEnabled() )
	{
		m_code += 
		"varying vec4 ecPosition;\n"
		"varying vec3 ecNormal;\n\n";

		m_code += GLSLHelpers::generate_lightAccumulators( state ) + '\n';
	}
	// else nothing

	if ( ftexgen )	m_code += GLSLHelpers::generate_samplers( state ) + '\n';

	// FUNCTIONS
	if ( state.isLightingEnabled() && state.isPerPixelLightingEnabled() ) 
	{
		m_code += GLSLHelpers::generate_lights( state ) + '\n';
		m_code += GLSLHelpers::generateFunction_flight( state ) + '\n';
	}

	// MAIN
	m_code += 
	"void main( void )\n"
	"{\n";
	//"	float	alphaFade = 1.0;\n";

	// texture lookup
	std::string textureLookup;

	if ( ftexgen ) textureLookup += GLSLHelpers::generate_texLookups( state );

	if ( state.isLightingEnabled() == false || state.isPerVertexLightingEnabled() )
	{
		m_code +=
		"	vec4 color = gl_Color;\n" +
		textureLookup +
		"	color += gl_SecondaryColor;\n"
		"	gl_FragColor = color;\n"; //* alphaFade
	}
	else
	{
		assert( state.isLightingEnabled() );
		assert( state.isPerPixelLightingEnabled() );

		// Calls flight()
		m_code +=
		"	vec3 normal = normalize(ecNormal);\n"
		"\n"
		"	flight( ecPosition, normal );\n"
		"\n";

		if ( state.isTwoSidedLightingEnabled() )
		{
			m_code +=
			"	if ( gl_FrontFacing )\n"
			"	{\n"
			"		vec4 color = accumColor;\n" +
					textureLookup +
			"		gl_FragColor = color + accumSecondaryColor;\n"//clamp( color * alphaFade, 0.0, 1.0 ) ;\n";
			"	}\n"
			"	else\n"
			"	{\n"
			"		vec4 color = accumBackColor ;\n" +
					textureLookup +
			"		gl_FragColor = color + accumBackSecondaryColor;\n"//clamp( color * alphaFade, 0.0, 1.0 ) ;\n";
			"	}\n";
		}
		else
		{
			m_code +=
			"	vec4 color = accumColor;\n" +
				textureLookup +
			"	gl_FragColor = color + accumSecondaryColor;\n";//clamp( color, 0.0, 1.0 ) * alphaFade;\n";
		}
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