// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/PostProcessing.hpp"


#include <vgd/node/PostProcessing.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"



namespace
{

const std::string horizKernel13 =
"vec2 horizKernel13[13] = vec2[13](\n"
"vec2(-6, 0),\n"
"vec2(-5, 0),\n"
"vec2(-4, 0),\n"
"vec2(-3, 0),\n"
"vec2(-2, 0),\n"
"vec2(-1, 0),\n"
"vec2(0, 0),\n"
"vec2(1, 0),\n"
"vec2(2, 0),\n"
"vec2(3, 0),\n"
"vec2(4, 0),\n"
"vec2(5, 0),\n"
"vec2(6, 0)\n"
");\n"
"\n";


const std::string vertKernel13 =
"vec2 vertKernel13[13] = vec2[13](\n"
"vec2( 0, -6 ),\n"
"vec2( 0, -5 ),\n"
"vec2( 0, -4 ),\n"
"vec2( 0, -3 ),\n"
"vec2( 0, -2 ),\n"
"vec2( 0, -1 ),\n"
"vec2( 0, 0 ),\n"
"vec2( 0, 1 ),\n"
"vec2( 0, 2 ),\n"
"vec2( 0, 3 ),\n"
"vec2( 0, 4 ),\n"
"vec2( 0, 5 ),\n"
"vec2( 0, 6 )\n"
");\n"
"\n";


const std::string kernel4 =
"vec2 kernel4[4] = vec2[4](\n"
"vec2(0, 1), vec2(1, 0), vec2(0, -1), vec2(-1, 0)\n"
");\n"
"\n";


const std::string gaussianWeights13 =
"const float gaussianWeights13[13] = float[13](\n"
"0.002216, 0.008764, 0.026995, 0.064759, 0.120985,\n"
"0.176033, 0.199471, 0.176033, 0.120985, 0.064759,\n"
"0.026995, 0.008764, 0.002216"
");\n"
"\n";


const std::string saturate =
"float saturate( float value )\n"
"{\n"
"	return clamp( value, 0.0, 1.0);\n"
"}\n"
"\n";



//////////////
// Identity //
//////////////

const std::string applyIdentity( 
	"	color = texture( texMap2D[0], mgl_TexCoord[0].xy);\n" );


/////////////////////////////////////////////
// Converts colored value to black & white //
/////////////////////////////////////////////

const std::string colorToMonochrome =
"float colorToMonochrome( vec4 color )\n"
"{\n"
"	vec3 luminanceConversion = vec3( 0.2125, 0.7154, 0.0721 );\n"
"\n"
"	return dot( vec3(color), luminanceConversion );\n"
"}\n"
"\n"
"float colorToMonochrome( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec4 color = texture( texMap, texCoord );\n"
"	return colorToMonochrome(color);\n"
"}\n"
"\n\n\n";

const std::string applyColorToMonochrome( 
	"	color = vec4( colorToMonochrome(texMap2D[0], mgl_TexCoord[0].xy) );\n" );


/////////////////////////////////////
// Converts colored value to sepia //
/////////////////////////////////////
const std::string colorToSepia =
"const vec3 lightColor	= vec3( 1.0, 0.9, 0.5 );\n"
"const vec3 darkColor	= vec3( 0.2, 0.05, 0.0 );\n"
"const vec3 grayXfer	= vec3( 0.3, 0.59, 0.11 );\n"
"vec4 colorToSepia( sampler2D texMap, vec2 texCoord, float desaturate, float toning )\n"
"{\n"
"	vec4	color		= texture( texMap, texCoord );\n"
"\n"
"	vec3	sceneColor	= lightColor * color.rgb;\n"
"	float	gray		= dot( grayXfer, sceneColor );\n"
"	vec3	muted		= mix( sceneColor, vec3(gray), desaturate );\n"
"	vec3	sepia		= mix( darkColor, lightColor, gray );\n"
"	vec3	result		= mix( muted, sepia, toning );\n"
"	return vec4( result.xyz, 1.0);\n"
"}\n"
"\n\n\n";


const std::string applyColorToSepia(
	"	color = vec4( colorToSepia(texMap2D[0], mgl_TexCoord[0].xy, param4f0.x, param4f0.y) );\n" );


///////////////////////////////
// Inverts the colored value //
///////////////////////////////

const std::string colorInverse =
"vec4 colorInverse( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec4 color = texture( texMap, texCoord );\n"
"	return vec4(1.0) - color;\n"
"}\n"
"\n\n\n";

const std::string applyColorInverse( 
	"	color = colorInverse( texMap2D[0], mgl_TexCoord[0].xy );\n" );

////////////////////
// SCALE_AND_BIAS //
////////////////////

const std::string scaleAndBias =
"vec4 scaleAndBias( sampler2D texMap, vec2 texCoord, vec4 scale, vec4 bias )\n"
"{\n"
"	vec4 color = texture( texMap, texCoord );\n"
"	return (color * scale) + bias;\n"
"}\n"
"\n\n\n";

const std::string applyScaleAndBias( 
	"	color = scaleAndBias( texMap2D[0], mgl_TexCoord[0].xy, param4f0, param4f1 );\n" );


///////////////////////////////////////////////////////////////////////////////////
// Blurs an image horizontally using weights that follow a Gaussian distribution //
///////////////////////////////////////////////////////////////////////////////////

const std::string blurHoriz =
"vec4 blurHoriz( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec2 texSize = textureSize( texMap, 0 );\n"
"	vec4 color = vec4(0.0);\n"
"	for( int i = 0; i < 13; ++i )\n"
"	{\n"
"		color += texture( texMap, texCoord + horizKernel13[i].xy/texSize ) * gaussianWeights13[i];\n"
"	}\n"
"	return color;\n"
"}\n"
"\n\n\n";

const std::string applyBlurHoriz( 
	"	color = blurHoriz( texMap2D[0], mgl_TexCoord[0].xy );\n" );


/////////////////////////////////////////////////////////////////////////////////
// Blurs an image vertically using weights that follow a Gaussian distribution //
/////////////////////////////////////////////////////////////////////////////////

const std::string blurVert =
"vec4 blurVert( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec2 texSize = textureSize( texMap, 0 );\n"
"	vec4 color = vec4(0.0);\n"
"	for( int i = 0; i < 13; ++i )\n"
"	{\n"
"		color += texture( texMap, texCoord + vertKernel13[i].xy/texSize ) * gaussianWeights13[i];\n"
"	}\n"
"	return color;\n"
"}\n"
"\n\n\n";

const std::string applyBlurVert( 
	"	color = blurVert( texMap2D[0], mgl_TexCoord[0].xy );\n" );


/////////////////////////////////////////////////////////////////////////////////////////////////
// Amplifies and blurs an image horizontally using weights that follow a gaussian distribution //
/////////////////////////////////////////////////////////////////////////////////////////////////

const std::string bloomHoriz = 
"vec4 bloomHoriz( sampler2D texMap, vec2 texCoord, float bloomScale )\n"
"{\n"
"	return blurHoriz( texMap, texCoord ) * bloomScale;\n"
"}\n"
"\n";

const std::string applyBloomHoriz(
	"	color = bloomHoriz( texMap2D[0], mgl_TexCoord[0].xy, param1f0 );\n" );


///////////////////////////////////////////////////////////////////////////////////////////////
// Amplifies and blurs an image vertically using weights that follow a gaussian distribution //
///////////////////////////////////////////////////////////////////////////////////////////////

const std::string bloomVert = 
"vec4 bloomVert( sampler2D texMap, vec2 texCoord, float bloomScale )\n"
"{\n"
"	return blurVert( texMap, texCoord ) * bloomScale;\n"
"}\n"
"\n\n\n";

const std::string applyBloomVert(
	"	color = bloomVert( texMap2D[0], mgl_TexCoord[0].xy, param1f0 );\n" );


///////////////////////////////////////
// Detects edges and highlights them //
///////////////////////////////////////

const std::string colorEdgeDetect =
"vec4 colorEdgeDetect( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec2 texSize = textureSize( texMap, 0 );\n"	
"	vec4 orig = texture( texMap, texCoord );\n"
"	vec4 sum = vec4(0);\n"
"\n"
"	for( int i = 0; i < 4; ++i )\n"
"	{\n"
"		sum += ( abs( orig - texture( texMap, texCoord + kernel4[i]/texSize ) ) - 0.5 ) * 1.2 + 0.5;\n"
"	}\n"
"	return vec4( clamp( colorToMonochrome(sum), 0.0, 1.0 ) * 5.0 );\n"
"}\n"
"\n\n\n";

const std::string applyColorEdgeDetect( 
	"	color = colorEdgeDetect( texMap2D[0], mgl_TexCoord[0].xy );\n" );


//////////////////
// DOWN_FILTER4 //
//////////////////

const std::string downFilter4 =
"vec2 downFilter4Kernel[16] = vec2[16](\n"
"vec2( 1.5, -1.5 ), vec2( 1.5, -0.5 ), vec2( 1.5, 0.5 ), vec2( 1.5, 1.5 ),\n"
"vec2( 0.5, -1.5 ), vec2( 0.5, -0.5 ), vec2( 0.5, 0.5 ), vec2( 0.5, 1.5 ),\n"
"vec2( -0.5, -1.5 ), vec2( -0.5, -0.5 ), vec2( -0.5, 0.5 ), vec2( -0.5, 1.5 ),\n"
"vec2( -1.5, -1.5 ), vec2( -1.5, -0.5 ), vec2( -1.5, 0.5 ), vec2( -1.5, 1.5 )\n"
");\n"
"\n"
"// Performs a high-pass filter on the texture and scale down.\n"
"vec4 downFilter4( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec2 texSize = textureSize( texMap, 0 );\n"
"	vec4 color = vec4(0);\n"
"	for( int i = 0; i < 16; ++i )\n"
"	{\n"
"		color += texture( texMap, texCoord + downFilter4Kernel[i]/texSize );\n"
"	}\n"
"	return color / 16.0;\n"
"}\n"
"\n\n\n";

const std::string applyDownFilter4( 
	"	color = downFilter4( texMap2D[0], mgl_TexCoord[0].xy );\n" );


//////////////////////////////
// Scales images up 4 times //
//////////////////////////////

const std::string upFilter4 = 
"// Performs up filtering to scale the image to its original size\n"
"vec4 upFilter4( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	return texture( texMap, texCoord );\n"
"}\n"
"\n\n\n";

const std::string applyUpFilter4( 
	"	color = upFilter4( texMap2D[0], mgl_TexCoord[0].xy );\n" );


//////////
// OVER //
//////////

const std::string over  =
"vec4 over( sampler2D texMap0, sampler2D texMap1, vec2 texCoord )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	if ( length(color0.rgb) > 0 )\n"
"	{\n"
//"		return vec4(color0.rgb, color0.r);\n"
"		return color0;\n"
"	}\n"
"	else\n"
"	{\n"
//"		return vec4(color1.rgb, color1.r);\n"
"		return color1;\n"
"	}\n"
"}\n"
"\n\n\n";

const std::string applyOver(
	"	color = over( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy );\n" );



/////////
// ADD //
/////////

const std::string add =
"vec4 add( sampler2D texMap0, sampler2D texMap1, vec2 texCoord )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	return color0 + color1;\n"
"}\n"
"\n\n\n";

const std::string applyAdd(
	"	color = add( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy );\n" );


/////////
// SUB //
/////////

const std::string sub =
"vec4 sub( sampler2D texMap0, sampler2D texMap1, vec2 texCoord )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	return color0 - color1;\n"
"}\n"
"\n\n\n";

const std::string applySub(
	"	color = sub( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy );\n" );


///////////////////
// MIX_AND_SCALE //
///////////////////

const std::string mixAndScale =
"vec4 mixAndScale( sampler2D texMap0, sampler2D texMap1, vec2 texCoord, float a, float scale )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	return mix(color0, color1, a) * scale;\n"
"}\n"
"\n\n\n";

const std::string applyMixAndScale(
	"	color = mixAndScale( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy, param4f0.x, param4f0.y );\n" );


////////////////////////
// ALPHAMIX_AND_SCALE //
////////////////////////

const std::string alphamixAndScale =
"vec4 alphamixAndScale( sampler2D texMap0, sampler2D texMap1, vec2 texCoord, float scale )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	return mix(color0, color1, color1.a) * scale;\n"
"}\n"
"\n\n\n";

const std::string applyAlphamixAndScale(
	"	color = alphamixAndScale( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy, param1f0 );\n" );


////////////////////////
// COMBINE2_AND_SCALE //
////////////////////////

const std::string combine2AndScale =
"vec4 combine2AndScale( sampler2D texMap0, sampler2D texMap1, vec2 texCoord, float a, float b, float scale )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	return (color0 * a + color1 * b) * scale;\n"
"}\n"
"\n\n\n";

const std::string applyCombine2AndScale(
	"	color = combine2AndScale( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy, param4f0.x, param4f0.y, param4f0.z );\n" );


////////////////////////
// COMBINE3_AND_SCALE //
////////////////////////

const std::string combine3AndScale =
"vec4 combine3AndScale( sampler2D texMap0, sampler2D texMap1, sampler2D texMap2, vec2 texCoord, vec4 param )"
"{\n"
"	vec4 color0 = texture( texMap0, texCoord );\n"
"	vec4 color1 = texture( texMap1, texCoord );\n"
"	vec4 color2 = texture( texMap2, texCoord );\n"
"	return (color0 * param[0] + color1 * param[1] + color2 * param[2] ) * param[3];\n"
"}\n"
"\n\n\n";

const std::string applyCombine3AndScale(
	"	color = combine3AndScale( texMap2D[0], texMap2D[1], texMap2D[2], mgl_TexCoord[0].xy, param4f0 );\n" );



}



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( PostProcessing );



