// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/FragmentShaderGenerator.hpp"

#include <vgd/node/Program.hpp>
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

	// Clears the code repository
	m_decl.clear();
	m_code1.clear();
	m_code2.clear();

	// DECLARATIONS
	m_decl += GLSLHelpers::getVersionDecl();
//				"#pragma optimize (on)\n"
//				"#pragma debug (off)\n"	
//				"#pragma optimize (off)\n"
//				"#pragma debug (on)\n"
				//"\n";

	// UNIFORMS
	m_decl += GLSLHelpers::getVGSDKUniformDecl();

	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape
	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "in" ); // @todo FIXME: only to retrieve ftexgen declaration (mgl_TexCoord...)
	std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	m_decl += code_samplers.first;

	// INPUTS
	m_decl += "// INPUTS\n";
	m_decl += code_ftexgen.first;
	m_code1 += code_samplers.second;

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		vgAssert( program );

		std::string shaderStr;
		program->getShader( vgd::node::Program::FRAGMENT, shaderStr );

		m_code1 = shaderStr;

		return true;
	}

	if ( state.isPerPixelLightingEnabled() )
	{
		if ( state.isEnabled( FLAT_SHADING ) )
		{
			m_decl += 
			"flat in vec4 ecPosition;\n"
			"flat in vec3 ecNormal;\n\n";
		}
		else
		{
			m_decl += 
			"in vec4 ecPosition;\n"
			"in vec3 ecNormal;\n\n";

			/*if ( state.isEnabled( COLOR4_BIND_PER_VERTEX ) )
			{
				m_decl += "in vec4 mglColor;\n\n";
			}*/
		}

		m_decl += "// LOCAL VARIABLES\n";
		m_decl += GLSLHelpers::generate_lightAccumulators( state ) + '\n';
	}
	// else nothing

	// OUTPUT
	m_decl += "// OUTPUTS\n";

	// FRAGMENT_DECLARATIONS
	const std::string fragmentDeclaration = state.getShaderStage( GLSLState::FRAGMENT_DECLARATIONS );
	if ( !fragmentDeclaration.empty() )				m_decl += fragmentDeclaration;

	const std::string& fragmentOutputDeclarationStage = state.getShaderStage( GLSLState::FRAGMENT_OUTPUT_DECLARATION );
	if ( !fragmentOutputDeclarationStage.empty() )	m_decl += fragmentOutputDeclarationStage;

	// FUNCTIONS
	if ( state.isLightingEnabled() && state.isPerPixelLightingEnabled() )
	{
		m_code1 += GLSLHelpers::generateFunctions_lights( state ) + '\n';
		m_code1 += GLSLHelpers::generateFunction_flight( state ) + '\n';
	}

	// MAIN
	m_code2 += 
	"void main( void )\n"
	"{\n"
	"	vec4 color;\n";

	// texture lookup
	std::string textureLookup;
	if ( has_ftexgen ) textureLookup += GLSLHelpers::generate_fragmentShader_texLookups( state );

	if ( state.isLightingEnabled() == false || state.isPerVertexLightingEnabled() )
	{
		m_code2 +=
		"\n"
		"	color = gl_FrontMaterial.diffuse;\n" +
			textureLookup +
		"	color += gl_SecondaryColor;\n"
		"	color = vec4(color.rgb, gl_FrontMaterial.diffuse.a);\n";
	}
	else
	{
		assert( state.isLightingEnabled() );
		assert( state.isPerPixelLightingEnabled() );

		// Calls flight()
		m_code2 +=
		"\n"
		"	vec3 normal = normalize(ecNormal);\n"
		"	flight( ecPosition, normal );\n"
		"\n";

		if ( state.isTwoSidedLightingEnabled() )
		{
			m_code2 +=
			"	if ( gl_FrontFacing )\n"
			"	{\n"
			"		color = accumColor;\n" +
					textureLookup +
			"		color = vec4( (color + accumSecondaryColor).rgb, gl_FrontMaterial.diffuse.a );\n"
			"	}\n"
			"	else\n"
			"	{\n"
			"		color = accumBackColor ;\n" +
					textureLookup +
			"		color = vec4( (color + accumBackSecondaryColor).rgb, gl_FrontMaterial.diffuse.a );\n"
			"	}\n";
		}
		else
		{
			m_code2 +=
			"	color = accumColor;\n" +
				textureLookup +
			"	color = vec4( (color + accumSecondaryColor).rgb, gl_FrontMaterial.diffuse.a );\n"; // @todo FIXME gl_FrontMaterial.diffuse.a <=> gl_Color.a ? 
		}
	}

	const std::string& fragmentOutputStage = state.getShaderStage( GLSLState::FRAGMENT_OUTPUT );
	if ( !fragmentOutputStage.empty() )
	{
		m_code2 += fragmentOutputStage;
	}
	/*else
	{

// @todo DirectPostProcessing node vs PostProcessing (for ping-pong post-process).
/*	// sepia
	m_code2 +=
	"	// Sepia colors\n"
	"	vec4 Sepia1 = vec4( 0.2, 0.05, 0.0, 1.0 );\n"
	"	vec4 Sepia2 = vec4( 1.0, 0.9, 0.5, 1.0 );\n"
	"	float SepiaMix = dot(vec3(0.3, 0.59, 0.11), vec3(gl_FragData[0]));\n"
	"	gl_FragData[0] = mix(gl_FragData[0], vec4(SepiaMix), vec4(0.5));\n"
	"	vec4 Sepia = mix(Sepia1, Sepia2, SepiaMix);\n"
	"	gl_FragData[0] = Sepia;\n";
	//"	gl_FragData[0] = mix(gl_FragData[0], Sepia, 1.0);\n";

	// grid effect
	m_code2 +=
	"	if ( mod(gl_FragCoord.x, 2.0) > 1.0 && mod(gl_FragCoord.y, 2.0) > 1.0	)\n"
	"	{\n"
	"		gl_FragData[0] = vec4(0.5,0,1,0);\n"
	"		discard;\n"
	"	}\n"
	"	else\n"
	"	{\n"
	"		gl_FragData[0] = color;\n"
	"	}\n"
	}*/

	m_code2 += "}\n";

	return true;
}



} // namespace engine

} // namespace vgeGL

