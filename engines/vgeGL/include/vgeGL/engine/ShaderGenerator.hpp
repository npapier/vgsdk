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
#include <vgDebug/convenience.hpp>

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
		static const std::string retVal = "uniform vec2 nearFar;\n\n";

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



	static const std::string generate_lights( const GLSLState& state )
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



	static const std::string generate_fcomputeShadowFactor( const GLSLState& state, const vgd::node::LightModel::ShadowValueType shadowType, const float samplingSize )
	{
		using vgd::node::LightModel;

		const std::string flookupShadowMap =	"float lookupShadowMap( sampler2DShadow map, vec2 mapSize, vec4 texCoord, vec2 offset )\n"
												"{\n"
												"	vec4 texCoordOffset = vec4(texCoord.xy + (offset / mapSize * texCoord.w), texCoord.z, texCoord.w );\n"
												"	return textureProj( map, texCoordOffset );\n"
												"}\n\n";

		std::string retVal =	"float computeShadowFactor( sampler2DShadow texMap, vec4 texCoord )\n"
								"{\n"
								"	float shadowFactor;\n";

		// mapSize
		retVal +=				"	vec2 mapSize = vec2( textureSize( texMap, 0) );\n";

		// samplingSize
		retVal += 				"	const float samplingSize = " + boost::lexical_cast<std::string>( samplingSize ) + ";\n";

		//
		retVal +=				"// Computes shadow factor\n";

		if ( shadowType == LightModel::SHADOW_OFF )
		{
			retVal += 	"shadowFactor = 0.0;\n";
		}
		else if ( shadowType ==LightModel::SHADOW_MAPPING )
		{
			// 1X
			retVal +=	"shadowFactor = lookupShadowMap( texMap, mapSize, texCoord, vec2(0,0) );\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_4U )
		{
			// 4X uniform
			retVal +=	"shadowFactor = lookupShadowMap( texMap, mapSize, texCoord, vec2(-0.5, -0.5) * samplingSize );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(0.5, -0.5) * samplingSize );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(0.5, 0.5) * samplingSize );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(-0.5, 0.5) * samplingSize );\n"
						"shadowFactor *= 0.25;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_4UM )
		{
			// 4X uniform
			// with modulo
			retVal +=	"// use modulo to vary the sample pattern\n"
						"vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"shadowFactor = lookupShadowMap( texMap, mapSize, texCoord, vec2(-0.5, -0.5) * samplingSize + o );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(0.5, -0.5) * samplingSize + o );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(0.5, 0.5) * samplingSize + o );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(-0.5, 0.5) * samplingSize + o );\n"
						"shadowFactor *= 0.25;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_4DM )
		{
			// 4X dither
			// with modulo
			retVal +=	"// use modulo to vary the sample pattern\n"
						"vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"shadowFactor = lookupShadowMap( texMap, mapSize, texCoord, vec2(-1.5, 1.5) * samplingSize  + o );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(0.5, 1.5) * samplingSize  + o );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(-1.5, -0.5) * samplingSize  + o );\n"
						"shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(0.5, -0.5) * samplingSize  + o );\n"
						"shadowFactor *= 0.25;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_9U )
		{
			// 9X uniform
			retVal +=	"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"for( y = -1; y <= 1; y += 1.0 )\n"
						"	for( x = -1; x <= 1; x += 1.0 )\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize );\n"
						"shadowFactor /= 9.0;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_9UM )
		{
			// 9X uniform
			// with modulo
			retVal +=	"// use modulo to vary the sample pattern\n"
						"vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"for( y = -1; y <= 1; y += 1.0 )\n"
						"	for( x = -1; x <= 1; x += 1.0 )\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize + o );\n"
						"shadowFactor /= 9.0;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_16U )
		{
			// 16X uniform
			retVal +=	"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"for( y = -1.5; y <= 1.5; y += 1.0 )\n"
						"	for( x = -1.5; x <= 1.5; x += 1.0 )\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize );\n"
						"shadowFactor /= 16.0;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_16UM )
		{
			// 16X uniform
			// with modulo
			retVal +=	"// use modulo to vary the sample pattern\n"
						"vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"for( y = -1.5; y <= 1.5; y += 1.0 )\n"
						"	for( x = -1.5; x <= 1.5; x += 1.0 )\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize  + o);\n"
						"shadowFactor /= 16.0;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_32U )
		{
			// 32X uniform
			retVal +=	"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"float coeff = sqrt(2.0);\n"
						"int count = 0;\n"
						"for( y = -1.5; y <= 1.5; y += 1.0 / coeff)\n"
						"	for( x = -1.5; x <= 1.5; x += 1.0 / coeff)\n"
						"	{\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize );\n"
						"		count++;\n"
						"	}\n"
						"shadowFactor /= count;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_32UM )
		{
			// 32X dither
			// with modulo
			retVal +=	"// use modulo to vary the sample pattern\n"
						"vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"float coeff = sqrt(2.0);\n"
						"int count = 0;\n"
						"for( y = -1.5; y <= 1.5; y += 1.0 / coeff)\n"
						"	for( x = -1.5; x <= 1.5; x += 1.0 / coeff)\n"
						"	{\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize + o );\n"
						"		count++;\n"
						"	}\n"						
						"shadowFactor /= count;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_64U )
		{
			// 64X uniform
			retVal +=	"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"float coeff = 2.0;\n"
						"int count = 0;\n"
						"for( y = -1.5; y <= 1.5; y += 1.0 / coeff)\n"
						"	for( x = -1.5; x <= 1.5; x += 1.0 / coeff)\n"
						"	{\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize );\n"
						"		count++;\n"
						"	}\n"						
						"shadowFactor /= count;\n";
		}
		else if ( shadowType == LightModel::SHADOW_MAPPING_64UM )
		{
			// 64X dither
			// with modulo
			retVal +=	"// use modulo to vary the sample pattern\n"
						"vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
						"shadowFactor = 0.0;\n"
						"float x, y;\n"
						"float coeff = 2.0;\n"
						"int count = 0;\n"
						"for( y = -1.5; y <= 1.5; y += 1.0 / coeff)\n"
						"	for( x = -1.5; x <= 1.5; x += 1.0 / coeff)\n"
						"	{\n"
						"		shadowFactor += lookupShadowMap( texMap, mapSize, texCoord, vec2(x, y) * samplingSize + o );\n"
						"		count++;\n"
						"	}\n"						
						"shadowFactor /= count;\n";
		}		
		else
		{
			vgAssertN( false, "Unexpected value." );
			retVal =	"shadowFactor = 0.0;\n";
		}

		retVal +=				"//\n";

		// illuminationInShadow
		const float illuminationInShadow = state.getIlluminationInShadow();
		retVal +=		"	const float illuminationInShadow = " + boost::lexical_cast<std::string>(illuminationInShadow) + ";\n"; // @todo should be a uniform param
		retVal += 		"	shadowFactor = max( illuminationInShadow, shadowFactor);\n"
						"	return shadowFactor;\n"
						"}\n\n";

		return flookupShadowMap + retVal;
	}

	// @todo removes /*&*/
	static const std::string /*&*/ generateFunction_spotLight( const GLSLState& state, const bool useBackMaterial, const bool castShadow )
	{
		using vgd::node::LightModel;

		static LightModel::ShadowValueType	shadowType		= LightModel::SHADOW_OFF;
		static float						samplingSize	= 1.f;
		static std::string					shadowString	= generate_fcomputeShadowFactor( state, LightModel::SHADOW_OFF, 1.f );

		static std::string					retValFront;
		static std::string					retValBack;

		// Updates shadow factor computation string
		LightModel::ShadowValueType	incomingShadowType		= state.getShadowType();
		const float					incomingSamplingSize	= state.getSamplingSize();
		if (	(incomingShadowType != shadowType ) ||
				(incomingSamplingSize != samplingSize )	)
		{
			shadowType = incomingShadowType;
			samplingSize = incomingSamplingSize;
			shadowString = generate_fcomputeShadowFactor( state, shadowType, samplingSize );
		}

		//
		if ( retValFront.length() == 0 )
		{
			retValFront =
			"void spotLightFront( int i, vec3 ecPosition3, vec3 normal, vec3 eye, float shadowFactor )\n"
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
			"	VP = normalize(VP);\n"
			"\n"
			"	// Compute attenuation\n"
//		"	attenuation =	1.0;\n"
// @todo uncomments attenuation (when Light node specifies distance attenuation).
//		"	attenuation =	1.0 / (gl_LightSource[i].constantAttenuation +\n"
//		"					gl_LightSource[i].linearAttenuation * d +\n"
//		"					gl_LightSource[i].quadraticAttenuation * d * d);\n"
			"\n"
			"	// See if point on surface is inside cone of illumination\n"
			"	spotDot = dot(-VP, normalize(gl_LightSource[i].spotDirection));\n"

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
			std::string spotLightFrontShadow = 
				"\n"
				"void spotLightFrontShadow( int i, sampler2DShadow texMapShadow, vec4 texCoordShadow, vec3 ecPosition3, vec3 normal, vec3 eye )\n"
				"{\n"
				"	float shadowFactor = computeShadowFactor( texMapShadow, texCoordShadow );\n"
				"\n"
				"	spotLightFront( i, ecPosition3, normal, eye, shadowFactor );\n"
				"}\n\n";

			std::string spotLightBackShadow = spotLightFrontShadow;
			boost::algorithm::replace_all( spotLightBackShadow, "Front", "Back" );
		//}

		// Returns the desired function
		// @todo not always included shadow code
		if ( useBackMaterial )
		{
			return shadowString + retValBack + spotLightBackShadow;
		}
		else
		{
			return shadowString + retValFront + spotLightFrontShadow;
		}
	}


	static void generateFunction_flightFrontAndBack(	const GLSLState& state,
														std::string& flightFront, std::string& flightBack )
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

		flightBack	=
			"// Computes the light contributions for back face\n"
			"void flightBack( in vec3 ecPosition3, in vec3 normal, in vec3 eye )\n"
			"{\n" +
			clearLightIntensityAccumulators;

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
							flightBack		+= "	directionalLightFront( " + iStr + ", normal );\n";
							//currentLightBack	+= "	directionalLightBack( " + iStr + ", -normal );\n";
							break;

						case POINT_LIGHT:
							flightFront		+= "	pointLightFront( " + iStr + ", ecPosition3, normal, eye );\n";
							flightBack		+= "	pointLightFront( " + iStr + ", ecPosition3, normal, eye );\n";
							//currentLightBack	+= "	pointLightBack( " + iStr + ", ecPosition3, -normal, eye );\n";
							break;

						case SPOT_LIGHT:
							if (	state.getShadowType() != vgd::node::LightModel::SHADOW_OFF && 
									currentLightState->getCastShadow() )
							{
								const std::string	texCoordShadowIndexStr	= vgd::basic::toString(lightCastingShadowCount);
								const std::string	texMapIndexStr			= state.getPrivateTexUnit(lightCastingShadowCount);
								const std::string&	texMapShadowIndexStr	= texCoordShadowIndexStr;
								++lightCastingShadowCount;

								flightFront		+= "	spotLightFrontShadow( " + iStr + ", texMap2DShadow[" + texMapShadowIndexStr + "], mgl_TexCoordShadow[" + texCoordShadowIndexStr + "], ecPosition3, normal, eye );\n";
								flightBack		+= "	spotLightFrontShadow( " + iStr + ", texMap2DShadow[" + texMapShadowIndexStr + "], mgl_TexCoordShadow[" + texCoordShadowIndexStr + "], ecPosition3, normal, eye );\n";

								// currentLightBack	+= "	spotLightBack( " + iStr + ", ecPosition3, -normal, eye );\n";
							}
							else
							{
								flightFront		+= "	spotLightFront( " + iStr + ", ecPosition3, normal, eye, 1.0 );\n";
								flightBack		+= "	spotLightFront( " + iStr + ", ecPosition3, normal, eye, 1.0 );\n";
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

		flightBack	+=
		"}\n";
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

			std::string flightFront, flightBack;
			generateFunction_flightFrontAndBack( state, flightFront, flightBack );

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

		if ( mgl_TexCoordShadowCount > 0 )
		{
			decl += storageQualifierDecl + " vec4 mgl_TexCoordShadow[" + vgd::basic::toString(mgl_TexCoordShadowCount) + "];\n";
		}

		decl += "\n";

		return std::make_pair( decl, code );
	}


	static std::pair< std::string, std::string >  generate_samplers( const vgeGL::engine::GLSLState& state )
	{
		std::string decl;

		uint sampler2DCount						= 0;
		uint sampler2DShadowCount				= 0;

		// Contained the last texture node used for shadow mapping. Used to retrieve the shadow map size.
		// Remarks that all shadow map have the same size.
		vgd::node::Texture * shadowTextureNode	= 0;

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
						shadowTextureNode = textureNode;
						break;

					case vgd::node::Texture::IMAGE:
						++sampler2DCount;
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
		}

		// Updates samplers declarations
		if ( sampler2DCount > 0 )
		{
			decl += "uniform sampler2D texMap2D[" + vgd::basic::toString(sampler2DCount) + "];\n\n";
		}

		if ( sampler2DShadowCount > 0 )
		{
			//decl += "uniform sampler2D texMap2DShadow[" + vgd::basic::toString(sampler2DShadowCount) + "];\n";
			decl += "uniform sampler2DShadow texMap2DShadow[" + vgd::basic::toString(sampler2DShadowCount) + "];\n\n";
		}

		return std::make_pair(decl, ""/*code*/);
	}


	// @todo renames generate_texLookups into generate_fragmentShader_texLookups
	static const std::string generate_texLookups( const vgeGL::engine::GLSLState& state )
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
				//const std::string				strUnit		= vgd::basic::toString( i );
				const vgd::node::Texture *		textureNode	= current->getTextureNode();

				if (	textureNode->hasFunction() &&
						textureNode->getUsage() == vgd::node::Texture::IMAGE )
				{
					std::string function;
					textureNode->getFunction( function );
					retVal +=
					"	" + function;
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