const vge::handler::Handler::TargetVector PostProcessing::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::PostProcessing::getClassIndexStatic() );

	return targets;
}



void PostProcessing::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::PostProcessing* >(node) != 0 );
	vgd::node::PostProcessing *postProcessingNode = static_cast< vgd::node::PostProcessing* >(node);

	// Updates engine state
	if ( glEngine->isGLSLEnabled() /*&& glEngine->isTextureMappingEnabled() */)
	{
		using vgeGL::engine::GLSLState;
		GLSLState& glslState = glEngine->getGLSLState();

		vgd::Shp< GLSLState::PostProcessingState > postProcessingState( new GLSLState::PostProcessingState(postProcessingNode) );

		const int multiAttributeIndex = computeMultiAttributeIndex( postProcessingNode, glslState.postProcessing );
		glslState.postProcessing.setState( multiAttributeIndex, postProcessingState );
	}

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



void PostProcessing::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void PostProcessing::setToDefaults()
{
}



std::pair< std::string, std::string > PostProcessing::getFilter( vgd::node::PostProcessing * postProcessing, const vgd::node::PostProcessing::FilterValueType& filter )
{
	if ( filter == vgd::node::PostProcessing::IDENTITY )
	{
		return std::make_pair( std::string(""), applyIdentity );
	}
	else if ( filter == vgd::node::PostProcessing::COLOR_TO_MONOCHROME )
	{
		return std::make_pair( colorToMonochrome, applyColorToMonochrome );
	}
	else if ( filter == vgd::node::PostProcessing::COLOR_TO_SEPIA )
	{
		return std::make_pair( colorToSepia, applyColorToSepia );
	}
	else if ( filter == vgd::node::PostProcessing::COLOR_INVERSE )
	{
		return std::make_pair( colorInverse, applyColorInverse );
	}
	else if ( filter == vgd::node::PostProcessing::SCALE_AND_BIAS )
	{
		return std::make_pair( scaleAndBias, applyScaleAndBias );
	}
	else if ( filter == vgd::node::PostProcessing::BLUR_HORIZ )
	{
		return std::make_pair( horizKernel13 + gaussianWeights13 + blurHoriz, applyBlurHoriz );
	}
	else if ( filter == vgd::node::PostProcessing::BLUR_VERT )
	{
		return std::make_pair( vertKernel13 + gaussianWeights13 + blurVert, applyBlurVert );
	}
	else if ( filter == vgd::node::PostProcessing::BLOOM_HORIZ )
	{
		return std::make_pair( horizKernel13 + gaussianWeights13 + blurHoriz + bloomHoriz, applyBloomHoriz );
	}
	else if ( filter == vgd::node::PostProcessing::BLOOM_VERT )
	{
		return std::make_pair( vertKernel13 + gaussianWeights13 + blurVert + bloomVert, applyBloomVert );
	}
	else if ( filter == vgd::node::PostProcessing::COLOR_EDGE_DETECT )
	{
		return std::make_pair( colorToMonochrome + kernel4 + colorEdgeDetect, applyColorEdgeDetect );
	}
	else if ( filter == vgd::node::PostProcessing::DOWN_FILTER4 )
	{
		return std::make_pair( downFilter4, applyDownFilter4 );
	}
	else if ( filter == vgd::node::PostProcessing::UP_FILTER4 )
	{
		return std::make_pair( upFilter4, applyUpFilter4 );
	}
	else if ( filter == vgd::node::PostProcessing::OVER )
	{
		return std::make_pair( over, applyOver );
	}
	else if ( filter == vgd::node::PostProcessing::ADD )
	{
		return std::make_pair( add, applyAdd );
	}
	else if ( filter == vgd::node::PostProcessing::SUB )
	{
		return std::make_pair( sub, applySub );
	}	
	else if ( filter == vgd::node::PostProcessing::MIX_AND_SCALE )
	{
		return std::make_pair( mixAndScale, applyMixAndScale );
	}
	else if ( filter == vgd::node::PostProcessing::ALPHAMIX_AND_SCALE )
	{
		return std::make_pair( alphamixAndScale, applyAlphamixAndScale );
	}
	else if ( filter == vgd::node::PostProcessing::COMBINE2_AND_SCALE )
	{
		return std::make_pair( combine2AndScale, applyCombine2AndScale );
	}
	else if ( filter == vgd::node::PostProcessing::COMBINE3_AND_SCALE )
	{
		return std::make_pair( combine3AndScale, applyCombine3AndScale );
	}
	else if ( filter == vgd::node::PostProcessing::NO_FILTER )
	{
		return std::make_pair( "", "color = texture( texMap2D[0], mgl_TexCoord[0].xy );\n" );
	}
	else if ( filter == vgd::node::PostProcessing::CUSTOM_FILTER )
	{
		const std::string definition	= postProcessing->getCustomFilterDefinition();
		const std::string apply			= postProcessing->getCustomFilterApply();

		if ( apply.empty() )
		{
			vgLogDebug("PostProcessing.filter is equal to CUSTOM_FILTER, but no custom filter is defined.");
			return std::make_pair( "", "color = texture( texMap2D[0], mgl_TexCoord[0].xy );\n" );
		}
		else
		{
			// @todo documentation for all conventions in shaders (texture.function, PostProcesing.custom*...)
			// @todo doc about the predefined functions (horizKernel13 + ... + colorEdgeDetect)
			return std::make_pair(	horizKernel13 + vertKernel13 + kernel4 + gaussianWeights13 +
									saturate + colorToMonochrome + blurHoriz + blurVert + bloomHoriz + bloomVert + colorEdgeDetect +
									definition, apply );
		}
	}
	else
	{
		assert( false );
		return std::make_pair( "", "" );
	}
}



std::pair< float, float > PostProcessing::getScale( const vgd::node::PostProcessing::FilterValueType& filter )
{
	if ( filter == vgd::node::PostProcessing::DOWN_FILTER4 )
	{
		return std::make_pair( 1.f, 0.25f );
	}
	else if ( filter == vgd::node::PostProcessing::UP_FILTER4 )
	{
		return std::make_pair( 1.f, 4.f );
	}
	else
	{
		return std::make_pair( 1.f, 1.f );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
