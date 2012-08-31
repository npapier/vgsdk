// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_SHADERGENERATOR_HPP
#define _VGEGL_ENGINE_SHADERGENERATOR_HPP

#include <boost/algorithm/string/replace.hpp>
#include <glo/GLSLProgram.hpp>
#include <vgd/Shp.hpp>
#include <vgd/basic/toString.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Light.hpp>
#include <vgd/node/Texture.hpp>


#include "vgeGL/engine/GLSLState.hpp"

//// @todo gl_Color only in vertexShader and if color4 ?

namespace vgeGL { namespace engine { struct Engine; } }



namespace vgeGL
{

namespace engine
{



/*lazy generation of shaders => call run() on VertexShape node
invalid generator from handlers
count generation during a pass
cache generated shaders at least for a single rendering */

// @todo move GLSLGHelpers
struct GLSLHelpers
{
	// @todo Flags class in vgd::basic



	//
	static const std::string& getVersionDecl()
	{
		static const std::string retVal = "#version 330 compatibility\n\n";

		return retVal;
	}

	static const std::string& getVGSDKUniformDecl()
	{
		static const std::string retVal =	"// UNIFORMS\n"
											"uniform vec4	random;\n"
											"uniform int	time;\n"
											"uniform vec2	nearFar;\n\n";

		return retVal;
	}

	// LIGHTING
	static const std::string& generate_lightAccumulators( const GLSLState& state )
	{
		static const std::string retValNoLighting("");

		static const std::string retValTwoSided = 
		"vec4 accumAmbient = vec4(0.0);\n"
		"vec4 accumDiffuse = vec4(0.0);\n"
		"vec4 accumSpecular = vec4(0.0);\n"
		"\n"
		"vec4 accumColor = vec4(0.0);\n"
		"vec4 accumSecondaryColor = vec4(0.0);\n"
		"vec4 accumBackColor = vec4(0.0);\n"
		"vec4 accumBackSecondaryColor = vec4(0.0);\n"
		"\n";

		static const std::string retVal = 
		"vec4 accumAmbient = vec4(0.0);\n"
		"vec4 accumDiffuse = vec4(0.0);\n"
		"vec4 accumSpecular = vec4(0.0);\n"
		"\n"
		"vec4 accumColor = vec4(0.0);\n"
		"vec4 accumSecondaryColor = vec4(0.0);\n"
		"\n";

		if ( state.isLightingEnabled() == false )
		{
			return retValNoLighting;
		}
		else if ( state.isTwoSidedLightingEnabled() )
		{
			return retValTwoSided;
		}
		else
		{
			return retVal;
		}
	}



	static const std::string generateFunctions_lights( const GLSLState& state )
	{
		std::string retVal;

		// DIRECTIONAL_LIGHT
		if ( state.isEnabled( DIRECTIONAL_LIGHT ) )
		{
			const std::string& directionalLight = GLSLHelpers::generateFunction_directionalLight( state, false );
			retVal += directionalLight + '\n';
		}

		// POINT_LIGHT
		if ( state.isEnabled( POINT_LIGHT ) )
		{
			const std::string& pointLight = GLSLHelpers::generateFunction_pointLight( state, false );
			retVal += pointLight + '\n';
		}

		// SPOT_LIGHT_CASTING_SHADOW
		if (	state.isEnabled( SPOT_LIGHT_CASTING_SHADOW ) &&
				state.getShadowType() != vgd::node::LightModel::SHADOW_OFF )
		{
			const std::string& spotLightFront	= GLSLHelpers::generateFunction_spotLight( state, false /*useBackMaterial*/, true /*castShadow*/);
			// const std::string& spotLightBack	= GLSLHelpers::generateFunction_spotLight( state, true ); @todo
			retVal += spotLightFront + '\n';
			// retVal += spotLightBack; @todo
		}
		else if ( state.isEnabled( SPOT_LIGHT ) )
		// SPOT_LIGHT
		{
			const std::string& spotLightFront = GLSLHelpers::generateFunction_spotLight( state, false /*useBackMaterial*/, false /*castShadow*/ );
			// const std::string& spotLightBack	= GLSLHelpers::generateFunction_spotLight( state, true ); @todo
			retVal += spotLightFront + '\n';
			// retVal += spotLightBack; @todo
		}
		
		return retVal;
	}



	static const std::string& generateFunction_directionalLight( const GLSLState& state, const bool useBackMaterial )
	{
		static std::string retValFront;
		static std::string retValBack;

		if ( retValFront.length() == 0 )
		{
			retValFront = 
				"void directionalLightFront( in int i, in vec3 normal )\n"
				"{\n"
				"	float nDotVP;			// normal . light direction\n"
				"	float nDotHV;			// normal . light half vector\n"
				"	float pf;				// power factor\n"
				"\n"
				"	nDotVP = max(0.0, dot(normal, normalize(vec3(gl_LightSource[i].position))));\n"
				"	nDotHV = max(0.0, dot(normal, vec3(gl_LightSource[i].halfVector)));\n\n"
				"	if ( nDotVP == 0.0 || nDotHV == 0.0 )\n"
				"	{\n"
				"		pf = 0.0;\n"
				"	}\n"
				"	else\n"
				"	{\n"
				"		pf = pow( nDotHV, gl_FrontMaterial.shininess);\n\n"
				"	}\n"
				"\n"
				"	accumAmbient	+= gl_LightSource[i].ambient;\n"
				"	accumDiffuse	+= gl_LightSource[i].diffuse * nDotVP;\n"
				"	accumSpecular	+= gl_LightSource[i].specular * pf;\n"
				"}\n";

			retValBack = retValFront;
			boost::algorithm::replace_all( retValBack, "Front", "Back" );
		}

		// Returns the desired function
		if ( useBackMaterial )
		{
			return retValBack;
		}
		else
		{
			return retValFront;
		}
	}



