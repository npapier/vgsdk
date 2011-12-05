// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/EnumRegistry.hpp"

#include <vgDebug/helpers.hpp>
#include <vgd/Shp.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/DepthOfField.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Noise.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/Texture.hpp>



namespace vgd
{

namespace node
{



const std::string EnumRegistry::toString( const int enumValue )
{
	if ( m_toString.empty() )
	{
		// Initializes the registry (only once).
		initialize();
	}

	ToStringType::const_iterator iter = m_toString.find( enumValue );

	if ( iter != m_toString.end() )
	{
		return iter->second;
	}
	else
	{
		return std::string("");
	}
}



const vgd::Shp< vgd::field::Enum > EnumRegistry::toEnum( const int enumValue )
{
	if ( m_toEnum.empty() )
	{
		// Initializes the registry (only once).
		initialize();
	}

	ToEnumType::const_iterator iter = m_toEnum.find( enumValue );

	if ( iter != m_toEnum.end() )
	{
		return iter->second;
	}
	else
	{
		return vgd::makeShp( new vgd::field::Enum() );
	}
}



EnumRegistry::ToStringType EnumRegistry::m_toString;



EnumRegistry::ToEnumType EnumRegistry::m_toEnum;



void EnumRegistry::initialize()
{
	// Initializes m_toString map

	//
	#ifdef _DEBUG
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, CHOICE4) already in m_toString enum registry");
		assert( false && "(278, CHOICE4) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("CHOICE4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 277 ) != m_toString.end() )
	{
		vgLogDebug("(277, CHOICE3) already in m_toString enum registry");
		assert( false && "(277, CHOICE3) already in registry" );
	}
	#endif

