// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, Nicolas Papier.
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
	m_decl += GLSLHelpers::getVersionDecl( state );
	m_decl += GLSLHelpers::getDefines( state );

	// UNIFORMS
	m_decl += GLSLHelpers::getVGSDKUniformDecl( state );

	const bool has_ftexgen = engine->isTextureMappingEnabled() && state.textures.getNum() > 0;	// @todo Should be the number of texCoord in VertexShape

	std::pair< std::string, std::string > code_ftexgen	= GLSLHelpers::generateFunction_ftexgen(state, "in", "TexCoords", "inTexCoord", false, true ); // @todo FIXME: only to retrieve ftexgen declaration (mgl_TexCoord...)
	std::pair< std::string, std::string > code_samplers	= GLSLHelpers::generate_samplers( state );

	m_decl += code_samplers.first;

	// INPUTS
	m_decl += "// INPUTS\n";

	if ( state.isLightingEnabled() /*PerPixelLightingEnabled()*/ )
	{
		if ( state.isEnabled( FLAT_SHADING ) ) m_decl +=  "flat ";
		m_decl += "in vec4 ecPosition;\n";

		if ( state.isEnabled( FLAT_SHADING ) ) m_decl +=  "flat ";
		m_decl += "in vec3 ecNormal;\n\n"; // @todo not if bump
	}

	if ( has_ftexgen )
	{
		m_decl += code_ftexgen.first;

		m_code1 += code_samplers.second;
	}

	// DECLARATIONS for bumpmapping
	if ( state.isBumpMappingEnabled() )
	{
		m_decl +=	"// Bumpmapping parameters\n"
					"in vec3 ecTangent;\n";

		m_decl += GLSLHelpers::generate_declarationsForBumpmapping();
		m_decl += "in BumpMappingParameters bumpParams;\n";
	}

	// OUTPUT
	m_decl +=	"\n"
				"// OUTPUTS\n";

	// FRAGMENT_DECLARATIONS
	const std::string fragmentDeclaration = state.getShaderStage( GLSLState::FRAGMENT_DECLARATIONS );
	if ( !fragmentDeclaration.empty() )				m_decl += fragmentDeclaration;

	const std::string& fragmentOutputDeclarationStage = state.getShaderStage( GLSLState::FRAGMENT_OUTPUT_DECLARATION );
	if ( !fragmentOutputDeclarationStage.empty() )	m_decl += fragmentOutputDeclarationStage;

	// LOCAL VARIABLES
	if ( state.isLightingEnabled() && state.isPerPixelLightingEnabled() )
	{
		m_decl +=
			"\n"
			"// LOCAL VARIABLES\n";
		m_decl += GLSLHelpers::generate_lightAccumulators( state );
	}

	// FUNCTIONS
	m_code1 +=
		"\n"
		"// FUNCTIONS\n";
	m_code1 += GLSLHelpers::generateFunction_eyeVectorRelated( state );

	if ( state.isLightingEnabled() && state.isPerPixelLightingEnabled() )
	{
		m_code1 += GLSLHelpers::generateFunctions_lights( state ) + '\n';
		m_code1 += GLSLHelpers::generateFunction_flight( state ) + '\n';
	}

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		vgAssert( program != 0 );

		if ( program->getFragmentUse() )
		{
			m_code1 = program->getFragment();
			return true;
		}
	}

	// MAIN
	m_code2 +=
	"// MAIN function\n"
	"void main( void )\n"
	"{\n"
	"	vec4 color;\n\n";

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
		if ( state.isBumpMappingEnabled() == true && state.isPerPixelLightingEnabled())
		{
			m_code2 += "	// Lookup normal from normal map, move from [0,1] to [-1, 1] range and normalize.\n";
			m_code2 += "	vec3 tsNormal = 2.0 * texture(texMap2D[1], mgl_TexCoord[0].st).xyz - 1.0;\n"; // @todo texMap2D[1] for normalMap not generic
			m_code2 += "	tsNormal = normalize(tsNormal);\n\n";
			m_code2 +=  "	flight( ecPosition, tsNormal );\n\n";
		}
		else
		{
			m_code2 += "	vec3 normal = normalize(ecNormal);\n";
			m_code2 +=  "	flight( ecPosition, normal );\n\n";
		}

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
			"	}\n\n";
		}
		else
		{
			m_code2 +=
			"	color = accumColor;\n"
			"	" + textureLookup +
			"	color = vec4( (color + accumSecondaryColor).rgb, gl_FrontMaterial.diffuse.a );\n\n";
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