	static const std::string& generateFunction_pointLight( const GLSLState& state, const bool useBackMaterial )
	{
		static std::string retValFront;
		static std::string retValBack;

		if ( retValFront.length() == 0 )
		{
			retValFront =
				"void pointLightFront( int i, vec3 ecPosition3, vec3 normal, vec3 eye )\n"
				"{\n"
				"	float nDotVP;			// normal . light direction\n"
				"	float nDotHV;			// normal . light half vector\n"
				"	float pf;				// power factor\n"
				"	float attenuation;		// computed attenuation factor\n"
				"	float d;				// distance from surface to light source\n"
				"	vec3  VP;				// direction from surface to light position\n"
				"	vec3  halfVector;		// direction of maximum highlights\n"
				"\n"
				"	// Compute vector from surface to light position\n"
				"	VP = vec3(gl_LightSource[i].position) - ecPosition3;\n"
				"\n"
				"	// Compute distance between surface and light position\n"
				"	d = length(VP);\n"
				"\n"
				"	// Normalize the vector from surface to light position\n"
				"	VP = normalize(VP);\n"
				"\n"
				"	// Compute attenuation\n"
				"	attenuation =	1.0 / (gl_LightSource[i].constantAttenuation +\n"
				"					gl_LightSource[i].linearAttenuation * d +\n"
				"					gl_LightSource[i].quadraticAttenuation * d * d);\n"
				"\n"
				"	halfVector = normalize(VP + eye);\n"
				"\n"
				"	nDotVP = max(0.0, dot(normal, VP));\n"
				"	nDotHV = max(0.0, dot(normal, halfVector));\n"
				"\n"
				"	if ( nDotVP == 0.0 || nDotHV == 0.0 )\n"
				"	{\n"
				"		pf = 0.0;\n"
				"	}\n"
				"	else\n"
				"	{\n"
				"		pf = pow(nDotHV, gl_FrontMaterial.shininess);\n"
				"	}\n"
				"\n"
				"	accumAmbient	+= gl_LightSource[i].ambient * attenuation;\n"
				"	accumDiffuse	+= gl_LightSource[i].diffuse * nDotVP * attenuation;\n"
				"	accumSpecular	+= gl_LightSource[i].specular * pf * attenuation;\n"
				"}\n";

			retValBack = retValFront;
			boost::algorithm::replace_all( retValBack, "Front", "Back" );
		}

		// Returns the desired function
		if ( useBackMaterial )
		{
			return retValBack;
		}
		else
		{
			return retValFront;
		}
	}