	m_toString[ 277 ] = std::string("CHOICE3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 276 ) != m_toString.end() )
	{
		vgLogDebug("(276, CHOICE2) already in m_toString enum registry");
		assert( false && "(276, CHOICE2) already in registry" );
	}
	#endif

	m_toString[ 276 ] = std::string("CHOICE2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 275 ) != m_toString.end() )
	{
		vgLogDebug("(275, CHOICE1) already in m_toString enum registry");
		assert( false && "(275, CHOICE1) already in registry" );
	}
	#endif

	m_toString[ 275 ] = std::string("CHOICE1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 274 ) != m_toString.end() )
	{
		vgLogDebug("(274, CHOICE0) already in m_toString enum registry");
		assert( false && "(274, CHOICE0) already in registry" );
	}
	#endif

	m_toString[ 274 ] = std::string("CHOICE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 408 ) != m_toString.end() )
	{
		vgLogDebug("(408, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(408, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 408 ] = std::string("MIN_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 334 ) != m_toString.end() )
	{
		vgLogDebug("(334, ADD) already in m_toString enum registry");
		assert( false && "(334, ADD) already in registry" );
	}
	#endif

	m_toString[ 334 ] = std::string("ADD");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 315 ) != m_toString.end() )
	{
		vgLogDebug("(315, COLOR) already in m_toString enum registry");
		assert( false && "(315, COLOR) already in registry" );
	}
	#endif

	m_toString[ 315 ] = std::string("COLOR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 400 ) != m_toString.end() )
	{
		vgLogDebug("(400, WRAP_T) already in m_toString enum registry");
		assert( false && "(400, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 400 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 257 ) != m_toString.end() )
	{
		vgLogDebug("(257, EYE_RIGHT) already in m_toString enum registry");
		assert( false && "(257, EYE_RIGHT) already in registry" );
	}
	#endif

	m_toString[ 257 ] = std::string("EYE_RIGHT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 404 ) != m_toString.end() )
	{
		vgLogDebug("(404, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(404, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 404 ] = std::string("CLAMP_TO_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 399 ) != m_toString.end() )
	{
		vgLogDebug("(399, WRAP_S) already in m_toString enum registry");
		assert( false && "(399, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 399 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 401 ) != m_toString.end() )
	{
		vgLogDebug("(401, WRAP_R) already in m_toString enum registry");
		assert( false && "(401, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 401 ] = std::string("WRAP_R");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 297 ) != m_toString.end() )
	{
		vgLogDebug("(297, LOW) already in m_toString enum registry");
		assert( false && "(297, LOW) already in registry" );
	}
	#endif

	m_toString[ 297 ] = std::string("LOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 329 ) != m_toString.end() )
	{
		vgLogDebug("(329, BLOOM_VERT) already in m_toString enum registry");
		assert( false && "(329, BLOOM_VERT) already in registry" );
	}
	#endif

	m_toString[ 329 ] = std::string("BLOOM_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 298 ) != m_toString.end() )
	{
		vgLogDebug("(298, MEDIUM) already in m_toString enum registry");
		assert( false && "(298, MEDIUM) already in registry" );
	}
	#endif

	m_toString[ 298 ] = std::string("MEDIUM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 269 ) != m_toString.end() )
	{
		vgLogDebug("(269, CW) already in m_toString enum registry");
		assert( false && "(269, CW) already in registry" );
	}
	#endif

	m_toString[ 269 ] = std::string("CW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, SHADOW_MAPPING_9U) already in m_toString enum registry");
		assert( false && "(289, SHADOW_MAPPING_9U) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("SHADOW_MAPPING_9U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 311 ) != m_toString.end() )
	{
		vgLogDebug("(311, LUMINANCE_FOR_DEPTH) already in m_toString enum registry");
		assert( false && "(311, LUMINANCE_FOR_DEPTH) already in registry" );
	}
	#endif

	m_toString[ 311 ] = std::string("LUMINANCE_FOR_DEPTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, SHADOW_MAPPING) already in m_toString enum registry");
		assert( false && "(285, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("SHADOW_MAPPING");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 389 ) != m_toString.end() )
	{
		vgLogDebug("(389, DEPTH_COMPONENT_32) already in m_toString enum registry");
		assert( false && "(389, DEPTH_COMPONENT_32) already in registry" );
	}
	#endif

	m_toString[ 389 ] = std::string("DEPTH_COMPONENT_32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 268 ) != m_toString.end() )
	{
		vgLogDebug("(268, CCW) already in m_toString enum registry");
		assert( false && "(268, CCW) already in registry" );
	}
	#endif

	m_toString[ 268 ] = std::string("CCW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 415 ) != m_toString.end() )
	{
		vgLogDebug("(415, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(415, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 415 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 402 ) != m_toString.end() )
	{
		vgLogDebug("(402, REPEAT) already in m_toString enum registry");
		assert( false && "(402, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 402 ] = std::string("REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 395 ) != m_toString.end() )
	{
		vgLogDebug("(395, LUMINANCE_16F) already in m_toString enum registry");
		assert( false && "(395, LUMINANCE_16F) already in registry" );
	}
	#endif

	m_toString[ 395 ] = std::string("LUMINANCE_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 372 ) != m_toString.end() )
	{
		vgLogDebug("(372, INPUT2_TEXTURE0) already in m_toString enum registry");
		assert( false && "(372, INPUT2_TEXTURE0) already in registry" );
	}
	#endif

	m_toString[ 372 ] = std::string("INPUT2_TEXTURE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 328 ) != m_toString.end() )
	{
		vgLogDebug("(328, BLOOM_HORIZ) already in m_toString enum registry");
		assert( false && "(328, BLOOM_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 328 ] = std::string("BLOOM_HORIZ");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 338 ) != m_toString.end() )
	{
		vgLogDebug("(338, COMBINE2_AND_SCALE) already in m_toString enum registry");
		assert( false && "(338, COMBINE2_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 338 ] = std::string("COMBINE2_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 327 ) != m_toString.end() )
	{
		vgLogDebug("(327, BLUR_VERT) already in m_toString enum registry");
		assert( false && "(327, BLUR_VERT) already in registry" );
	}
	#endif

	m_toString[ 327 ] = std::string("BLUR_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 356 ) != m_toString.end() )
	{
		vgLogDebug("(356, INPUT1_OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(356, INPUT1_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 356 ] = std::string("INPUT1_OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, PINHOLE) already in m_toString enum registry");
		assert( false && "(266, PINHOLE) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("PINHOLE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 403 ) != m_toString.end() )
	{
		vgLogDebug("(403, CLAMP) already in m_toString enum registry");
		assert( false && "(403, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 403 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 407 ) != m_toString.end() )
	{
		vgLogDebug("(407, ONCE) already in m_toString enum registry");
		assert( false && "(407, ONCE) already in registry" );
	}
	#endif

	m_toString[ 407 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 413 ) != m_toString.end() )
	{
		vgLogDebug("(413, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(413, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 413 ] = std::string("LINEAR_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 301 ) != m_toString.end() )
	{
		vgLogDebug("(301, NEAREST) already in m_toString enum registry");
		assert( false && "(301, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 301 ] = std::string("NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 312 ) != m_toString.end() )
	{
		vgLogDebug("(312, INTEGER) already in m_toString enum registry");
		assert( false && "(312, INTEGER) already in registry" );
	}
	#endif

	m_toString[ 312 ] = std::string("INTEGER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 339 ) != m_toString.end() )
	{
		vgLogDebug("(339, COMBINE3_AND_SCALE) already in m_toString enum registry");
		assert( false && "(339, COMBINE3_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 339 ] = std::string("COMBINE3_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 282 ) != m_toString.end() )
	{
		vgLogDebug("(282, AT_INFINITY) already in m_toString enum registry");
		assert( false && "(282, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 282 ] = std::string("AT_INFINITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 377 ) != m_toString.end() )
	{
		vgLogDebug("(377, OUTPUT_OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(377, OUTPUT_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 377 ] = std::string("OUTPUT_OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 388 ) != m_toString.end() )
	{
		vgLogDebug("(388, DEPTH_COMPONENT_24) already in m_toString enum registry");
		assert( false && "(388, DEPTH_COMPONENT_24) already in registry" );
	}
	#endif

	m_toString[ 388 ] = std::string("DEPTH_COMPONENT_24");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 306 ) != m_toString.end() )
	{
		vgLogDebug("(306, PIXEL_SIZE) already in m_toString enum registry");
		assert( false && "(306, PIXEL_SIZE) already in registry" );
	}
	#endif

	m_toString[ 306 ] = std::string("PIXEL_SIZE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 385 ) != m_toString.end() )
	{
		vgLogDebug("(385, SHADOW) already in m_toString enum registry");
		assert( false && "(385, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 385 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 294 ) != m_toString.end() )
	{
		vgLogDebug("(294, SHADOW_MAPPING_32UM) already in m_toString enum registry");
		assert( false && "(294, SHADOW_MAPPING_32UM) already in registry" );
	}
	#endif

	m_toString[ 294 ] = std::string("SHADOW_MAPPING_32UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 406 ) != m_toString.end() )
	{
		vgLogDebug("(406, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(406, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 406 ] = std::string("MIRRORED_REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 391 ) != m_toString.end() )
	{
		vgLogDebug("(391, RGB_16F) already in m_toString enum registry");
		assert( false && "(391, RGB_16F) already in registry" );
	}
	#endif

	m_toString[ 391 ] = std::string("RGB_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 310 ) != m_toString.end() )
	{
		vgLogDebug("(310, LUMINANCE_ALPHA) already in m_toString enum registry");
		assert( false && "(310, LUMINANCE_ALPHA) already in registry" );
	}
	#endif

	m_toString[ 310 ] = std::string("LUMINANCE_ALPHA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 316 ) != m_toString.end() )
	{
		vgLogDebug("(316, NORMAL) already in m_toString enum registry");
		assert( false && "(316, NORMAL) already in registry" );
	}
	#endif

	m_toString[ 316 ] = std::string("NORMAL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 380 ) != m_toString.end() )
	{
		vgLogDebug("(380, OUTPUT_OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(380, OUTPUT_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 380 ] = std::string("OUTPUT_OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 375 ) != m_toString.end() )
	{
		vgLogDebug("(375, OUTPUT_TMP0) already in m_toString enum registry");
		assert( false && "(375, OUTPUT_TMP0) already in registry" );
	}
	#endif

	m_toString[ 375 ] = std::string("OUTPUT_TMP0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 393 ) != m_toString.end() )
	{
		vgLogDebug("(393, RGBA_16F) already in m_toString enum registry");
		assert( false && "(393, RGBA_16F) already in registry" );
	}
	#endif

	m_toString[ 393 ] = std::string("RGBA_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 351 ) != m_toString.end() )
	{
		vgLogDebug("(351, PREVIOUS0) already in m_toString enum registry");
		assert( false && "(351, PREVIOUS0) already in registry" );
	}
	#endif

	m_toString[ 351 ] = std::string("PREVIOUS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, THIN_LENS) already in m_toString enum registry");
		assert( false && "(267, THIN_LENS) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("THIN_LENS");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 336 ) != m_toString.end() )
	{
		vgLogDebug("(336, MIX_AND_SCALE) already in m_toString enum registry");
		assert( false && "(336, MIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 336 ] = std::string("MIX_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 384 ) != m_toString.end() )
	{
		vgLogDebug("(384, IMAGE) already in m_toString enum registry");
		assert( false && "(384, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 384 ] = std::string("IMAGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 299 ) != m_toString.end() )
	{
		vgLogDebug("(299, HIGH) already in m_toString enum registry");
		assert( false && "(299, HIGH) already in registry" );
	}
	#endif

	m_toString[ 299 ] = std::string("HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 387 ) != m_toString.end() )
	{
		vgLogDebug("(387, DEPTH_COMPONENT_16) already in m_toString enum registry");
		assert( false && "(387, DEPTH_COMPONENT_16) already in registry" );
	}
	#endif

	m_toString[ 387 ] = std::string("DEPTH_COMPONENT_16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 397 ) != m_toString.end() )
	{
		vgLogDebug("(397, LUMINANCE_ALPHA_16F) already in m_toString enum registry");
		assert( false && "(397, LUMINANCE_ALPHA_16F) already in registry" );
	}
	#endif

	m_toString[ 397 ] = std::string("LUMINANCE_ALPHA_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 293 ) != m_toString.end() )
	{
		vgLogDebug("(293, SHADOW_MAPPING_32U) already in m_toString enum registry");
		assert( false && "(293, SHADOW_MAPPING_32U) already in registry" );
	}
	#endif

	m_toString[ 293 ] = std::string("SHADOW_MAPPING_32U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 307 ) != m_toString.end() )
	{
		vgLogDebug("(307, RGB) already in m_toString enum registry");
		assert( false && "(307, RGB) already in registry" );
	}
	#endif

	m_toString[ 307 ] = std::string("RGB");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 337 ) != m_toString.end() )
	{
		vgLogDebug("(337, ALPHAMIX_AND_SCALE) already in m_toString enum registry");
		assert( false && "(337, ALPHAMIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 337 ] = std::string("ALPHAMIX_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 309 ) != m_toString.end() )
	{
		vgLogDebug("(309, LUMINANCE) already in m_toString enum registry");
		assert( false && "(309, LUMINANCE) already in registry" );
	}
	#endif

	m_toString[ 309 ] = std::string("LUMINANCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 344 ) != m_toString.end() )
	{
		vgLogDebug("(344, OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(344, OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 344 ] = std::string("OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 343 ) != m_toString.end() )
	{
		vgLogDebug("(343, OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(343, OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 343 ] = std::string("OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 342 ) != m_toString.end() )
	{
		vgLogDebug("(342, OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(342, OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 342 ] = std::string("OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 349 ) != m_toString.end() )
	{
		vgLogDebug("(349, OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(349, OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 349 ] = std::string("OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 348 ) != m_toString.end() )
	{
		vgLogDebug("(348, OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(348, OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 348 ] = std::string("OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 347 ) != m_toString.end() )
	{
		vgLogDebug("(347, OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(347, OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 347 ] = std::string("OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 346 ) != m_toString.end() )
	{
		vgLogDebug("(346, OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(346, OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 346 ] = std::string("OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 313 ) != m_toString.end() )
	{
		vgLogDebug("(313, FLOAT16) already in m_toString enum registry");
		assert( false && "(313, FLOAT16) already in registry" );
	}
	#endif

	m_toString[ 313 ] = std::string("FLOAT16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 279 ) != m_toString.end() )
	{
		vgLogDebug("(279, LIGHTING_OFF) already in m_toString enum registry");
		assert( false && "(279, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 279 ] = std::string("LIGHTING_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 410 ) != m_toString.end() )
	{
		vgLogDebug("(410, NEAREST) already in m_toString enum registry");
		assert( false && "(410, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 410 ] = std::string("NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 386 ) != m_toString.end() )
	{
		vgLogDebug("(386, AUTOMATIC) already in m_toString enum registry");
		assert( false && "(386, AUTOMATIC) already in registry" );
	}
	#endif

	m_toString[ 386 ] = std::string("AUTOMATIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 345 ) != m_toString.end() )
	{
		vgLogDebug("(345, OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(345, OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 345 ] = std::string("OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 271 ) != m_toString.end() )
	{
		vgLogDebug("(271, INT24) already in m_toString enum registry");
		assert( false && "(271, INT24) already in registry" );
	}
	#endif

	m_toString[ 271 ] = std::string("INT24");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 361 ) != m_toString.end() )
	{
		vgLogDebug("(361, INPUT1_TEXTURE0) already in m_toString enum registry");
		assert( false && "(361, INPUT1_TEXTURE0) already in registry" );
	}
	#endif

	m_toString[ 361 ] = std::string("INPUT1_TEXTURE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 414 ) != m_toString.end() )
	{
		vgLogDebug("(414, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(414, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 414 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 261 ) != m_toString.end() )
	{
		vgLogDebug("(261, ANAGLYPH) already in m_toString enum registry");
		assert( false && "(261, ANAGLYPH) already in registry" );
	}
	#endif

	m_toString[ 261 ] = std::string("ANAGLYPH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 256 ) != m_toString.end() )
	{
		vgLogDebug("(256, EYE_LEFT) already in m_toString enum registry");
		assert( false && "(256, EYE_LEFT) already in registry" );
	}
	#endif

	m_toString[ 256 ] = std::string("EYE_LEFT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 259 ) != m_toString.end() )
	{
		vgLogDebug("(259, MONOSCOPIC) already in m_toString enum registry");
		assert( false && "(259, MONOSCOPIC) already in registry" );
	}
	#endif

	m_toString[ 259 ] = std::string("MONOSCOPIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 324 ) != m_toString.end() )
	{
		vgLogDebug("(324, COLOR_INVERSE) already in m_toString enum registry");
		assert( false && "(324, COLOR_INVERSE) already in registry" );
	}
	#endif

	m_toString[ 324 ] = std::string("COLOR_INVERSE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 409 ) != m_toString.end() )
	{
		vgLogDebug("(409, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(409, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 409 ] = std::string("MAG_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 363 ) != m_toString.end() )
	{
		vgLogDebug("(363, INPUT1_NONE) already in m_toString enum registry");
		assert( false && "(363, INPUT1_NONE) already in registry" );
	}
	#endif

	m_toString[ 363 ] = std::string("INPUT1_NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 273 ) != m_toString.end() )
	{
		vgLogDebug("(273, FLOAT32) already in m_toString enum registry");
		assert( false && "(273, FLOAT32) already in registry" );
	}
	#endif

	m_toString[ 273 ] = std::string("FLOAT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 373 ) != m_toString.end() )
	{
		vgLogDebug("(373, INPUT2_PREVIOUS0) already in m_toString enum registry");
		assert( false && "(373, INPUT2_PREVIOUS0) already in registry" );
	}
	#endif

	m_toString[ 373 ] = std::string("INPUT2_PREVIOUS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 258 ) != m_toString.end() )
	{
		vgLogDebug("(258, EYE_BOTH) already in m_toString enum registry");
		assert( false && "(258, EYE_BOTH) already in registry" );
	}
	#endif

	m_toString[ 258 ] = std::string("EYE_BOTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 295 ) != m_toString.end() )
	{
		vgLogDebug("(295, SHADOW_MAPPING_64U) already in m_toString enum registry");
		assert( false && "(295, SHADOW_MAPPING_64U) already in registry" );
	}
	#endif

	m_toString[ 295 ] = std::string("SHADOW_MAPPING_64U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 322 ) != m_toString.end() )
	{
		vgLogDebug("(322, COLOR_TO_MONOCHROME) already in m_toString enum registry");
		assert( false && "(322, COLOR_TO_MONOCHROME) already in registry" );
	}
	#endif

	m_toString[ 322 ] = std::string("COLOR_TO_MONOCHROME");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, SHADOW_MAPPING_4DM) already in m_toString enum registry");
		assert( false && "(288, SHADOW_MAPPING_4DM) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("SHADOW_MAPPING_4DM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 355 ) != m_toString.end() )
	{
		vgLogDebug("(355, INPUT1_OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(355, INPUT1_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 355 ] = std::string("INPUT1_OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 354 ) != m_toString.end() )
	{
		vgLogDebug("(354, INPUT1_OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(354, INPUT1_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 354 ] = std::string("INPUT1_OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 353 ) != m_toString.end() )
	{
		vgLogDebug("(353, INPUT1_OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(353, INPUT1_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 353 ] = std::string("INPUT1_OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 360 ) != m_toString.end() )
	{
		vgLogDebug("(360, INPUT1_OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(360, INPUT1_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 360 ] = std::string("INPUT1_OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 359 ) != m_toString.end() )
	{
		vgLogDebug("(359, INPUT1_OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(359, INPUT1_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 359 ] = std::string("INPUT1_OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 358 ) != m_toString.end() )
	{
		vgLogDebug("(358, INPUT1_OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(358, INPUT1_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 358 ] = std::string("INPUT1_OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 357 ) != m_toString.end() )
	{
		vgLogDebug("(357, INPUT1_OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(357, INPUT1_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 357 ] = std::string("INPUT1_OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 319 ) != m_toString.end() )
	{
		vgLogDebug("(319, LINEAR_DEPTH) already in m_toString enum registry");
		assert( false && "(319, LINEAR_DEPTH) already in registry" );
	}
	#endif

	m_toString[ 319 ] = std::string("LINEAR_DEPTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 321 ) != m_toString.end() )
	{
		vgLogDebug("(321, IDENTITY) already in m_toString enum registry");
		assert( false && "(321, IDENTITY) already in registry" );
	}
	#endif

	m_toString[ 321 ] = std::string("IDENTITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 284 ) != m_toString.end() )
	{
		vgLogDebug("(284, SHADOW_OFF) already in m_toString enum registry");
		assert( false && "(284, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toString[ 284 ] = std::string("SHADOW_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 272 ) != m_toString.end() )
	{
		vgLogDebug("(272, INT32) already in m_toString enum registry");
		assert( false && "(272, INT32) already in registry" );
	}
	#endif

	m_toString[ 272 ] = std::string("INT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 303 ) != m_toString.end() )
	{
		vgLogDebug("(303, NO) already in m_toString enum registry");
		assert( false && "(303, NO) already in registry" );
	}
	#endif

	m_toString[ 303 ] = std::string("NO");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 325 ) != m_toString.end() )
	{
		vgLogDebug("(325, SCALE_AND_BIAS) already in m_toString enum registry");
		assert( false && "(325, SCALE_AND_BIAS) already in registry" );
	}
	#endif

	m_toString[ 325 ] = std::string("SCALE_AND_BIAS");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 394 ) != m_toString.end() )
	{
		vgLogDebug("(394, RGBA_32F) already in m_toString enum registry");
		assert( false && "(394, RGBA_32F) already in registry" );
	}
	#endif

	m_toString[ 394 ] = std::string("RGBA_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, FRONT) already in m_toString enum registry");
		assert( false && "(264, FRONT) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("FRONT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 304 ) != m_toString.end() )
	{
		vgLogDebug("(304, PHOTON) already in m_toString enum registry");
		assert( false && "(304, PHOTON) already in registry" );
	}
	#endif

	m_toString[ 304 ] = std::string("PHOTON");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 260 ) != m_toString.end() )
	{
		vgLogDebug("(260, QUAD_BUFFER) already in m_toString enum registry");
		assert( false && "(260, QUAD_BUFFER) already in registry" );
	}
	#endif

	m_toString[ 260 ] = std::string("QUAD_BUFFER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 333 ) != m_toString.end() )
	{
		vgLogDebug("(333, OVER) already in m_toString enum registry");
		assert( false && "(333, OVER) already in registry" );
	}
	#endif

	m_toString[ 333 ] = std::string("OVER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 314 ) != m_toString.end() )
	{
		vgLogDebug("(314, FLOAT32) already in m_toString enum registry");
		assert( false && "(314, FLOAT32) already in registry" );
	}
	#endif

	m_toString[ 314 ] = std::string("FLOAT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 352 ) != m_toString.end() )
	{
		vgLogDebug("(352, NONE) already in m_toString enum registry");
		assert( false && "(352, NONE) already in registry" );
	}
	#endif

	m_toString[ 352 ] = std::string("NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 308 ) != m_toString.end() )
	{
		vgLogDebug("(308, RGBA) already in m_toString enum registry");
		assert( false && "(308, RGBA) already in registry" );
	}
	#endif

	m_toString[ 308 ] = std::string("RGBA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 320 ) != m_toString.end() )
	{
		vgLogDebug("(320, CUSTOM) already in m_toString enum registry");
		assert( false && "(320, CUSTOM) already in registry" );
	}
	#endif

	m_toString[ 320 ] = std::string("CUSTOM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 405 ) != m_toString.end() )
	{
		vgLogDebug("(405, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(405, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 405 ] = std::string("CLAMP_TO_BORDER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 296 ) != m_toString.end() )
	{
		vgLogDebug("(296, SHADOW_MAPPING_64UM) already in m_toString enum registry");
		assert( false && "(296, SHADOW_MAPPING_64UM) already in registry" );
	}
	#endif

	m_toString[ 296 ] = std::string("SHADOW_MAPPING_64UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 335 ) != m_toString.end() )
	{
		vgLogDebug("(335, SUB) already in m_toString enum registry");
		assert( false && "(335, SUB) already in registry" );
	}
	#endif

	m_toString[ 335 ] = std::string("SUB");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 302 ) != m_toString.end() )
	{
		vgLogDebug("(302, LINEAR) already in m_toString enum registry");
		assert( false && "(302, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 302 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 379 ) != m_toString.end() )
	{
		vgLogDebug("(379, OUTPUT_OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(379, OUTPUT_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 379 ] = std::string("OUTPUT_OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 378 ) != m_toString.end() )
	{
		vgLogDebug("(378, OUTPUT_OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(378, OUTPUT_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 378 ] = std::string("OUTPUT_OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 350 ) != m_toString.end() )
	{
		vgLogDebug("(350, TEXTURE0) already in m_toString enum registry");
		assert( false && "(350, TEXTURE0) already in registry" );
	}
	#endif

	m_toString[ 350 ] = std::string("TEXTURE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 376 ) != m_toString.end() )
	{
		vgLogDebug("(376, OUTPUT_OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(376, OUTPUT_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 376 ] = std::string("OUTPUT_OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 383 ) != m_toString.end() )
	{
		vgLogDebug("(383, OUTPUT_OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(383, OUTPUT_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 383 ] = std::string("OUTPUT_OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 382 ) != m_toString.end() )
	{
		vgLogDebug("(382, OUTPUT_OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(382, OUTPUT_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 382 ] = std::string("OUTPUT_OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 381 ) != m_toString.end() )
	{
		vgLogDebug("(381, OUTPUT_OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(381, OUTPUT_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 381 ] = std::string("OUTPUT_OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, SHADOW_MAPPING_4UM) already in m_toString enum registry");
		assert( false && "(287, SHADOW_MAPPING_4UM) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("SHADOW_MAPPING_4UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 318 ) != m_toString.end() )
	{
		vgLogDebug("(318, DEPTH) already in m_toString enum registry");
		assert( false && "(318, DEPTH) already in registry" );
	}
	#endif

	m_toString[ 318 ] = std::string("DEPTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 364 ) != m_toString.end() )
	{
		vgLogDebug("(364, INPUT2_OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(364, INPUT2_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 364 ] = std::string("INPUT2_OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 396 ) != m_toString.end() )
	{
		vgLogDebug("(396, LUMINANCE_32F) already in m_toString enum registry");
		assert( false && "(396, LUMINANCE_32F) already in registry" );
	}
	#endif

	m_toString[ 396 ] = std::string("LUMINANCE_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 366 ) != m_toString.end() )
	{
		vgLogDebug("(366, INPUT2_OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(366, INPUT2_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 366 ] = std::string("INPUT2_OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 330 ) != m_toString.end() )
	{
		vgLogDebug("(330, COLOR_EDGE_DETECT) already in m_toString enum registry");
		assert( false && "(330, COLOR_EDGE_DETECT) already in registry" );
	}
	#endif

	m_toString[ 330 ] = std::string("COLOR_EDGE_DETECT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 412 ) != m_toString.end() )
	{
		vgLogDebug("(412, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(412, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 412 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 326 ) != m_toString.end() )
	{
		vgLogDebug("(326, BLUR_HORIZ) already in m_toString enum registry");
		assert( false && "(326, BLUR_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 326 ] = std::string("BLUR_HORIZ");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 323 ) != m_toString.end() )
	{
		vgLogDebug("(323, COLOR_TO_SEPIA) already in m_toString enum registry");
		assert( false && "(323, COLOR_TO_SEPIA) already in registry" );
	}
	#endif

	m_toString[ 323 ] = std::string("COLOR_TO_SEPIA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, SHADOW_MAPPING_4U) already in m_toString enum registry");
		assert( false && "(286, SHADOW_MAPPING_4U) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("SHADOW_MAPPING_4U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 411 ) != m_toString.end() )
	{
		vgLogDebug("(411, LINEAR) already in m_toString enum registry");
		assert( false && "(411, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 411 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, DISABLED) already in m_toString enum registry");
		assert( false && "(262, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 270 ) != m_toString.end() )
	{
		vgLogDebug("(270, INT16) already in m_toString enum registry");
		assert( false && "(270, INT16) already in registry" );
	}
	#endif

	m_toString[ 270 ] = std::string("INT16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 398 ) != m_toString.end() )
	{
		vgLogDebug("(398, LUMINANCE_ALPHA_32F) already in m_toString enum registry");
		assert( false && "(398, LUMINANCE_ALPHA_32F) already in registry" );
	}
	#endif

	m_toString[ 398 ] = std::string("LUMINANCE_ALPHA_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, BACK) already in m_toString enum registry");
		assert( false && "(263, BACK) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, SHADOW_MAPPING_9UM) already in m_toString enum registry");
		assert( false && "(290, SHADOW_MAPPING_9UM) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("SHADOW_MAPPING_9UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, SHADOW_MAPPING_16U) already in m_toString enum registry");
		assert( false && "(291, SHADOW_MAPPING_16U) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("SHADOW_MAPPING_16U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 283 ) != m_toString.end() )
	{
		vgLogDebug("(283, AT_EYE) already in m_toString enum registry");
		assert( false && "(283, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 283 ] = std::string("AT_EYE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 332 ) != m_toString.end() )
	{
		vgLogDebug("(332, UP_FILTER4) already in m_toString enum registry");
		assert( false && "(332, UP_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 332 ] = std::string("UP_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 390 ) != m_toString.end() )
	{
		vgLogDebug("(390, DEPTH_COMPONENT_32F) already in m_toString enum registry");
		assert( false && "(390, DEPTH_COMPONENT_32F) already in registry" );
	}
	#endif

	m_toString[ 390 ] = std::string("DEPTH_COMPONENT_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 300 ) != m_toString.end() )
	{
		vgLogDebug("(300, VERY_HIGH) already in m_toString enum registry");
		assert( false && "(300, VERY_HIGH) already in registry" );
	}
	#endif

	m_toString[ 300 ] = std::string("VERY_HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 331 ) != m_toString.end() )
	{
		vgLogDebug("(331, DOWN_FILTER4) already in m_toString enum registry");
		assert( false && "(331, DOWN_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 331 ] = std::string("DOWN_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 341 ) != m_toString.end() )
	{
		vgLogDebug("(341, CUSTOM_FILTER) already in m_toString enum registry");
		assert( false && "(341, CUSTOM_FILTER) already in registry" );
	}
	#endif

	m_toString[ 341 ] = std::string("CUSTOM_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 317 ) != m_toString.end() )
	{
		vgLogDebug("(317, POSITION) already in m_toString enum registry");
		assert( false && "(317, POSITION) already in registry" );
	}
	#endif

	m_toString[ 317 ] = std::string("POSITION");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 392 ) != m_toString.end() )
	{
		vgLogDebug("(392, RGB_32F) already in m_toString enum registry");
		assert( false && "(392, RGB_32F) already in registry" );
	}
	#endif

	m_toString[ 392 ] = std::string("RGB_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 292 ) != m_toString.end() )
	{
		vgLogDebug("(292, SHADOW_MAPPING_16UM) already in m_toString enum registry");
		assert( false && "(292, SHADOW_MAPPING_16UM) already in registry" );
	}
	#endif

	m_toString[ 292 ] = std::string("SHADOW_MAPPING_16UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, FRONT_AND_BACK) already in m_toString enum registry");
		assert( false && "(265, FRONT_AND_BACK) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("FRONT_AND_BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 365 ) != m_toString.end() )
	{
		vgLogDebug("(365, INPUT2_OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(365, INPUT2_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 365 ] = std::string("INPUT2_OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 281 ) != m_toString.end() )
	{
		vgLogDebug("(281, STANDARD_PER_PIXEL) already in m_toString enum registry");
		assert( false && "(281, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toString[ 281 ] = std::string("STANDARD_PER_PIXEL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 367 ) != m_toString.end() )
	{
		vgLogDebug("(367, INPUT2_OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(367, INPUT2_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 367 ] = std::string("INPUT2_OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 362 ) != m_toString.end() )
	{
		vgLogDebug("(362, INPUT1_PREVIOUS0) already in m_toString enum registry");
		assert( false && "(362, INPUT1_PREVIOUS0) already in registry" );
	}
	#endif

	m_toString[ 362 ] = std::string("INPUT1_PREVIOUS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 369 ) != m_toString.end() )
	{
		vgLogDebug("(369, INPUT2_OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(369, INPUT2_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 369 ] = std::string("INPUT2_OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 368 ) != m_toString.end() )
	{
		vgLogDebug("(368, INPUT2_OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(368, INPUT2_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 368 ] = std::string("INPUT2_OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 371 ) != m_toString.end() )
	{
		vgLogDebug("(371, INPUT2_OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(371, INPUT2_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 371 ] = std::string("INPUT2_OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 370 ) != m_toString.end() )
	{
		vgLogDebug("(370, INPUT2_OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(370, INPUT2_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 370 ] = std::string("INPUT2_OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 340 ) != m_toString.end() )
	{
		vgLogDebug("(340, NO_FILTER) already in m_toString enum registry");
		assert( false && "(340, NO_FILTER) already in registry" );
	}
	#endif

	m_toString[ 340 ] = std::string("NO_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 305 ) != m_toString.end() )
	{
		vgLogDebug("(305, SCALE_FACTOR) already in m_toString enum registry");
		assert( false && "(305, SCALE_FACTOR) already in registry" );
	}
	#endif

	m_toString[ 305 ] = std::string("SCALE_FACTOR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, STANDARD_PER_VERTEX) already in m_toString enum registry");
		assert( false && "(280, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("STANDARD_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 374 ) != m_toString.end() )
	{
		vgLogDebug("(374, INPUT2_NONE) already in m_toString enum registry");
		assert( false && "(374, INPUT2_NONE) already in registry" );
	}
	#endif

	m_toString[ 374 ] = std::string("INPUT2_NONE");

	// Initializes m_toEnum map

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 278 ) != m_toEnum.end() )
	{
		vgLogDebug("(278, Option0ValueType) already in m_toEnum enum registry");
		assert( false && "(278, Option0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 278 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(278) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, Option0ValueType) already in m_toEnum enum registry");
		assert( false && "(277, Option0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(277) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 276 ) != m_toEnum.end() )
	{
		vgLogDebug("(276, Option0ValueType) already in m_toEnum enum registry");
		assert( false && "(276, Option0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 276 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(276) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 275 ) != m_toEnum.end() )
	{
		vgLogDebug("(275, Option0ValueType) already in m_toEnum enum registry");
		assert( false && "(275, Option0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 275 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(275) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 274 ) != m_toEnum.end() )
	{
		vgLogDebug("(274, Option0ValueType) already in m_toEnum enum registry");
		assert( false && "(274, Option0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 274 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(274) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 408 ) != m_toEnum.end() )
	{
		vgLogDebug("(408, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(408, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 408 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(408) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 334 ) != m_toEnum.end() )
	{
		vgLogDebug("(334, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(334, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 334 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(334) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 315 ) != m_toEnum.end() )
	{
		vgLogDebug("(315, CommandValueType) already in m_toEnum enum registry");
		assert( false && "(315, CommandValueType) already in registry" );
	}
	#endif

	m_toEnum[ 315 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(315) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 400 ) != m_toEnum.end() )
	{
		vgLogDebug("(400, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(400, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 400 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(400) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 257 ) != m_toEnum.end() )
	{
		vgLogDebug("(257, EyeUsagePolicyValueType) already in m_toEnum enum registry");
		assert( false && "(257, EyeUsagePolicyValueType) already in registry" );
	}
	#endif

	m_toEnum[ 257 ] = vgd::makeShp( new vgd::node::Camera::EyeUsagePolicyValueType(257) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 404 ) != m_toEnum.end() )
	{
		vgLogDebug("(404, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(404, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 404 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(404) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 399 ) != m_toEnum.end() )
	{
		vgLogDebug("(399, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(399, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 399 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(399) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 401 ) != m_toEnum.end() )
	{
		vgLogDebug("(401, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(401, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 401 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(401) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 297 ) != m_toEnum.end() )
	{
		vgLogDebug("(297, ShadowMapSizeValueType) already in m_toEnum enum registry");
		assert( false && "(297, ShadowMapSizeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 297 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(297) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 329 ) != m_toEnum.end() )
	{
		vgLogDebug("(329, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(329, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 329 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(329) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 298 ) != m_toEnum.end() )
	{
		vgLogDebug("(298, ShadowMapSizeValueType) already in m_toEnum enum registry");
		assert( false && "(298, ShadowMapSizeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 298 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(298) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 269 ) != m_toEnum.end() )
	{
		vgLogDebug("(269, OrientationValueType) already in m_toEnum enum registry");
		assert( false && "(269, OrientationValueType) already in registry" );
	}
	#endif

	m_toEnum[ 269 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(269) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 289 ) != m_toEnum.end() )
	{
		vgLogDebug("(289, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(289, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 289 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(289) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 311 ) != m_toEnum.end() )
	{
		vgLogDebug("(311, FormatValueType) already in m_toEnum enum registry");
		assert( false && "(311, FormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 311 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(311) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(285, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(285) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 389 ) != m_toEnum.end() )
	{
		vgLogDebug("(389, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(389, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 389 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(389) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 268 ) != m_toEnum.end() )
	{
		vgLogDebug("(268, OrientationValueType) already in m_toEnum enum registry");
		assert( false && "(268, OrientationValueType) already in registry" );
	}
	#endif

	m_toEnum[ 268 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(268) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 415 ) != m_toEnum.end() )
	{
		vgLogDebug("(415, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(415, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 415 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(415) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 402 ) != m_toEnum.end() )
	{
		vgLogDebug("(402, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(402, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 402 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(402) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 395 ) != m_toEnum.end() )
	{
		vgLogDebug("(395, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(395, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 395 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(395) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 372 ) != m_toEnum.end() )
	{
		vgLogDebug("(372, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(372, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 372 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(372) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 328 ) != m_toEnum.end() )
	{
		vgLogDebug("(328, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(328, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 328 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(328) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 338 ) != m_toEnum.end() )
	{
		vgLogDebug("(338, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(338, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 338 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(338) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 327 ) != m_toEnum.end() )
	{
		vgLogDebug("(327, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(327, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 327 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(327) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 356 ) != m_toEnum.end() )
	{
		vgLogDebug("(356, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(356, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 356 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(356) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 266 ) != m_toEnum.end() )
	{
		vgLogDebug("(266, CameraModelValueType) already in m_toEnum enum registry");
		assert( false && "(266, CameraModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 266 ] = vgd::makeShp( new vgd::node::DepthOfField::CameraModelValueType(266) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 403 ) != m_toEnum.end() )
	{
		vgLogDebug("(403, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(403, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 403 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(403) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 407 ) != m_toEnum.end() )
	{
		vgLogDebug("(407, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(407, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 407 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(407) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 413 ) != m_toEnum.end() )
	{
		vgLogDebug("(413, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(413, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 413 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(413) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 301 ) != m_toEnum.end() )
	{
		vgLogDebug("(301, ShadowFilteringValueType) already in m_toEnum enum registry");
		assert( false && "(301, ShadowFilteringValueType) already in registry" );
	}
	#endif

	m_toEnum[ 301 ] = vgd::makeShp( new vgd::node::LightModel::ShadowFilteringValueType(301) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 312 ) != m_toEnum.end() )
	{
		vgLogDebug("(312, TypeValueType) already in m_toEnum enum registry");
		assert( false && "(312, TypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 312 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::TypeValueType(312) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 339 ) != m_toEnum.end() )
	{
		vgLogDebug("(339, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(339, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 339 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(339) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 282 ) != m_toEnum.end() )
	{
		vgLogDebug("(282, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(282, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 282 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(282) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 377 ) != m_toEnum.end() )
	{
		vgLogDebug("(377, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(377, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 377 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(377) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 388 ) != m_toEnum.end() )
	{
		vgLogDebug("(388, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(388, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 388 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(388) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 306 ) != m_toEnum.end() )
	{
		vgLogDebug("(306, SizeSemanticValueType) already in m_toEnum enum registry");
		assert( false && "(306, SizeSemanticValueType) already in registry" );
	}
	#endif

	m_toEnum[ 306 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::SizeSemanticValueType(306) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 385 ) != m_toEnum.end() )
	{
		vgLogDebug("(385, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(385, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 385 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(385) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 294 ) != m_toEnum.end() )
	{
		vgLogDebug("(294, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(294, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 294 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(294) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 406 ) != m_toEnum.end() )
	{
		vgLogDebug("(406, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(406, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 406 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(406) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 391 ) != m_toEnum.end() )
	{
		vgLogDebug("(391, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(391, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 391 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(391) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 310 ) != m_toEnum.end() )
	{
		vgLogDebug("(310, FormatValueType) already in m_toEnum enum registry");
		assert( false && "(310, FormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 310 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(310) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 316 ) != m_toEnum.end() )
	{
		vgLogDebug("(316, CommandValueType) already in m_toEnum enum registry");
		assert( false && "(316, CommandValueType) already in registry" );
	}
	#endif

	m_toEnum[ 316 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(316) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 380 ) != m_toEnum.end() )
	{
		vgLogDebug("(380, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(380, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 380 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(380) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 375 ) != m_toEnum.end() )
	{
		vgLogDebug("(375, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(375, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 375 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(375) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 393 ) != m_toEnum.end() )
	{
		vgLogDebug("(393, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(393, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 393 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(393) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 351 ) != m_toEnum.end() )
	{
		vgLogDebug("(351, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(351, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 351 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(351) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 267 ) != m_toEnum.end() )
	{
		vgLogDebug("(267, CameraModelValueType) already in m_toEnum enum registry");
		assert( false && "(267, CameraModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 267 ] = vgd::makeShp( new vgd::node::DepthOfField::CameraModelValueType(267) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 336 ) != m_toEnum.end() )
	{
		vgLogDebug("(336, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(336, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 336 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(336) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 384 ) != m_toEnum.end() )
	{
		vgLogDebug("(384, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(384, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 384 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(384) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 299 ) != m_toEnum.end() )
	{
		vgLogDebug("(299, ShadowMapSizeValueType) already in m_toEnum enum registry");
		assert( false && "(299, ShadowMapSizeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 299 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(299) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 387 ) != m_toEnum.end() )
	{
		vgLogDebug("(387, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(387, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 387 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(387) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 397 ) != m_toEnum.end() )
	{
		vgLogDebug("(397, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(397, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 397 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(397) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 293 ) != m_toEnum.end() )
	{
		vgLogDebug("(293, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(293, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 293 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(293) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 307 ) != m_toEnum.end() )
	{
		vgLogDebug("(307, FormatValueType) already in m_toEnum enum registry");
		assert( false && "(307, FormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 307 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(307) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 337 ) != m_toEnum.end() )
	{
		vgLogDebug("(337, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(337, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 337 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(337) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 309 ) != m_toEnum.end() )
	{
		vgLogDebug("(309, FormatValueType) already in m_toEnum enum registry");
		assert( false && "(309, FormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 309 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(309) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 344 ) != m_toEnum.end() )
	{
		vgLogDebug("(344, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(344, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 344 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(344) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 343 ) != m_toEnum.end() )
	{
		vgLogDebug("(343, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(343, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 343 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(343) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 342 ) != m_toEnum.end() )
	{
		vgLogDebug("(342, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(342, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 342 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(342) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 349 ) != m_toEnum.end() )
	{
		vgLogDebug("(349, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(349, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 349 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(349) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 348 ) != m_toEnum.end() )
	{
		vgLogDebug("(348, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(348, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 348 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(348) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 347 ) != m_toEnum.end() )
	{
		vgLogDebug("(347, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(347, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 347 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(347) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 346 ) != m_toEnum.end() )
	{
		vgLogDebug("(346, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(346, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 346 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(346) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 313 ) != m_toEnum.end() )
	{
		vgLogDebug("(313, TypeValueType) already in m_toEnum enum registry");
		assert( false && "(313, TypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 313 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::TypeValueType(313) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 279 ) != m_toEnum.end() )
	{
		vgLogDebug("(279, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(279, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 279 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(279) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 410 ) != m_toEnum.end() )
	{
		vgLogDebug("(410, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(410, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 410 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(410) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 386 ) != m_toEnum.end() )
	{
		vgLogDebug("(386, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(386, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 386 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(386) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 345 ) != m_toEnum.end() )
	{
		vgLogDebug("(345, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(345, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 345 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(345) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 271 ) != m_toEnum.end() )
	{
		vgLogDebug("(271, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(271, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 271 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(271) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 361 ) != m_toEnum.end() )
	{
		vgLogDebug("(361, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(361, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 361 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(361) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 414 ) != m_toEnum.end() )
	{
		vgLogDebug("(414, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(414, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 414 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(414) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 261 ) != m_toEnum.end() )
	{
		vgLogDebug("(261, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(261, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 261 ] = vgd::makeShp( new vgd::node::Camera::ModeValueType(261) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 256 ) != m_toEnum.end() )
	{
		vgLogDebug("(256, EyeUsagePolicyValueType) already in m_toEnum enum registry");
		assert( false && "(256, EyeUsagePolicyValueType) already in registry" );
	}
	#endif

	m_toEnum[ 256 ] = vgd::makeShp( new vgd::node::Camera::EyeUsagePolicyValueType(256) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 259 ) != m_toEnum.end() )
	{
		vgLogDebug("(259, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(259, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 259 ] = vgd::makeShp( new vgd::node::Camera::ModeValueType(259) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 324 ) != m_toEnum.end() )
	{
		vgLogDebug("(324, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(324, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 324 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(324) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 409 ) != m_toEnum.end() )
	{
		vgLogDebug("(409, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(409, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 409 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(409) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 363 ) != m_toEnum.end() )
	{
		vgLogDebug("(363, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(363, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 363 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(363) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 273 ) != m_toEnum.end() )
	{
		vgLogDebug("(273, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(273, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 273 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(273) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 373 ) != m_toEnum.end() )
	{
		vgLogDebug("(373, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(373, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 373 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(373) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 258 ) != m_toEnum.end() )
	{
		vgLogDebug("(258, EyeUsagePolicyValueType) already in m_toEnum enum registry");
		assert( false && "(258, EyeUsagePolicyValueType) already in registry" );
	}
	#endif

	m_toEnum[ 258 ] = vgd::makeShp( new vgd::node::Camera::EyeUsagePolicyValueType(258) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 295 ) != m_toEnum.end() )
	{
		vgLogDebug("(295, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(295, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 295 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(295) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 322 ) != m_toEnum.end() )
	{
		vgLogDebug("(322, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(322, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 322 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(322) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 288 ) != m_toEnum.end() )
	{
		vgLogDebug("(288, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(288, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 288 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(288) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 355 ) != m_toEnum.end() )
	{
		vgLogDebug("(355, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(355, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 355 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(355) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 354 ) != m_toEnum.end() )
	{
		vgLogDebug("(354, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(354, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 354 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(354) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 353 ) != m_toEnum.end() )
	{
		vgLogDebug("(353, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(353, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 353 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(353) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 360 ) != m_toEnum.end() )
	{
		vgLogDebug("(360, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(360, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 360 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(360) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 359 ) != m_toEnum.end() )
	{
		vgLogDebug("(359, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(359, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 359 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(359) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 358 ) != m_toEnum.end() )
	{
		vgLogDebug("(358, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(358, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 358 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(358) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 357 ) != m_toEnum.end() )
	{
		vgLogDebug("(357, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(357, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 357 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(357) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 319 ) != m_toEnum.end() )
	{
		vgLogDebug("(319, CommandValueType) already in m_toEnum enum registry");
		assert( false && "(319, CommandValueType) already in registry" );
	}
	#endif

	m_toEnum[ 319 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(319) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 321 ) != m_toEnum.end() )
	{
		vgLogDebug("(321, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(321, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 321 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(321) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 284 ) != m_toEnum.end() )
	{
		vgLogDebug("(284, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(284, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 284 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(284) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 272 ) != m_toEnum.end() )
	{
		vgLogDebug("(272, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(272, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 272 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(272) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 303 ) != m_toEnum.end() )
	{
		vgLogDebug("(303, NoiseModelValueType) already in m_toEnum enum registry");
		assert( false && "(303, NoiseModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 303 ] = vgd::makeShp( new vgd::node::Noise::NoiseModelValueType(303) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 325 ) != m_toEnum.end() )
	{
		vgLogDebug("(325, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(325, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 325 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(325) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 394 ) != m_toEnum.end() )
	{
		vgLogDebug("(394, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(394, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 394 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(394) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 264 ) != m_toEnum.end() )
	{
		vgLogDebug("(264, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(264, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 264 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(264) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 304 ) != m_toEnum.end() )
	{
		vgLogDebug("(304, NoiseModelValueType) already in m_toEnum enum registry");
		assert( false && "(304, NoiseModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 304 ] = vgd::makeShp( new vgd::node::Noise::NoiseModelValueType(304) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 260 ) != m_toEnum.end() )
	{
		vgLogDebug("(260, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(260, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 260 ] = vgd::makeShp( new vgd::node::Camera::ModeValueType(260) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 333 ) != m_toEnum.end() )
	{
		vgLogDebug("(333, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(333, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 333 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(333) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 314 ) != m_toEnum.end() )
	{
		vgLogDebug("(314, TypeValueType) already in m_toEnum enum registry");
		assert( false && "(314, TypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 314 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::TypeValueType(314) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 352 ) != m_toEnum.end() )
	{
		vgLogDebug("(352, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(352, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 352 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(352) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 308 ) != m_toEnum.end() )
	{
		vgLogDebug("(308, FormatValueType) already in m_toEnum enum registry");
		assert( false && "(308, FormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 308 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(308) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 320 ) != m_toEnum.end() )
	{
		vgLogDebug("(320, CommandValueType) already in m_toEnum enum registry");
		assert( false && "(320, CommandValueType) already in registry" );
	}
	#endif

	m_toEnum[ 320 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(320) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 405 ) != m_toEnum.end() )
	{
		vgLogDebug("(405, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(405, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 405 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(405) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 296 ) != m_toEnum.end() )
	{
		vgLogDebug("(296, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(296, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 296 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(296) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 335 ) != m_toEnum.end() )
	{
		vgLogDebug("(335, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(335, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 335 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(335) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 302 ) != m_toEnum.end() )
	{
		vgLogDebug("(302, ShadowFilteringValueType) already in m_toEnum enum registry");
		assert( false && "(302, ShadowFilteringValueType) already in registry" );
	}
	#endif

	m_toEnum[ 302 ] = vgd::makeShp( new vgd::node::LightModel::ShadowFilteringValueType(302) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 379 ) != m_toEnum.end() )
	{
		vgLogDebug("(379, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(379, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 379 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(379) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 378 ) != m_toEnum.end() )
	{
		vgLogDebug("(378, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(378, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 378 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(378) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 350 ) != m_toEnum.end() )
	{
		vgLogDebug("(350, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(350, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 350 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(350) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 376 ) != m_toEnum.end() )
	{
		vgLogDebug("(376, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(376, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 376 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(376) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 383 ) != m_toEnum.end() )
	{
		vgLogDebug("(383, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(383, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 383 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(383) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 382 ) != m_toEnum.end() )
	{
		vgLogDebug("(382, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(382, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 382 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(382) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 381 ) != m_toEnum.end() )
	{
		vgLogDebug("(381, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(381, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 381 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(381) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(287, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(287) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 318 ) != m_toEnum.end() )
	{
		vgLogDebug("(318, CommandValueType) already in m_toEnum enum registry");
		assert( false && "(318, CommandValueType) already in registry" );
	}
	#endif

	m_toEnum[ 318 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(318) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 364 ) != m_toEnum.end() )
	{
		vgLogDebug("(364, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(364, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 364 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(364) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 396 ) != m_toEnum.end() )
	{
		vgLogDebug("(396, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(396, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 396 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(396) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 366 ) != m_toEnum.end() )
	{
		vgLogDebug("(366, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(366, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 366 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(366) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 330 ) != m_toEnum.end() )
	{
		vgLogDebug("(330, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(330, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 330 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(330) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 412 ) != m_toEnum.end() )
	{
		vgLogDebug("(412, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(412, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 412 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(412) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 326 ) != m_toEnum.end() )
	{
		vgLogDebug("(326, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(326, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 326 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(326) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 323 ) != m_toEnum.end() )
	{
		vgLogDebug("(323, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(323, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 323 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(323) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(286, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(286) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 411 ) != m_toEnum.end() )
	{
		vgLogDebug("(411, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(411, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 411 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(411) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 262 ) != m_toEnum.end() )
	{
		vgLogDebug("(262, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(262, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 262 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(262) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 270 ) != m_toEnum.end() )
	{
		vgLogDebug("(270, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(270, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 270 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(270) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 398 ) != m_toEnum.end() )
	{
		vgLogDebug("(398, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(398, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 398 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(398) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 263 ) != m_toEnum.end() )
	{
		vgLogDebug("(263, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(263, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 263 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(263) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(290, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(290) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 291 ) != m_toEnum.end() )
	{
		vgLogDebug("(291, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(291, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 291 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(291) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 283 ) != m_toEnum.end() )
	{
		vgLogDebug("(283, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(283, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 283 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(283) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 332 ) != m_toEnum.end() )
	{
		vgLogDebug("(332, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(332, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 332 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(332) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 390 ) != m_toEnum.end() )
	{
		vgLogDebug("(390, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(390, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 390 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(390) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 300 ) != m_toEnum.end() )
	{
		vgLogDebug("(300, ShadowMapSizeValueType) already in m_toEnum enum registry");
		assert( false && "(300, ShadowMapSizeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 300 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(300) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 331 ) != m_toEnum.end() )
	{
		vgLogDebug("(331, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(331, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 331 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(331) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 341 ) != m_toEnum.end() )
	{
		vgLogDebug("(341, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(341, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 341 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(341) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 317 ) != m_toEnum.end() )
	{
		vgLogDebug("(317, CommandValueType) already in m_toEnum enum registry");
		assert( false && "(317, CommandValueType) already in registry" );
	}
	#endif

	m_toEnum[ 317 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(317) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 392 ) != m_toEnum.end() )
	{
		vgLogDebug("(392, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(392, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 392 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(392) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 292 ) != m_toEnum.end() )
	{
		vgLogDebug("(292, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(292, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 292 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(292) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 265 ) != m_toEnum.end() )
	{
		vgLogDebug("(265, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(265, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 265 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(265) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 365 ) != m_toEnum.end() )
	{
		vgLogDebug("(365, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(365, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 365 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(365) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 281 ) != m_toEnum.end() )
	{
		vgLogDebug("(281, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(281, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 281 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(281) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 367 ) != m_toEnum.end() )
	{
		vgLogDebug("(367, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(367, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 367 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(367) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 362 ) != m_toEnum.end() )
	{
		vgLogDebug("(362, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(362, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 362 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(362) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 369 ) != m_toEnum.end() )
	{
		vgLogDebug("(369, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(369, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 369 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(369) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 368 ) != m_toEnum.end() )
	{
		vgLogDebug("(368, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(368, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 368 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(368) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 371 ) != m_toEnum.end() )
	{
		vgLogDebug("(371, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(371, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 371 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(371) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 370 ) != m_toEnum.end() )
	{
		vgLogDebug("(370, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(370, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 370 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(370) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 340 ) != m_toEnum.end() )
	{
		vgLogDebug("(340, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(340, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 340 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(340) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 305 ) != m_toEnum.end() )
	{
		vgLogDebug("(305, SizeSemanticValueType) already in m_toEnum enum registry");
		assert( false && "(305, SizeSemanticValueType) already in registry" );
	}
	#endif

	m_toEnum[ 305 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::SizeSemanticValueType(305) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(280, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(280) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 374 ) != m_toEnum.end() )
	{
		vgLogDebug("(374, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(374, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 374 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(374) );
	
}



} // namespace node

} // namespace vgd