	static const std::string generate_fshadowFiltering( const GLSLState& state, const vgd::node::LightModel::ShadowValueType shadowType )
	{
		using vgd::node::LightModel;

		std::string retValShadow =
						"float shadowFiltering( sampler2DShadow texMap, vec2 mapSize, vec4 texCoord, float samplingSize )\n"
						"{\n"
						"	float shadowFactor = 0.0;\n\n";

		std::string retVal =
						"float shadowFiltering( sampler2D texMap, vec2 mapSize, vec4 texCoord, float samplingSize )\n"
						"{\n"
						"	float shadowFactor = 1.0;\n\n";

		// uniform
		const std::string tplShadowFilteringU =
						"	float x, y;\n"
						"	for( y = -RANGE; y <= RANGE; y += STEP )\n"
						"		for( x = -RANGE; x <= RANGE; x += STEP )\n"
						"			shadowFactor += lookupMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize );\n"
						"	shadowFactor /= DIVISOR;\n";

		const std::string tplCasterFilteringU =
						"	float x, y;\n"
						"	for( y = -RANGE; y <= RANGE; y += STEP )\n"
						"		for( x = -RANGE; x <= RANGE; x += STEP )\n"
						"			shadowFactor = min( shadowFactor, lookupMap(texMap, mapSize, texCoord, vec2(x, y) * samplingSize * 2.0) );\n";

		// uniform with modulo
		const std::string tplShadowFilteringUM =
						"	// use modulo to vary the sample pattern\n"
						"	vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"	float x, y;\n"
						"	for( y = -RANGE; y <= RANGE; y += STEP )\n"
						"		for( x = -RANGE; x <= RANGE; x += STEP )\n"
						"			shadowFactor += lookupMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize + o );\n"
						"	shadowFactor /= DIVISOR;\n";

		const std::string tplCasterFilteringUM =
						"	// use modulo to vary the sample pattern\n"
						"	vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"	float x, y;\n"
						"	for( y = -RANGE; y <= RANGE; y += STEP )\n"
						"		for( x = -RANGE; x <= RANGE; x += STEP )\n"
						"			shadowFactor = min( shadowFactor, lookupMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize * 2.0 + o ) );\n";

		std::string shadowFiltering;
		std::string casterFiltering;

		if ( shadowType == LightModel::SHADOW_OFF )
		{
			// nothing to do
		}
		else if ( shadowType ==LightModel::SHADOW_MAPPING )
		{
			// 1X
			shadowFiltering =	"	shadowFactor = lookupMap( texMap, mapSize, texCoord, vec2(0,0) );\n";
			casterFiltering = shadowFiltering;
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_4U )
		{
			// 4X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "0.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "4.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "0.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_4UM )
		{
			// 4X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "0.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "4.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "0.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_4DM )
		{
			// 4X dithered with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "1.5" );
			boost::algorithm::replace_all( shadowFiltering, "STEP", "2.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "4.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "1.5" );
			boost::algorithm::replace_all( casterFiltering, "STEP", "2.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_9U )
		{
			// 9X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "1.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "9.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "1.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_9UM )
		{
			// 9X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "1.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "9.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "1.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_16U )
		{
			// 16X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "1.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "16.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "1.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_16UM )
		{
			// 16X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "1.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "16.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "1.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_25U )
		{
			// 25X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "2.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "25.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "2.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_25UM )
		{
			// 25X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "2.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "25.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "2.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_36U )
		{
			// 36X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "2.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "36.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "2.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_36UM )
		{
			// 36X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "2.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "36.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "2.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_64U )
		{
			// 64X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "3.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "64.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "3.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_64UM )
		{
			// 64X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "3.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "64.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "3.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_144U )
		{
			// 144X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "5.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "144.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "5.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_144UM )
		{
			// 144X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "5.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "144.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "5.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_225U )
		{
			// 225X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "7.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "225.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "7.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_225UM )
		{
			// 225X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "7.0" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "225.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "7.0" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_256U )
		{
			// 256X uniform
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringU, "RANGE", "7.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "256.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringU, "RANGE", "7.5" );
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_256UM )
		{
			// 256X uniform with modulo
			shadowFiltering = boost::algorithm::replace_all_copy( tplShadowFilteringUM, "RANGE", "7.5" );
			boost::algorithm::replace_all( shadowFiltering, "DIVISOR", "256.0" );

			casterFiltering = boost::algorithm::replace_all_copy( tplCasterFilteringUM, "RANGE", "7.5" );
		}
		else
		{
			vgAssertN( false, "Unexpected value." );
			shadowFiltering =	"shadowFactor = 0.0;\n";
			casterFiltering = shadowFiltering;
		}

		// If not yet replaced
		boost::algorithm::replace_all( shadowFiltering, "STEP", "1.0" );
		boost::algorithm::replace_all( casterFiltering, "STEP", "1.0" );

		const std::string end =
						"	return shadowFactor;\n"
						"}\n"
						"\n";
		shadowFiltering += end;
		casterFiltering += end;

		retValShadow	+= shadowFiltering;
		retVal			+= casterFiltering;

		return retValShadow + retVal;
	}


	static const std::string generate_fcomputeShadowFactor( const GLSLState& state, const vgd::node::LightModel::ShadowValueType shadowType, const float samplingSize )
	{
		using vgd::node::LightModel;

		const std::string flookupShadowMap =	"float lookupMap( sampler2DShadow map, vec2 mapSize, vec4 texCoord, vec2 offset )\n"
												"{\n"
												"	vec4 texCoordOffset = vec4(texCoord.xy + (offset/mapSize * texCoord.w), texCoord.z, texCoord.w );\n"
												"	return textureProj( map, texCoordOffset );\n"
												"}\n\n";

		const std::string flookupMap =			"float lookupMap( sampler2D map, vec2 mapSize, vec4 texCoord, vec2 offset )\n"
												"{\n"
												"	vec2 texCoordOffset = texCoord.xy/texCoord.w + (offset/mapSize);\n"
												"	return texture( map, texCoordOffset ).a;\n"
												"}\n\n";

		const std::string shadowFiltering = generate_fshadowFiltering( state, shadowType );

		std::string retVal =	"float computeShadowFactor( int ism )\n"
								"{\n"
//								"	vec4			texCoord			= mgl_TexCoordShadow[ism];\n";
								"	vec4			texCoord			= mgl_TexCoordShadow[0];\n";

		// shadow caster
// @todo if ( state.getOption2() == vgd::node::LightModel::CHOICE0 )
// @todo OPTME only if a transparent object is rendered

		// mapSize
		// retVal +=				"	vec2 mapSize = vec2( textureSize( texMap2DShadow[ism], 0) );\n"; // @todo texMap2DShadow[ism] only on sm5 GPU
		retVal +=				"	vec2 mapSize = vec2( textureSize( texMap2DShadow[0], 0) );\n";

		// samplingSize
		// @todo samplingSize must be an uniform
		retVal += 				"	const float samplingSize = " + boost::lexical_cast<std::string>( samplingSize ) + ";\n";

		//
		retVal +=				"	// Computes shadow factor\n"
//								"	float shadowFactor = shadowFiltering( texMap2DShadow[ism], mapSize, texCoord, samplingSize );\n" // @todo texMap2DShadow[ism] only on sm5 GPU
								"	float shadowFactor = shadowFiltering( texMap2DShadow[0], mapSize, texCoord, samplingSize );\n"
								"\n";

		retVal +=				"	// Computes shadow caster opacity\n"
								"	float shadowCasterAlpha = shadowFiltering( texMap2D[3], mapSize, texCoord, samplingSize );\n" // @todo texMap2D[0][0] => index ?
								"\n";

		// illuminationInShadow
		const float illuminationInShadow = state.getIlluminationInShadow();
		// @todo should be a uniform param
		retVal +=				"	float illuminationInShadow = " + boost::lexical_cast<std::string>(illuminationInShadow) + ";\n";

		if ( state.getOption0() == vgd::node::LightModel::CHOICE0 )
		{
			retVal +=			"	if ( shadowFactor < 1 )\n"
								"	{\n"
								"		// Fade out shadow\n"
								"		illuminationInShadow = mix(1.0, illuminationInShadow, shadowCasterAlpha);\n"
								"\n"
								"		shadowFactor = mix(illuminationInShadow, 1.0, shadowFactor);\n"
// @todo use shadowSrcColor instead only alpha
//								"		shadowFactor = mix( 1.0, shadowFactor, shadowCasterAlpha );\n"
								"	}\n";
		}
		else if ( state.getOption0() == vgd::node::LightModel::CHOICE1 )
		{
// @todo use mix()
			retVal +=			"	shadowFactor = shadowFactor*(1-illuminationInShadow) + illuminationInShadow;\n";
		}
		else
		{
			retVal += 			"	shadowFactor = max( illuminationInShadow, shadowFactor);\n";
		}
		retVal += 				"	return shadowFactor;\n"
								"}\n\n";

		return flookupShadowMap + flookupMap + shadowFiltering + retVal;
	}

	// @todo removes /*&*/
	static const std::string /*&*/ generateFunction_spotLight( const GLSLState& state, const bool useBackMaterial, const bool castShadow )
	{
		using vgd::node::LightModel;

		static LightModel::ShadowValueType	shadowType				= LightModel::SHADOW_OFF;
		static float						samplingSize			= 1.f;
		static float						illuminationInShadow	= state.getIlluminationInShadow();
		static vgd::node::LightModel::Option0ValueType option0		= state.getOption0();
		static std::string					shadowString			= generate_fcomputeShadowFactor( state, LightModel::SHADOW_OFF, 1.f );

		static std::string					retValFront;
		static std::string					retValBack;

		// Updates shadow factor computation string
		const LightModel::ShadowValueType	incomingShadowType				= state.getShadowType();
		const float							incomingSamplingSize			= state.getSamplingSize();
		const float							incomingIlluminationInShadow	= state.getIlluminationInShadow();
		const vgd::node::LightModel::Option0ValueType incomingOption0		= state.getOption0();

		if (	(incomingShadowType != shadowType )						||
				(incomingSamplingSize != samplingSize)					||
				(incomingIlluminationInShadow != illuminationInShadow )	||
				(incomingOption0 != option0 )	)
		{
			shadowType				= incomingShadowType;
			samplingSize			= incomingSamplingSize;
			illuminationInShadow	= incomingIlluminationInShadow;

			shadowString = generate_fcomputeShadowFactor( state, shadowType, samplingSize );
		}

		//
		if ( retValFront.length() == 0 )
		{
			retValFront =
			"// i index of light, ism index of shadow map or -1 if shadow computation is disabled\n"
			"void spotLightFront( int i, int ism, vec3 ecPosition3, vec3 normal, vec3 eye )\n"
			"{\n"
			"	float nDotVP;			// normal . light direction\n"
			"	float nDotHV;			// normal . light half vector\n"
			"	float pf;				// power factor\n"
			"	float spotDot;			// cosine of angle between spotlight\n"
			"	float spotAttenuation;	// spotlight attenuation factor\n"
			"	float attenuation;		// computed attenuation factor\n"
			"	float d;				// distance from surface to light source\n"
			"	vec3  VP;				// direction from surface to light position\n"
			"	vec3  halfVector;		// direction of maximum highlights\n"
			"\n"
			"	// Compute vector from surface to light position\n"
			"	VP = vec3(gl_LightSource[i].position) - ecPosition3;\n"
			"\n"
			"	// Compute distance between surface and light position\n"
			"	d = length(VP);\n"
			"\n"
			"	// Normalize the vector from surface to light position\n"
// @todo uses d
			"	VP = normalize(VP);\n"
			"\n"
			"	// Compute attenuation\n"
// @todo uncomments attenuation (when Light node specifies distance attenuation).
//			"	attenuation =	1.0;\n"
//			"	attenuation =	1.0 / (gl_LightSource[i].constantAttenuation +\n"
//			"					gl_LightSource[i].linearAttenuation * d +\n"
//			"					gl_LightSource[i].quadraticAttenuation * d * d);\n"
			"\n"
			"	// See if point on surface is inside cone of illumination\n"
			"	spotDot = dot(-VP, normalize(gl_LightSource[i].spotDirection));\n"
// @todo uniform values cosOuterCone and cosInnerCone
			"	float cosOuterCone = cos( radians(gl_LightSource[i].spotCutoff) );\n"
			"	float cosInnerCone = cos( radians(gl_LightSource[i].spotCutoff * 0.8) );" // @todo 0.8 must be a param
			"\n"
			"	spotAttenuation = 1.0 - smoothstep( cosInnerCone, cosOuterCone, spotDot );\n"
			"\n"
/*		"	if ( spotAttenuation == 1.0 )\n"
			"	{\n"
			"		spotAttenuation = pow(spotDot, gl_LightSource[i].spotExponent);\n"
			"	}\n"*/
/*		"	if ( spotDot < cosOuterCone )\n"
			"	{\n"
			"		spotAttenuation = 0.0; // light adds no contribution\n"
			"	}\n"
			"	else\n"
			"	if ( spotDot < cosInnerCone || spotDot == 0.0 )\n"
			"	{\n"
			"		spotAttenuation = 0.5; // light adds no contribution\n"
			"	}\n"
			"	else\n"
			"	{\n"
			"		spotAttenuation = pow(spotDot, gl_LightSource[i].spotExponent);\n"
			"	}\n"*/
			"\n"
// @todo OPTME computeShadowFactor only if needed
			"	// Compute shadow\n"
			"	float shadowFactor;\n"
			"	if ( (ism >= 0) && gl_FrontFacing )\n"
			"	{\n"
			"		shadowFactor = computeShadowFactor( ism );\n"
			"	}\n"
			"	else\n"
			"	{\n"
			"		// No shadow\n"
			"		shadowFactor = 1.0;\n"
			"	}\n"
			"\n"
			"	// Combine the spotlight, shadow factor and distance attenuation.\n"
			"	attenuation = spotAttenuation * shadowFactor;\n"
			"\n"
			//"	halfVector = gl_LightSource[i].halfVector;\n"
			"	halfVector = normalize(VP + eye);\n"
			"\n"
			"	nDotVP = max( 0.0, dot(normal, VP) );\n"
			"	nDotHV = max( 0.0, dot(normal, halfVector) );\n"
			"\n"
//		"	if ( nDotVP <= 0.0 )\n"
			"	if ( nDotVP == 0.0 || nDotHV == 0.0 )\n"
			"	{\n"
			"		pf = 0.0;\n"
			"	}\n"
			"	else\n"
			"	{\n"
			"		pf = pow( nDotHV, gl_FrontMaterial.shininess );\n"				// @todo gl_Back ?
			"	}\n"
			"\n"
			"	accumAmbient	+= gl_LightSource[i].ambient * attenuation;\n"
			"	accumDiffuse	+= gl_LightSource[i].diffuse * nDotVP * attenuation;\n"
			"	accumSpecular	+= gl_LightSource[i].specular * pf * attenuation;\n"
			"}\n";

			retValBack = retValFront;
			boost::algorithm::replace_all( retValBack, "Front", "Back" );
		}

		//if ( castShadow )
		//{
/*			std::string spotLightFrontShadow = 
				"\n"
				"void spotLightFrontShadow( int i, sampler2DShadow texMapShadow, vec4 texCoordShadow, vec3 ecPosition3, vec3 normal, vec3 eye )\n"
				"{\n"
				"	float shadowFactor = computeShadowFactor( texMapShadow, texCoordShadow );\n"
				"\n"
				"	spotLightFront( i, ecPosition3, normal, eye, shadowFactor );\n"
				"}\n\n";*/

			//std::string spotLightBackShadow = spotLightFrontShadow;
			//boost::algorithm::replace_all( spotLightBackShadow, "Front", "Back" );
		//}

		// Returns the desired function
		// @todo not always included shadow code
		if ( useBackMaterial )
		{
			return shadowString + retValBack;// + spotLightBackShadow;
		}
		else
		{
			return shadowString + retValFront;// + spotLightFrontShadow;
		}
	}


	//static void generateFunction_flightFrontAndBack(	const GLSLState& state,
	//													std::string& flightFront, std::string& flightBack )
	static void generateFunction_flightFront( const GLSLState& state, std::string& flightFront )
	{
		const std::string clearLightIntensityAccumulators =
			"	// Clear the light intensity accumulators\n"
			"	accumAmbient	= vec4(0.0);\n"
			"	accumDiffuse	= vec4(0.0);\n"
			"	accumSpecular	= vec4(0.0);\n"
			"\n";

		flightFront	=
			"// Computes the light contributions for front face\n"
			"void flightFront( in vec3 ecPosition3, in vec3 normal, in vec3 eye )\n"
			"{\n" +
			clearLightIntensityAccumulators;

		/*flightBack	=
			"// Computes the light contributions for back face\n"
			"void flightBack( in vec3 ecPosition3, in vec3 normal, in vec3 eye )\n"
			"{\n" +
			clearLightIntensityAccumulators;*/

		// For each light, do
		uint		lightCastingShadowCount	= 0;
		uint		i						= 0;
		const uint	iEnd					= state.lights.getMax();

		for( uint foundLight = 0; i != iEnd; ++i )
		{
			const vgd::Shp< LightState > currentLightState = state.lights.getState(i);

			if ( currentLightState )
			{
				if ( currentLightState->getOn() )
				{
					const std::string iStr = vgd::basic::toString( i );

					const int lightType = currentLightState->getLightType();

					switch ( lightType )
					{
						case DIRECTIONAL_LIGHT:
							flightFront		+= "	directionalLightFront( " + iStr + ", normal );\n";
							//flightBack		+= "	directionalLightFront( " + iStr + ", normal );\n";
							//currentLightBack	+= "	directionalLightBack( " + iStr + ", -normal );\n";
							break;

						case POINT_LIGHT:
							flightFront		+= "	pointLightFront( " + iStr + ", ecPosition3, normal, eye );\n";
							//flightBack		+= "	pointLightFront( " + iStr + ", ecPosition3, normal, eye );\n";
							//currentLightBack	+= "	pointLightBack( " + iStr + ", ecPosition3, -normal, eye );\n";
							break;

						case SPOT_LIGHT:
							if (	state.getShadowType() != vgd::node::LightModel::SHADOW_OFF && 
									currentLightState->getCastShadow() )
							{
// @todo api state.get[Private]TexUnit( "Texture", "lightShadowMap" "lightShadowCasterRGBA", 0, sampler2D/sampler2Dshadow... ) => allocTU/desallocTU/get bimap< string(lightShadowMap0), int(34) >
// texCoordIndex[0...N]
// texMap2DShadow[0...N]
// TEXUNIT		[N...0]
//								const std::string	texCoordShadowIndexStr	= vgd::basic::toString(lightCastingShadowCount);
//								const std::string	texMapIndexStr			= state.getPrivateTexUnit(lightCastingShadowCount);
//								const std::string&	texMapShadowIndexStr	= texCoordShadowIndexStr;
								const std::string	ismStr					= vgd::basic::toString(lightCastingShadowCount);
								++lightCastingShadowCount;
								flightFront		+= "	spotLightFront( " + iStr + ", " + ismStr + ", ecPosition3, normal, eye );\n";
//flightFront		+= "	spotLightFront( " + iStr + ", texMap2DShadow[" + texMapShadowIndexStr + "], mgl_TexCoordShadow[" + texCoordShadowIndexStr + "], ecPosition3, normal, eye );\n";
								//flightBack		+= "	spotLightFrontShadow( " + iStr + ", texMap2DShadow[" + texMapShadowIndexStr + "], mgl_TexCoordShadow[" + texCoordShadowIndexStr + "], ecPosition3, normal, eye );\n";

								// currentLightBack	+= "	spotLightBack( " + iStr + ", ecPosition3, -normal, eye );\n";
							}
							else
							{
								flightFront		+= "	spotLightFront( " + iStr + ", -1, ecPosition3, normal, eye );\n";
								//flightBack		+= "	spotLightFront( " + iStr + ", ecPosition3, normal, eye, 1.0 );\n";
								// currentLightBack	+= "	spotLightBack( " + iStr + ", ecPosition3, -normal, eye );\n";
							}
							break;

						default:
							assert( false && "Unknown light type !" );
					}
				}
				// else light off, nothing to do

				//
				++foundLight;
				if ( foundLight == state.lights.getNum() )
				{
					break;
				}
			}
			// else no light, nothing to do
		}

		flightFront	+= 
		"}\n";

		//flightBack	+=
		//"}\n";
	}



	static const std::string generateFunction_flight( const GLSLState& state )
	{
		std::string retVal;

		std::string flight;

		if ( state.isLightingEnabled() )
		{
			// 
			flight +=
				"\n"
				"void flight( in vec4 ecPosition, in vec3 normal )\n"
				"{\n"
				"	// Several pre-computations\n"
				"	vec3 ecPosition3	= (vec3(ecPosition)) / ecPosition.w;\n";

			if ( state.isEnabled(LOCAL_VIEWER) )
			{
				flight +=
				"	vec3 eye			= -normalize(ecPosition3);\n"
				"\n";
			}
			else
			{
				flight +=
				"	vec3 eye			= vec3(0.0, 0.0, 1.0);\n"
				"\n";
			}

			//
			// Color updating stage
			const std::string colorUpdating =
				"\n"
				"	// Sets the color accumulators\n"
				"	accumColor	=	gl_FrontLightModelProduct.sceneColor + \n"
				"					accumAmbient * gl_FrontMaterial.ambient +\n"
				"					accumDiffuse * gl_FrontMaterial.diffuse;\n"
				"	accumSecondaryColor	= accumSpecular * gl_FrontMaterial.specular;\n" // GL_SEPARATE_SPECULAR_COLOR
				"\n\n";

			const std::string colorUpdating2 =
				"\n"
				"		// Sets the color accumulators\n"
				"		accumColor	=	gl_FrontLightModelProduct.sceneColor + \n"
				"						accumAmbient * gl_FrontMaterial.ambient +\n"
				"						accumDiffuse * gl_FrontMaterial.diffuse;\n"
				"		accumSecondaryColor	= accumSpecular * gl_FrontMaterial.specular;\n"  // GL_SEPARATE_SPECULAR_COLOR
				"\n\n";

			const std::string backColorUpdating =
				"\n"
				"	// Sets the color accumulators\n"
				"	accumBackColor			=	gl_BackLightModelProduct.sceneColor + \n"
				"								accumAmbient * gl_FrontMaterial.ambient +\n"
				"								accumDiffuse * gl_FrontMaterial.diffuse;\n"
				"	accumBackSecondaryColor	=	accumSpecular * gl_FrontMaterial.specular;\n" // GL_SEPARATE_SPECULAR_COLOR
				"\n\n";

			const std::string backColorUpdating2 =
				"\n"
				"		// Sets the color accumulators\n"
				"		accumBackColor			=	gl_BackLightModelProduct.sceneColor + \n"
				"									accumAmbient * gl_FrontMaterial.ambient +\n"
				"									accumDiffuse * gl_FrontMaterial.diffuse;\n"
				"		accumBackSecondaryColor	=	accumSpecular * gl_FrontMaterial.specular;\n" // GL_SEPARATE_SPECULAR_COLOR
				"\n\n";

			//std::string flightFront, flightBack;
			//generateFunction_flightFrontAndBack( state, flightFront, flightBack );
			std::string flightFront;
			generateFunction_flightFront( state, flightFront );

			retVal += flightFront + "\n";
//if ( state.isTwoSidedLightingEnabled() ) retVal += flightBack + "\n";

			if ( state.isPerPixelLightingEnabled() )
			{
				if ( state.isTwoSidedLightingEnabled() )
				{
					flight +=
						"	if ( gl_FrontFacing )\n"
						"	{\n"
						"		// Computes the light contributions for front face\n"
						"		flightFront( ecPosition3, normal, eye );\n" +
								colorUpdating2 +
						"	}\n"
						"	else\n"
						"	{\n"
						"		// Computes the light contributions for back face\n"
						"		flightFront( ecPosition3, -normal, eye );\n" +
								backColorUpdating2 +
						"	}\n";
				}
				else
				{
					flight +=
						"	// Computes the light contributions for front face\n"
						"	flightFront( ecPosition3, normal, eye );\n" +
							colorUpdating;
				}

				//
				/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
				{
					boost::algorithm::replace_all( flight, "gl_FrontMaterial.diffuse", "gl_Color"  ); // "mglColor"
				}*/
			}
			else
			{
				if ( state.isTwoSidedLightingEnabled() )
				{
					flight +=
						"	// Computes the light contributions for front face\n"
						"	flightFront( ecPosition3, normal, eye );\n" +
							colorUpdating +
						"	// Computes the light contributions for back face\n"
						"	flightFront( ecPosition3, -normal, eye );\n" +
							backColorUpdating;
				}
				else
				{
					flight +=
						"	// Computes the light contributions for front face\n"
						"	flightFront( ecPosition3, normal, eye );\n" +
							colorUpdating;
				}

				//
				/*if ( state.isEnabled( GLSLState::COLOR4_BIND_PER_VERTEX ) )
				{
					boost::algorithm::replace_all( flight, "gl_FrontMaterial.diffuse", "gl_Color" ); //mglColor
				}*/
			}


// if(lightModelTwoSidedInt)
// {     
	// str += "    gl_FrontSecondaryColor.a *= alphaFade;\n"
		// "    gl_BackColor.a *= alphaFade;\n"
		// "    gl_BackSecondaryColor.a *= alphaFade;\n";
// }
			flight += 
			"}\n"
			"\n";
		}
		//else no lighting, so nothing to do

		retVal += flight;

		return retVal;
	}



	//
	static const std::string& generateFunction_fnormal( const GLSLState& state )
	{
		/*if ( state.isLightingEnabled() )
		{*/
			static const std::string retVal =
			"\n"
			"vec3 fnormal(void)\n"
			"{\n"
			"	//Compute the normal\n"
			"	vec3 normal = gl_NormalMatrix * mgl_Normal;\n"
			"	normal = normalize(normal);\n"	// glIsEnabled(GL_NORMALIZE)	//@todo not if PerPixelLighting
//			"	normal = normal * gl_NormalScale;\n"		// glIsEnabled(GL_RESCALE_NORMAL)
			"	return normal;\n"
			"}\n"
			"\n";

			return retVal;
		/*}
		else
		{
			static const std::string retVal("");
			return retVal;
		}*/
	}



	// TEXTURE
	// @todo class to store varying variables (vertex output, fragment input in glsl 1.3)
	// @param storageQualifierDecl	'out' for vertex shader, 'in' for fragment shader.
	static std::pair< std::string, std::string > generateFunction_ftexgen( const vgeGL::engine::GLSLState& state, const std::string storageQualifierDecl )
	{
		std::string decl;
		std::string code;

		uint mgl_TexCoordCount			= 0;
		uint mgl_TexCoordShadowCount	= 0;

		code =
		"void ftexgen( in vec4 ecPosition, in vec3 normal )\n"
		"{\n";

		uint		i		= 0;
		const uint	iEnd	= state.textures.getMax();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const vgd::Shp< GLSLState::TexUnitState >  current = state.textures.getState( i );

			if ( current )
			{
				const vgd::node::Texture *			textureNode	= current->getTextureNode();
				if ( textureNode == 0 )
				{
					vgAssertN( false, "generateFunction_ftexgen(): No texture node !" );
					continue;
				}
				vgd::node::Texture::UsageValueType	usage		= textureNode->getUsage();

				const std::string					strUnit		= vgd::basic::toString( i );
				const vgd::node::TexGen *			texGen		= current->getTexGenNode();

				// TEXGEN
				if ( texGen /*&& current->isComplete() */)
				{
					if ( usage == vgd::node::Texture::SHADOW )
					{
						const std::string strIndex = vgd::basic::toString( mgl_TexCoordShadowCount );
						++mgl_TexCoordShadowCount;

						code +=
						"	mgl_TexCoordShadow[" + strIndex + "].s = dot( ecPosition, gl_EyePlaneS[" + strUnit + "] );\n"
						"	mgl_TexCoordShadow[" + strIndex + "].t = dot( ecPosition, gl_EyePlaneT[" + strUnit + "] );\n"
						"	mgl_TexCoordShadow[" + strIndex + "].p = dot( ecPosition, gl_EyePlaneR[" + strUnit + "] );\n"
						"	mgl_TexCoordShadow[" + strIndex + "].q = dot( ecPosition, gl_EyePlaneQ[" + strUnit + "] );\n"
						"	mgl_TexCoordShadow[" + strIndex + "] = gl_TextureMatrix[" + strUnit +"] * mgl_TexCoordShadow[" + strIndex + "];\n";
					}
					else
					{
						vgAssert( usage == vgd::node::Texture::IMAGE );

						const std::string strIndex = vgd::basic::toString( mgl_TexCoordCount );
						++mgl_TexCoordCount;

						code +=
						"	mgl_TexCoord[" + strIndex + "].s = dot( ecPosition, gl_EyePlaneS[" + strUnit + "] );\n"
						"	mgl_TexCoord[" + strIndex + "].t = dot( ecPosition, gl_EyePlaneT[" + strUnit + "] );\n"
						"	mgl_TexCoord[" + strIndex + "].p = dot( ecPosition, gl_EyePlaneR[" + strUnit + "] );\n"
						"	mgl_TexCoord[" + strIndex + "].q = dot( ecPosition, gl_EyePlaneQ[" + strUnit + "] );\n"
						"	mgl_TexCoord[" + strIndex + "] = gl_TextureMatrix[" + strUnit +"] * mgl_TexCoord[" + strIndex + "];\n";
					}
				}
				// NO TEXGEN
				else if ( texGen == 0 && current->isComplete() )
				{
					if ( usage == vgd::node::Texture::SHADOW )
					{
						const std::string strIndex = vgd::basic::toString( mgl_TexCoordShadowCount );
						++mgl_TexCoordShadowCount;

						code +=
						"	mgl_TexCoordShadow[" + strIndex + "] = gl_TextureMatrix[" + strUnit +"] * mgl_MultiTexCoord" + strUnit + ";\n";
					}
					else
					{
						const std::string strIndex = vgd::basic::toString( mgl_TexCoordCount );
						++mgl_TexCoordCount;

						code +=
						"	mgl_TexCoord[" + strIndex + "] = gl_TextureMatrix[" + strUnit +"] * mgl_MultiTexCoord" + strUnit + ";\n";
					}
				}
				// else nothing to do

				//
				++foundTexture;
				if ( foundTexture == state.textures.getNum() )
				{
					break;
				}
			}
			// else no texture, nothing to do
		}

		code  += 
		"}\n\n";

		if ( mgl_TexCoordCount > 0 )
		{
			decl += storageQualifierDecl + " vec4 mgl_TexCoord[" + vgd::basic::toString(mgl_TexCoordCount) + "];\n";
		}
		else
		{
			decl += storageQualifierDecl + " vec4 mgl_TexCoord[2];\n"; // @todo
		}

		if ( mgl_TexCoordShadowCount > 0 )
		{
			decl += storageQualifierDecl + " vec4 mgl_TexCoordShadow[" + vgd::basic::toString(mgl_TexCoordShadowCount) + "];\n";
		}
		else
		{
			decl += storageQualifierDecl + " vec4 mgl_TexCoordShadow[2];\n"; // @todo
		}

		decl += "\n";

		return std::make_pair( decl, code );
	}

//??getSampler2DCount???
	static std::pair< std::string, std::string >  generate_samplers( const vgeGL::engine::GLSLState& state )
	{
		std::string decl;

		/*//uint sampler2DCount						= 0;
		uint sampler2DShadowCount				= 0;

		uint		i		= 0;
		const uint	iEnd	= state.textures.getMax();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const vgd::Shp< GLSLState::TexUnitState > current = state.textures.getState( i );

			// Empty texture unit, so do nothing
			if ( current == 0 )	continue;

			if ( current->isComplete() )
			{
				vgd::node::Texture *				textureNode	= current->getTextureNode();
				vgd::node::Texture::UsageValueType	usage		= textureNode->getUsage();

				switch ( usage.value() )
				{
					case vgd::node::Texture::SHADOW:
						++sampler2DShadowCount;
						//shadowTextureNode = textureNode;
						break;

					case vgd::node::Texture::IMAGE:
					//	++sampler2DCount;
						break;

					default:
						++sampler2DCount;
						assert( false && "Unexpected value for vgd::node::Texture.usage field" );
				}
			}
			// else nothing to do

			//
			++foundTexture;
			if ( foundTexture == state.textures.getNum() )
			{
				break;
			}
		}*/

		// Updates samplers declarations
//		if ( sampler2DCount > 0 )
		if ( state.textures.size() > 0 )
		{
			//decl += "uniform sampler2D texMap2D[];\n\n";
			//decl += "uniform sampler2D texMap2D[" + vgd::basic::toString(sampler2DCount) + "];\n\n";
			decl += "uniform sampler2D		texMap2D[" + vgd::basic::toString(state.textures.size()) + "];\n";
		}
		else
		{
			decl += "uniform sampler2D		texMap2D[2];\n";
		}

		//if ( sampler2DShadowCount > 0 )
		if ( state.textures.size() > 0 )
		{
			//decl += "uniform sampler2DShadow texMap2DShadow[1];\n\n";
			//decl += "uniform sampler2DShadow texMap2DShadow[" + vgd::basic::toString(sampler2DShadowCount) + "];\n\n";
			decl += "uniform sampler2DShadow	texMap2DShadow[" + vgd::basic::toString(state.textures.size()) + "];\n";
		}
		else
		{
			decl += "uniform sampler2DShadow	texMap2DShadow[2];\n";
		}

		return std::make_pair(decl + "\n", ""/*code*/);
	}


	static const std::string generate_texLookups( const vgeGL::engine::GLSLState& state, const bool fragmentShader )
	{
		std::string retVal;

		uint		i		= 0;
		const uint	iEnd	= state.textures.getMax();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const vgd::Shp< GLSLState::TexUnitState > current = state.textures.getState( i );

			// Empty texture unit, so do nothing
			if ( current == 0 ) continue;

			if ( current->isComplete() )
			{
				const vgd::node::Texture *		textureNode	= current->getTextureNode();

				if (	fragmentShader ? textureNode->hasFragmentFunction() : textureNode->hasVertexFunction() &&
						textureNode->getUsage() == vgd::node::Texture::IMAGE )
				{
					std::string function;
					if ( fragmentShader )
					{
						textureNode->getFragmentFunction( function );
					}
					else
					{
						textureNode->getVertexFunction( function );
					}

					// Replaces MAI by multi attribute index of texture node
					const std::string strUnit = vgd::basic::toString( i );
					boost::algorithm::replace_all( function, "MAI", strUnit );
// @todo adds the comment without breaking GLSLProgram cache
					//const std::string comments = "	// Vertex function adds by node named " + textureNode->getName() + " (mai=" + strUnit + ")\n";
					retVal += /*comments + */function + "\n";
				}
				// else nothing to do (at least for SHADOW)
			}
			// else nothing to do

			//
			++foundTexture;
			if ( foundTexture == state.textures.getNum() )
			{
				break;
			}
		}

		return retVal;
	}

	static const std::string generate_vertexShader_texLookups( const vgeGL::engine::GLSLState& state )
	{
		return generate_texLookups( state, false );
	}

	static const std::string generate_fragmentShader_texLookups( const vgeGL::engine::GLSLState& state )
	{
		return generate_texLookups( state, true );
	}


	static const std::string generate_fpoint( const vgeGL::engine::GLSLState& state )
	{
		std::string retVal;

		retVal +=	"float fpoint( in float ecDistance )\n" //, out float fadeFactor)\n"
					"{\n"
					"	float derivedSize;\n"
					"	derivedSize =	gl_Point.distanceConstantAttenuation +\n"
					"					(gl_Point.distanceLinearAttenuation * ecDistance) +\n"
					"					(gl_Point.distanceQuadraticAttenuation * ecDistance * ecDistance);\n"
					"	derivedSize = gl_Point.size * inversesqrt(derivedSize);\n"
					"	derivedSize = clamp( derivedSize, gl_Point.sizeMin, gl_Point.sizeMax );\n"
					"	return derivedSize;\n"
					"}\n";

		return retVal;
	/*
	if(glIsEnabled(GL_MULTISAMPLE))
	{
		str += "        {\n"
				"            derivedSize = max(derivedSize, gl_Point.fadeThresholdSize);\n"
				"            if (derivedSize >= gl_Point.fadeThresholdSize)\n"
				"                fadeFactor = 1.0;\n"
				"            else\n"
				"            {\n"
				"                float ratio = derivedSize/gl_Point.fadeThresholdSize;\n"
				"                fadeFactor  = ratio * ratio;\n"
				"            }\n"
				"        }\n";
	}
	str += "    return derivedSize;\n    }\n";*/
	}


	/**
	 * @brief Returns GLSL textureless classic 2D noise cnoise() and an RSL-style periodic variant pnoise()
	 *
	 * Classic Perlin noise, periodic variant : float pnoise(vec2 P, vec2 rep)
	 * Classic Perlin noise\n : float cnoise(vec2 P)
	 *
	 * The motivation for these functions not using any textures is ease of use, self-sufficiency and scalability for massively parallel execution.
	 *
	 * @remark Support on OpenGL 2.1, OpenGL 3.x and 4.x, OpenGL ES 2.x and WebGL 1.0
	 * @remark See LICENSE_webgl-noise
	 */
	static const std::string& get_pnoise_cnoise()
	{
		static const std::string retVal =
		"// GLSL textureless classic 2D noise cnoise,\n"
		"// with an RSL-style periodic variant pnoise.\n"
		"// Author:  Stefan Gustavson (stefan.gustavson@liu.se)\n"
		"// Version: 2011-08-22\n"
		"//\n"
		"// Many thanks to Ian McEwan of Ashima Arts for the\n"
		"// ideas for permutation and gradient selection.\n"
		"//\n"
		"// Copyright (c) 2011 Stefan Gustavson. All rights reserved.\n"
		"// Distributed under the MIT license. See LICENSE file.\n"
		"// https://github.com/ashima/webgl-noise\n"
		"//\n"
		"\n"
		"vec4 mod289(vec4 x)\n"
		"{\n"
		"  return x - floor(x * (1.0 / 289.0)) * 289.0;\n"
		"}\n"
		"\n"
		"vec4 permute(vec4 x)\n"
		"{\n"
		"  return mod289(((x*34.0)+1.0)*x);\n"
		"}\n"
		"\n"
		"vec4 taylorInvSqrt(vec4 r)\n"
		"{\n"
		"  return 1.79284291400159 - 0.85373472095314 * r;\n"
		"}\n"
		"\n"
		"vec2 fade(vec2 t) {\n"
		"  return t*t*t*(t*(t*6.0-15.0)+10.0);\n"
		"}\n"
		"\n"
		"// Classic Perlin noise\n"
		"float cnoise(vec2 P)\n"
		"{\n"
		"  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);\n"
		"  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);\n"
		"  Pi = mod289(Pi); // To avoid truncation effects in permutation\n"
		"  vec4 ix = Pi.xzxz;\n"
		"  vec4 iy = Pi.yyww;\n"
		"  vec4 fx = Pf.xzxz;\n"
		"  vec4 fy = Pf.yyww;\n"
		"\n"
		"  vec4 i = permute(permute(ix) + iy);\n"
		"\n"
		"  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;\n"
		"  vec4 gy = abs(gx) - 0.5 ;\n"
		"  vec4 tx = floor(gx + 0.5);\n"
		"  gx = gx - tx;\n"
		"\n"
		"  vec2 g00 = vec2(gx.x,gy.x);\n"
		"  vec2 g10 = vec2(gx.y,gy.y);\n"
		"  vec2 g01 = vec2(gx.z,gy.z);\n"
		"  vec2 g11 = vec2(gx.w,gy.w);\n"
		"\n"
		"  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));\n"
		"  g00 *= norm.x;\n"
		"  g01 *= norm.y;\n"
		"  g10 *= norm.z;\n"
		"  g11 *= norm.w;\n"
		"\n"
		"  float n00 = dot(g00, vec2(fx.x, fy.x));\n"
		"  float n10 = dot(g10, vec2(fx.y, fy.y));\n"
		"  float n01 = dot(g01, vec2(fx.z, fy.z));\n"
		"  float n11 = dot(g11, vec2(fx.w, fy.w));\n"
		"\n"
		"  vec2 fade_xy = fade(Pf.xy);\n"
		"  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);\n"
		"  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);\n"
		"  return 2.3 * n_xy;\n"
		"}\n"
		"\n"
		"// Classic Perlin noise, periodic variant\n"
		"float pnoise(vec2 P, vec2 rep)\n"
		"{\n"
		"  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);\n"
		"  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);\n"
		"  Pi = mod(Pi, rep.xyxy); // To create noise with explicit period\n"
		"  Pi = mod289(Pi);        // To avoid truncation effects in permutation\n"
		"  vec4 ix = Pi.xzxz;\n"
		"  vec4 iy = Pi.yyww;\n"
		"  vec4 fx = Pf.xzxz;\n"
		"  vec4 fy = Pf.yyww;\n"
		"\n"
		"  vec4 i = permute(permute(ix) + iy);\n"
		"\n"
		"  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;\n"
		"  vec4 gy = abs(gx) - 0.5 ;\n"
		"  vec4 tx = floor(gx + 0.5);\n"
		"  gx = gx - tx;\n"
		"\n"
		"  vec2 g00 = vec2(gx.x,gy.x);\n"
		"  vec2 g10 = vec2(gx.y,gy.y);\n"
		"  vec2 g01 = vec2(gx.z,gy.z);\n"
		"  vec2 g11 = vec2(gx.w,gy.w);\n"
		"\n"
		"  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));\n"
		"  g00 *= norm.x;\n"
		"  g01 *= norm.y;\n"
		"  g10 *= norm.z;\n"
		"  g11 *= norm.w;\n"
		"\n"
		"  float n00 = dot(g00, vec2(fx.x, fy.x));\n"
		"  float n10 = dot(g10, vec2(fx.y, fy.y));\n"
		"  float n01 = dot(g01, vec2(fx.z, fy.z));\n"
		"  float n11 = dot(g11, vec2(fx.w, fy.w));\n"
		"\n"
		"  vec2 fade_xy = fade(Pf.xy);\n"
		"  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);\n"
		"  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);\n"
		"  return 2.3 * n_xy;\n"
		"}\n";

		return retVal;
	}

};



/**
 * @brief Abstract base class for code generator
 *
 * This is the abstract base class for all GLSL shader generator.
 *
 * @todo NVidia/CG generator ?
 */
struct VGEGL_API ShaderGenerator
{
	/**
	 * @brief Default constructor
	 */
	ShaderGenerator( const glo::GLSLProgram::ShaderType shaderType );


	/**
	 * @param engine	used to lookup the rendering state (light(s) , texture(s) and so on).
	 */
	virtual const bool generate( vgeGL::engine::Engine * engine ) = 0;


	/**
	 * @brief Returns the type of the shader generated by this class.
	 *
	 * @return the type of the shader generated by this class
	 */
	const glo::GLSLProgram::ShaderType getShaderType() const;


	// @todo hides getMainDF() and adds isValid() and invalidate()
	/**
	 * @brief Retrieves the main dirty flag of the generator
	 *
	 * This dirty flag is used to store the validation/invalidation state of the generator.
	 * An invalid state means that method run() must be called before retrieving the generated code.
	 * A valid state means that generaed code could be retrieve directly.
	 *
	 * @return the main dirty flag
	 */
	vgd::field::DirtyFlag& getMainDirtyFlag();


	/**
	 * @brief Enables or disables the code generation depending on the value of the parameter b.
	 *
	 * @param isEnabled		true when code generation must be enabled, false otherwise
	 */
	void setEnabled( const bool isEnabled = true );

	/**
	 * @brief Determines whether the code generation is enabled.
	 *
	 * @return true if the code generation is enabled, false otherwise
	 */
	const bool isEnabled() const;


	/**
	 * @brief Retrieves the generated code
	 *
	 * @return the string containing the generated code
	 */
	const std::string getCode() const;


private:
	glo::GLSLProgram::ShaderType	m_shaderType;		///< the type of the generated shader
	vgd::field::DirtyFlag			m_mainDirtyFlag;	///< the main dirty flag
	bool							m_isEnabled;		///< true when code generation is enabled, false otherwise

protected:
	std::string						m_decl;				///< the string containing the generated declaration
	std::string						m_code1;			///< the string containing the first part of the generated code : several different helpers functions
	std::string						m_code2;			///< the string containing the second part of the generated code : the main() function
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_SHADERGENERATOR_HPP
