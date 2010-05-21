// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/EnumRegistry.hpp"

#include <vgDebug/convenience.hpp>
#include <vgd/Shp.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/OutputBuffers.hpp>
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
	if ( m_toString.find( 305 ) != m_toString.end() )
	{
		vgLogDebug("(305, DOF) already in m_toString enum registry");
		assert( false && "(305, DOF) already in registry" );
	}
	#endif

	m_toString[ 305 ] = std::string("DOF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 295 ) != m_toString.end() )
	{
		vgLogDebug("(295, BLOOM_VERT) already in m_toString enum registry");
		assert( false && "(295, BLOOM_VERT) already in registry" );
	}
	#endif

	m_toString[ 295 ] = std::string("BLOOM_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 304 ) != m_toString.end() )
	{
		vgLogDebug("(304, COMBINE3_AND_SCALE) already in m_toString enum registry");
		assert( false && "(304, COMBINE3_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 304 ] = std::string("COMBINE3_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 366 ) != m_toString.end() )
	{
		vgLogDebug("(366, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(366, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 366 ] = std::string("MIN_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 301 ) != m_toString.end() )
	{
		vgLogDebug("(301, ADD) already in m_toString enum registry");
		assert( false && "(301, ADD) already in registry" );
	}
	#endif

	m_toString[ 301 ] = std::string("ADD");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 358 ) != m_toString.end() )
	{
		vgLogDebug("(358, WRAP_T) already in m_toString enum registry");
		assert( false && "(358, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 358 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 362 ) != m_toString.end() )
	{
		vgLogDebug("(362, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(362, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 362 ] = std::string("CLAMP_TO_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 284 ) != m_toString.end() )
	{
		vgLogDebug("(284, VERY_HIGH) already in m_toString enum registry");
		assert( false && "(284, VERY_HIGH) already in registry" );
	}
	#endif

	m_toString[ 284 ] = std::string("VERY_HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 357 ) != m_toString.end() )
	{
		vgLogDebug("(357, WRAP_S) already in m_toString enum registry");
		assert( false && "(357, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 357 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 359 ) != m_toString.end() )
	{
		vgLogDebug("(359, WRAP_R) already in m_toString enum registry");
		assert( false && "(359, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 359 ] = std::string("WRAP_R");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 261 ) != m_toString.end() )
	{
		vgLogDebug("(261, CW) already in m_toString enum registry");
		assert( false && "(261, CW) already in registry" );
	}
	#endif

	m_toString[ 261 ] = std::string("CW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 368 ) != m_toString.end() )
	{
		vgLogDebug("(368, NEAREST) already in m_toString enum registry");
		assert( false && "(368, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 368 ] = std::string("NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 321 ) != m_toString.end() )
	{
		vgLogDebug("(321, INPUT1_ORIGINAL_DEPTH1) already in m_toString enum registry");
		assert( false && "(321, INPUT1_ORIGINAL_DEPTH1) already in registry" );
	}
	#endif

	m_toString[ 321 ] = std::string("INPUT1_ORIGINAL_DEPTH1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 319 ) != m_toString.end() )
	{
		vgLogDebug("(319, INPUT1_ORIGINAL_DEPTH0) already in m_toString enum registry");
		assert( false && "(319, INPUT1_ORIGINAL_DEPTH0) already in registry" );
	}
	#endif

	m_toString[ 319 ] = std::string("INPUT1_ORIGINAL_DEPTH0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 323 ) != m_toString.end() )
	{
		vgLogDebug("(323, INPUT1_ORIGINAL_DEPTH2) already in m_toString enum registry");
		assert( false && "(323, INPUT1_ORIGINAL_DEPTH2) already in registry" );
	}
	#endif

	m_toString[ 323 ] = std::string("INPUT1_ORIGINAL_DEPTH2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 272 ) != m_toString.end() )
	{
		vgLogDebug("(272, SHADOW_MAPPING) already in m_toString enum registry");
		assert( false && "(272, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toString[ 272 ] = std::string("SHADOW_MAPPING");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 320 ) != m_toString.end() )
	{
		vgLogDebug("(320, INPUT1_ORIGINAL_COLOR1) already in m_toString enum registry");
		assert( false && "(320, INPUT1_ORIGINAL_COLOR1) already in registry" );
	}
	#endif

	m_toString[ 320 ] = std::string("INPUT1_ORIGINAL_COLOR1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 335 ) != m_toString.end() )
	{
		vgLogDebug("(335, INPUT2_ORIGINAL_NORMAL) already in m_toString enum registry");
		assert( false && "(335, INPUT2_ORIGINAL_NORMAL) already in registry" );
	}
	#endif

	m_toString[ 335 ] = std::string("INPUT2_ORIGINAL_NORMAL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 260 ) != m_toString.end() )
	{
		vgLogDebug("(260, CCW) already in m_toString enum registry");
		assert( false && "(260, CCW) already in registry" );
	}
	#endif

	m_toString[ 260 ] = std::string("CCW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 326 ) != m_toString.end() )
	{
		vgLogDebug("(326, INPUT1_PREVIOUS_COLOR0) already in m_toString enum registry");
		assert( false && "(326, INPUT1_PREVIOUS_COLOR0) already in registry" );
	}
	#endif

	m_toString[ 326 ] = std::string("INPUT1_PREVIOUS_COLOR0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 360 ) != m_toString.end() )
	{
		vgLogDebug("(360, REPEAT) already in m_toString enum registry");
		assert( false && "(360, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 360 ] = std::string("REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 353 ) != m_toString.end() )
	{
		vgLogDebug("(353, LUMINANCE_16F) already in m_toString enum registry");
		assert( false && "(353, LUMINANCE_16F) already in registry" );
	}
	#endif

	m_toString[ 353 ] = std::string("LUMINANCE_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 325 ) != m_toString.end() )
	{
		vgLogDebug("(325, INPUT1_ORIGINAL_POSITION) already in m_toString enum registry");
		assert( false && "(325, INPUT1_ORIGINAL_POSITION) already in registry" );
	}
	#endif

	m_toString[ 325 ] = std::string("INPUT1_ORIGINAL_POSITION");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 303 ) != m_toString.end() )
	{
		vgLogDebug("(303, COMBINE2_AND_SCALE) already in m_toString enum registry");
		assert( false && "(303, COMBINE2_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 303 ] = std::string("COMBINE2_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 283 ) != m_toString.end() )
	{
		vgLogDebug("(283, HIGH) already in m_toString enum registry");
		assert( false && "(283, HIGH) already in registry" );
	}
	#endif

	m_toString[ 283 ] = std::string("HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 293 ) != m_toString.end() )
	{
		vgLogDebug("(293, BLUR_VERT) already in m_toString enum registry");
		assert( false && "(293, BLUR_VERT) already in registry" );
	}
	#endif

	m_toString[ 293 ] = std::string("BLUR_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 361 ) != m_toString.end() )
	{
		vgLogDebug("(361, CLAMP) already in m_toString enum registry");
		assert( false && "(361, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 361 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 365 ) != m_toString.end() )
	{
		vgLogDebug("(365, ONCE) already in m_toString enum registry");
		assert( false && "(365, ONCE) already in registry" );
	}
	#endif

	m_toString[ 365 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 371 ) != m_toString.end() )
	{
		vgLogDebug("(371, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(371, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 371 ] = std::string("LINEAR_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 269 ) != m_toString.end() )
	{
		vgLogDebug("(269, AT_INFINITY) already in m_toString enum registry");
		assert( false && "(269, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 269 ] = std::string("AT_INFINITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 346 ) != m_toString.end() )
	{
		vgLogDebug("(346, DEPTH_COMPONENT_24) already in m_toString enum registry");
		assert( false && "(346, DEPTH_COMPONENT_24) already in registry" );
	}
	#endif

	m_toString[ 346 ] = std::string("DEPTH_COMPONENT_24");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 343 ) != m_toString.end() )
	{
		vgLogDebug("(343, SHADOW) already in m_toString enum registry");
		assert( false && "(343, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 343 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, SHADOW_MAPPING_32UM) already in m_toString enum registry");
		assert( false && "(278, SHADOW_MAPPING_32UM) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("SHADOW_MAPPING_32UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 364 ) != m_toString.end() )
	{
		vgLogDebug("(364, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(364, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 364 ] = std::string("MIRRORED_REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 324 ) != m_toString.end() )
	{
		vgLogDebug("(324, INPUT1_ORIGINAL_NORMAL) already in m_toString enum registry");
		assert( false && "(324, INPUT1_ORIGINAL_NORMAL) already in registry" );
	}
	#endif

	m_toString[ 324 ] = std::string("INPUT1_ORIGINAL_NORMAL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 349 ) != m_toString.end() )
	{
		vgLogDebug("(349, RGB_16F) already in m_toString enum registry");
		assert( false && "(349, RGB_16F) already in registry" );
	}
	#endif

	m_toString[ 349 ] = std::string("RGB_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 355 ) != m_toString.end() )
	{
		vgLogDebug("(355, LUMINANCE_ALPHA_16F) already in m_toString enum registry");
		assert( false && "(355, LUMINANCE_ALPHA_16F) already in registry" );
	}
	#endif

	m_toString[ 355 ] = std::string("LUMINANCE_ALPHA_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 340 ) != m_toString.end() )
	{
		vgLogDebug("(340, OUTPUT_TMP0) already in m_toString enum registry");
		assert( false && "(340, OUTPUT_TMP0) already in registry" );
	}
	#endif

	m_toString[ 340 ] = std::string("OUTPUT_TMP0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 341 ) != m_toString.end() )
	{
		vgLogDebug("(341, OUTPUT_TMP1) already in m_toString enum registry");
		assert( false && "(341, OUTPUT_TMP1) already in registry" );
	}
	#endif

	m_toString[ 341 ] = std::string("OUTPUT_TMP1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 351 ) != m_toString.end() )
	{
		vgLogDebug("(351, RGBA_16F) already in m_toString enum registry");
		assert( false && "(351, RGBA_16F) already in registry" );
	}
	#endif

	m_toString[ 351 ] = std::string("RGBA_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 316 ) != m_toString.end() )
	{
		vgLogDebug("(316, PREVIOUS_COLOR1) already in m_toString enum registry");
		assert( false && "(316, PREVIOUS_COLOR1) already in registry" );
	}
	#endif

	m_toString[ 316 ] = std::string("PREVIOUS_COLOR1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 315 ) != m_toString.end() )
	{
		vgLogDebug("(315, PREVIOUS_COLOR0) already in m_toString enum registry");
		assert( false && "(315, PREVIOUS_COLOR0) already in registry" );
	}
	#endif

	m_toString[ 315 ] = std::string("PREVIOUS_COLOR0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 302 ) != m_toString.end() )
	{
		vgLogDebug("(302, MIX_AND_SCALE) already in m_toString enum registry");
		assert( false && "(302, MIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 302 ] = std::string("MIX_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 342 ) != m_toString.end() )
	{
		vgLogDebug("(342, IMAGE) already in m_toString enum registry");
		assert( false && "(342, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 342 ] = std::string("IMAGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 345 ) != m_toString.end() )
	{
		vgLogDebug("(345, DEPTH_COMPONENT_16) already in m_toString enum registry");
		assert( false && "(345, DEPTH_COMPONENT_16) already in registry" );
	}
	#endif

	m_toString[ 345 ] = std::string("DEPTH_COMPONENT_16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 299 ) != m_toString.end() )
	{
		vgLogDebug("(299, OVER_AND_MIX) already in m_toString enum registry");
		assert( false && "(299, OVER_AND_MIX) already in registry" );
	}
	#endif

	m_toString[ 299 ] = std::string("OVER_AND_MIX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 277 ) != m_toString.end() )
	{
		vgLogDebug("(277, SHADOW_MAPPING_32U) already in m_toString enum registry");
		assert( false && "(277, SHADOW_MAPPING_32U) already in registry" );
	}
	#endif

	m_toString[ 277 ] = std::string("SHADOW_MAPPING_32U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 372 ) != m_toString.end() )
	{
		vgLogDebug("(372, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(372, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 372 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, LIGHTING_OFF) already in m_toString enum registry");
		assert( false && "(266, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("LIGHTING_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 344 ) != m_toString.end() )
	{
		vgLogDebug("(344, AUTOMATIC) already in m_toString enum registry");
		assert( false && "(344, AUTOMATIC) already in registry" );
	}
	#endif

	m_toString[ 344 ] = std::string("AUTOMATIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, INT24) already in m_toString enum registry");
		assert( false && "(263, INT24) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("INT24");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 331 ) != m_toString.end() )
	{
		vgLogDebug("(331, INPUT2_ORIGINAL_COLOR1) already in m_toString enum registry");
		assert( false && "(331, INPUT2_ORIGINAL_COLOR1) already in registry" );
	}
	#endif

	m_toString[ 331 ] = std::string("INPUT2_ORIGINAL_COLOR1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 329 ) != m_toString.end() )
	{
		vgLogDebug("(329, INPUT2_ORIGINAL_COLOR0) already in m_toString enum registry");
		assert( false && "(329, INPUT2_ORIGINAL_COLOR0) already in registry" );
	}
	#endif

	m_toString[ 329 ] = std::string("INPUT2_ORIGINAL_COLOR0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 333 ) != m_toString.end() )
	{
		vgLogDebug("(333, INPUT2_ORIGINAL_COLOR2) already in m_toString enum registry");
		assert( false && "(333, INPUT2_ORIGINAL_COLOR2) already in registry" );
	}
	#endif

	m_toString[ 333 ] = std::string("INPUT2_ORIGINAL_COLOR2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 281 ) != m_toString.end() )
	{
		vgLogDebug("(281, LOW) already in m_toString enum registry");
		assert( false && "(281, LOW) already in registry" );
	}
	#endif

	m_toString[ 281 ] = std::string("LOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, COLOR_INVERSE) already in m_toString enum registry");
		assert( false && "(290, COLOR_INVERSE) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("COLOR_INVERSE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 310 ) != m_toString.end() )
	{
		vgLogDebug("(310, ORIGINAL_DEPTH1) already in m_toString enum registry");
		assert( false && "(310, ORIGINAL_DEPTH1) already in registry" );
	}
	#endif

	m_toString[ 310 ] = std::string("ORIGINAL_DEPTH1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 367 ) != m_toString.end() )
	{
		vgLogDebug("(367, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(367, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 367 ] = std::string("MAG_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 314 ) != m_toString.end() )
	{
		vgLogDebug("(314, ORIGINAL_POSITION) already in m_toString enum registry");
		assert( false && "(314, ORIGINAL_POSITION) already in registry" );
	}
	#endif

	m_toString[ 314 ] = std::string("ORIGINAL_POSITION");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 328 ) != m_toString.end() )
	{
		vgLogDebug("(328, INPUT1_NONE) already in m_toString enum registry");
		assert( false && "(328, INPUT1_NONE) already in registry" );
	}
	#endif

	m_toString[ 328 ] = std::string("INPUT1_NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, FLOAT32) already in m_toString enum registry");
		assert( false && "(265, FLOAT32) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("FLOAT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 279 ) != m_toString.end() )
	{
		vgLogDebug("(279, SHADOW_MAPPING_64U) already in m_toString enum registry");
		assert( false && "(279, SHADOW_MAPPING_64U) already in registry" );
	}
	#endif

	m_toString[ 279 ] = std::string("SHADOW_MAPPING_64U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, COLOR_TO_MONOCHROME) already in m_toString enum registry");
		assert( false && "(288, COLOR_TO_MONOCHROME) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("COLOR_TO_MONOCHROME");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 274 ) != m_toString.end() )
	{
		vgLogDebug("(274, SHADOW_MAPPING_4DM) already in m_toString enum registry");
		assert( false && "(274, SHADOW_MAPPING_4DM) already in registry" );
	}
	#endif

	m_toString[ 274 ] = std::string("SHADOW_MAPPING_4DM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 271 ) != m_toString.end() )
	{
		vgLogDebug("(271, SHADOW_OFF) already in m_toString enum registry");
		assert( false && "(271, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toString[ 271 ] = std::string("SHADOW_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, INT32) already in m_toString enum registry");
		assert( false && "(264, INT32) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("INT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, SCALE_AND_BIAS) already in m_toString enum registry");
		assert( false && "(291, SCALE_AND_BIAS) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("SCALE_AND_BIAS");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 352 ) != m_toString.end() )
	{
		vgLogDebug("(352, RGBA_32F) already in m_toString enum registry");
		assert( false && "(352, RGBA_32F) already in registry" );
	}
	#endif

	m_toString[ 352 ] = std::string("RGBA_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 258 ) != m_toString.end() )
	{
		vgLogDebug("(258, FRONT) already in m_toString enum registry");
		assert( false && "(258, FRONT) already in registry" );
	}
	#endif

	m_toString[ 258 ] = std::string("FRONT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 300 ) != m_toString.end() )
	{
		vgLogDebug("(300, OVER) already in m_toString enum registry");
		assert( false && "(300, OVER) already in registry" );
	}
	#endif

	m_toString[ 300 ] = std::string("OVER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 336 ) != m_toString.end() )
	{
		vgLogDebug("(336, INPUT2_ORIGINAL_POSITION) already in m_toString enum registry");
		assert( false && "(336, INPUT2_ORIGINAL_POSITION) already in registry" );
	}
	#endif

	m_toString[ 336 ] = std::string("INPUT2_ORIGINAL_POSITION");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 317 ) != m_toString.end() )
	{
		vgLogDebug("(317, NONE) already in m_toString enum registry");
		assert( false && "(317, NONE) already in registry" );
	}
	#endif

	m_toString[ 317 ] = std::string("NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 363 ) != m_toString.end() )
	{
		vgLogDebug("(363, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(363, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 363 ] = std::string("CLAMP_TO_BORDER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, SHADOW_MAPPING_64UM) already in m_toString enum registry");
		assert( false && "(280, SHADOW_MAPPING_64UM) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("SHADOW_MAPPING_64UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 294 ) != m_toString.end() )
	{
		vgLogDebug("(294, BLOOM_HORIZ) already in m_toString enum registry");
		assert( false && "(294, BLOOM_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 294 ] = std::string("BLOOM_HORIZ");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 338 ) != m_toString.end() )
	{
		vgLogDebug("(338, INPUT2_PREVIOUS_COLOR1) already in m_toString enum registry");
		assert( false && "(338, INPUT2_PREVIOUS_COLOR1) already in registry" );
	}
	#endif

	m_toString[ 338 ] = std::string("INPUT2_PREVIOUS_COLOR1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 337 ) != m_toString.end() )
	{
		vgLogDebug("(337, INPUT2_PREVIOUS_COLOR0) already in m_toString enum registry");
		assert( false && "(337, INPUT2_PREVIOUS_COLOR0) already in registry" );
	}
	#endif

	m_toString[ 337 ] = std::string("INPUT2_PREVIOUS_COLOR0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 334 ) != m_toString.end() )
	{
		vgLogDebug("(334, INPUT2_ORIGINAL_DEPTH2) already in m_toString enum registry");
		assert( false && "(334, INPUT2_ORIGINAL_DEPTH2) already in registry" );
	}
	#endif

	m_toString[ 334 ] = std::string("INPUT2_ORIGINAL_DEPTH2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 332 ) != m_toString.end() )
	{
		vgLogDebug("(332, INPUT2_ORIGINAL_DEPTH1) already in m_toString enum registry");
		assert( false && "(332, INPUT2_ORIGINAL_DEPTH1) already in registry" );
	}
	#endif

	m_toString[ 332 ] = std::string("INPUT2_ORIGINAL_DEPTH1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 330 ) != m_toString.end() )
	{
		vgLogDebug("(330, INPUT2_ORIGINAL_DEPTH0) already in m_toString enum registry");
		assert( false && "(330, INPUT2_ORIGINAL_DEPTH0) already in registry" );
	}
	#endif

	m_toString[ 330 ] = std::string("INPUT2_ORIGINAL_DEPTH0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 354 ) != m_toString.end() )
	{
		vgLogDebug("(354, LUMINANCE_32F) already in m_toString enum registry");
		assert( false && "(354, LUMINANCE_32F) already in registry" );
	}
	#endif

	m_toString[ 354 ] = std::string("LUMINANCE_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 282 ) != m_toString.end() )
	{
		vgLogDebug("(282, MEDIUM) already in m_toString enum registry");
		assert( false && "(282, MEDIUM) already in registry" );
	}
	#endif

	m_toString[ 282 ] = std::string("MEDIUM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 296 ) != m_toString.end() )
	{
		vgLogDebug("(296, COLOR_EDGE_DETECT) already in m_toString enum registry");
		assert( false && "(296, COLOR_EDGE_DETECT) already in registry" );
	}
	#endif

	m_toString[ 296 ] = std::string("COLOR_EDGE_DETECT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, BUFFERS2) already in m_toString enum registry");
		assert( false && "(287, BUFFERS2) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("BUFFERS2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, BUFFERS1) already in m_toString enum registry");
		assert( false && "(286, BUFFERS1) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("BUFFERS1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, BUFFERS0) already in m_toString enum registry");
		assert( false && "(285, BUFFERS0) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("BUFFERS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 347 ) != m_toString.end() )
	{
		vgLogDebug("(347, DEPTH_COMPONENT_32) already in m_toString enum registry");
		assert( false && "(347, DEPTH_COMPONENT_32) already in registry" );
	}
	#endif

	m_toString[ 347 ] = std::string("DEPTH_COMPONENT_32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 292 ) != m_toString.end() )
	{
		vgLogDebug("(292, BLUR_HORIZ) already in m_toString enum registry");
		assert( false && "(292, BLUR_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 292 ] = std::string("BLUR_HORIZ");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, COLOR_TO_SEPIA) already in m_toString enum registry");
		assert( false && "(289, COLOR_TO_SEPIA) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("COLOR_TO_SEPIA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 273 ) != m_toString.end() )
	{
		vgLogDebug("(273, SHADOW_MAPPING_4U) already in m_toString enum registry");
		assert( false && "(273, SHADOW_MAPPING_4U) already in registry" );
	}
	#endif

	m_toString[ 273 ] = std::string("SHADOW_MAPPING_4U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 369 ) != m_toString.end() )
	{
		vgLogDebug("(369, LINEAR) already in m_toString enum registry");
		assert( false && "(369, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 369 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 256 ) != m_toString.end() )
	{
		vgLogDebug("(256, DISABLED) already in m_toString enum registry");
		assert( false && "(256, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 256 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 311 ) != m_toString.end() )
	{
		vgLogDebug("(311, ORIGINAL_COLOR2) already in m_toString enum registry");
		assert( false && "(311, ORIGINAL_COLOR2) already in registry" );
	}
	#endif

	m_toString[ 311 ] = std::string("ORIGINAL_COLOR2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 306 ) != m_toString.end() )
	{
		vgLogDebug("(306, NO_FILTER) already in m_toString enum registry");
		assert( false && "(306, NO_FILTER) already in registry" );
	}
	#endif

	m_toString[ 306 ] = std::string("NO_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 307 ) != m_toString.end() )
	{
		vgLogDebug("(307, ORIGINAL_COLOR0) already in m_toString enum registry");
		assert( false && "(307, ORIGINAL_COLOR0) already in registry" );
	}
	#endif

	m_toString[ 307 ] = std::string("ORIGINAL_COLOR0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, INT16) already in m_toString enum registry");
		assert( false && "(262, INT16) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("INT16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 356 ) != m_toString.end() )
	{
		vgLogDebug("(356, LUMINANCE_ALPHA_32F) already in m_toString enum registry");
		assert( false && "(356, LUMINANCE_ALPHA_32F) already in registry" );
	}
	#endif

	m_toString[ 356 ] = std::string("LUMINANCE_ALPHA_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 257 ) != m_toString.end() )
	{
		vgLogDebug("(257, BACK) already in m_toString enum registry");
		assert( false && "(257, BACK) already in registry" );
	}
	#endif

	m_toString[ 257 ] = std::string("BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 313 ) != m_toString.end() )
	{
		vgLogDebug("(313, ORIGINAL_NORMAL) already in m_toString enum registry");
		assert( false && "(313, ORIGINAL_NORMAL) already in registry" );
	}
	#endif

	m_toString[ 313 ] = std::string("ORIGINAL_NORMAL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 275 ) != m_toString.end() )
	{
		vgLogDebug("(275, SHADOW_MAPPING_16U) already in m_toString enum registry");
		assert( false && "(275, SHADOW_MAPPING_16U) already in registry" );
	}
	#endif

	m_toString[ 275 ] = std::string("SHADOW_MAPPING_16U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 270 ) != m_toString.end() )
	{
		vgLogDebug("(270, AT_EYE) already in m_toString enum registry");
		assert( false && "(270, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 270 ] = std::string("AT_EYE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 298 ) != m_toString.end() )
	{
		vgLogDebug("(298, UP_FILTER4) already in m_toString enum registry");
		assert( false && "(298, UP_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 298 ] = std::string("UP_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 348 ) != m_toString.end() )
	{
		vgLogDebug("(348, DEPTH_COMPONENT_32F) already in m_toString enum registry");
		assert( false && "(348, DEPTH_COMPONENT_32F) already in registry" );
	}
	#endif

	m_toString[ 348 ] = std::string("DEPTH_COMPONENT_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 297 ) != m_toString.end() )
	{
		vgLogDebug("(297, DOWN_FILTER4) already in m_toString enum registry");
		assert( false && "(297, DOWN_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 297 ] = std::string("DOWN_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 308 ) != m_toString.end() )
	{
		vgLogDebug("(308, ORIGINAL_DEPTH0) already in m_toString enum registry");
		assert( false && "(308, ORIGINAL_DEPTH0) already in registry" );
	}
	#endif

	m_toString[ 308 ] = std::string("ORIGINAL_DEPTH0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 373 ) != m_toString.end() )
	{
		vgLogDebug("(373, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(373, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 373 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 312 ) != m_toString.end() )
	{
		vgLogDebug("(312, ORIGINAL_DEPTH2) already in m_toString enum registry");
		assert( false && "(312, ORIGINAL_DEPTH2) already in registry" );
	}
	#endif

	m_toString[ 312 ] = std::string("ORIGINAL_DEPTH2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 350 ) != m_toString.end() )
	{
		vgLogDebug("(350, RGB_32F) already in m_toString enum registry");
		assert( false && "(350, RGB_32F) already in registry" );
	}
	#endif

	m_toString[ 350 ] = std::string("RGB_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 327 ) != m_toString.end() )
	{
		vgLogDebug("(327, INPUT1_PREVIOUS_COLOR1) already in m_toString enum registry");
		assert( false && "(327, INPUT1_PREVIOUS_COLOR1) already in registry" );
	}
	#endif

	m_toString[ 327 ] = std::string("INPUT1_PREVIOUS_COLOR1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 276 ) != m_toString.end() )
	{
		vgLogDebug("(276, SHADOW_MAPPING_16UM) already in m_toString enum registry");
		assert( false && "(276, SHADOW_MAPPING_16UM) already in registry" );
	}
	#endif

	m_toString[ 276 ] = std::string("SHADOW_MAPPING_16UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 259 ) != m_toString.end() )
	{
		vgLogDebug("(259, FRONT_AND_BACK) already in m_toString enum registry");
		assert( false && "(259, FRONT_AND_BACK) already in registry" );
	}
	#endif

	m_toString[ 259 ] = std::string("FRONT_AND_BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 268 ) != m_toString.end() )
	{
		vgLogDebug("(268, STANDARD_PER_PIXEL) already in m_toString enum registry");
		assert( false && "(268, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toString[ 268 ] = std::string("STANDARD_PER_PIXEL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 370 ) != m_toString.end() )
	{
		vgLogDebug("(370, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(370, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 370 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 322 ) != m_toString.end() )
	{
		vgLogDebug("(322, INPUT1_ORIGINAL_COLOR2) already in m_toString enum registry");
		assert( false && "(322, INPUT1_ORIGINAL_COLOR2) already in registry" );
	}
	#endif

	m_toString[ 322 ] = std::string("INPUT1_ORIGINAL_COLOR2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 309 ) != m_toString.end() )
	{
		vgLogDebug("(309, ORIGINAL_COLOR1) already in m_toString enum registry");
		assert( false && "(309, ORIGINAL_COLOR1) already in registry" );
	}
	#endif

	m_toString[ 309 ] = std::string("ORIGINAL_COLOR1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 318 ) != m_toString.end() )
	{
		vgLogDebug("(318, INPUT1_ORIGINAL_COLOR0) already in m_toString enum registry");
		assert( false && "(318, INPUT1_ORIGINAL_COLOR0) already in registry" );
	}
	#endif

	m_toString[ 318 ] = std::string("INPUT1_ORIGINAL_COLOR0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, STANDARD_PER_VERTEX) already in m_toString enum registry");
		assert( false && "(267, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("STANDARD_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 339 ) != m_toString.end() )
	{
		vgLogDebug("(339, INPUT2_NONE) already in m_toString enum registry");
		assert( false && "(339, INPUT2_NONE) already in registry" );
	}
	#endif

	m_toString[ 339 ] = std::string("INPUT2_NONE");

	// Initializes m_toEnum map

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 305 ) != m_toEnum.end() )
	{
		vgLogDebug("(305, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(305, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 305 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(305) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 295 ) != m_toEnum.end() )
	{
		vgLogDebug("(295, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(295, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 295 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(295) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 304 ) != m_toEnum.end() )
	{
		vgLogDebug("(304, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(304, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 304 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(304) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 366 ) != m_toEnum.end() )
	{
		vgLogDebug("(366, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(366, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 366 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(366) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 301 ) != m_toEnum.end() )
	{
		vgLogDebug("(301, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(301, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 301 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(301) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 358 ) != m_toEnum.end() )
	{
		vgLogDebug("(358, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(358, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 358 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(358) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 362 ) != m_toEnum.end() )
	{
		vgLogDebug("(362, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(362, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 362 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(362) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 284 ) != m_toEnum.end() )
	{
		vgLogDebug("(284, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(284, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 284 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(284) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 357 ) != m_toEnum.end() )
	{
		vgLogDebug("(357, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(357, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 357 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(357) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 359 ) != m_toEnum.end() )
	{
		vgLogDebug("(359, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(359, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 359 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(359) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 261 ) != m_toEnum.end() )
	{
		vgLogDebug("(261, OrientationValueType) already in m_toEnum enum registry");
		assert( false && "(261, OrientationValueType) already in registry" );
	}
	#endif

	m_toEnum[ 261 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(261) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 368 ) != m_toEnum.end() )
	{
		vgLogDebug("(368, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(368, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 368 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(368) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 321 ) != m_toEnum.end() )
	{
		vgLogDebug("(321, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(321, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 321 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(321) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 319 ) != m_toEnum.end() )
	{
		vgLogDebug("(319, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(319, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 319 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(319) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 323 ) != m_toEnum.end() )
	{
		vgLogDebug("(323, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(323, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 323 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(323) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 272 ) != m_toEnum.end() )
	{
		vgLogDebug("(272, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(272, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 272 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(272) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 320 ) != m_toEnum.end() )
	{
		vgLogDebug("(320, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(320, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 320 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(320) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 335 ) != m_toEnum.end() )
	{
		vgLogDebug("(335, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(335, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 335 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(335) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 260 ) != m_toEnum.end() )
	{
		vgLogDebug("(260, OrientationValueType) already in m_toEnum enum registry");
		assert( false && "(260, OrientationValueType) already in registry" );
	}
	#endif

	m_toEnum[ 260 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(260) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 326 ) != m_toEnum.end() )
	{
		vgLogDebug("(326, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(326, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 326 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(326) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 360 ) != m_toEnum.end() )
	{
		vgLogDebug("(360, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(360, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 360 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(360) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 353 ) != m_toEnum.end() )
	{
		vgLogDebug("(353, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(353, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 353 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(353) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 325 ) != m_toEnum.end() )
	{
		vgLogDebug("(325, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(325, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 325 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(325) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 303 ) != m_toEnum.end() )
	{
		vgLogDebug("(303, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(303, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 303 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(303) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 283 ) != m_toEnum.end() )
	{
		vgLogDebug("(283, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(283, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 283 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(283) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 293 ) != m_toEnum.end() )
	{
		vgLogDebug("(293, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(293, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 293 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(293) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 361 ) != m_toEnum.end() )
	{
		vgLogDebug("(361, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(361, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 361 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(361) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 365 ) != m_toEnum.end() )
	{
		vgLogDebug("(365, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(365, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 365 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(365) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 371 ) != m_toEnum.end() )
	{
		vgLogDebug("(371, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(371, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 371 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(371) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 269 ) != m_toEnum.end() )
	{
		vgLogDebug("(269, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(269, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 269 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(269) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 346 ) != m_toEnum.end() )
	{
		vgLogDebug("(346, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(346, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 346 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(346) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 343 ) != m_toEnum.end() )
	{
		vgLogDebug("(343, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(343, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 343 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(343) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 278 ) != m_toEnum.end() )
	{
		vgLogDebug("(278, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(278, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 278 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(278) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 364 ) != m_toEnum.end() )
	{
		vgLogDebug("(364, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(364, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 364 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(364) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 324 ) != m_toEnum.end() )
	{
		vgLogDebug("(324, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(324, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 324 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(324) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 349 ) != m_toEnum.end() )
	{
		vgLogDebug("(349, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(349, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 349 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(349) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 355 ) != m_toEnum.end() )
	{
		vgLogDebug("(355, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(355, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 355 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(355) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 340 ) != m_toEnum.end() )
	{
		vgLogDebug("(340, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(340, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 340 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(340) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 341 ) != m_toEnum.end() )
	{
		vgLogDebug("(341, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(341, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 341 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(341) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 351 ) != m_toEnum.end() )
	{
		vgLogDebug("(351, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(351, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 351 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(351) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 316 ) != m_toEnum.end() )
	{
		vgLogDebug("(316, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(316, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 316 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(316) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 315 ) != m_toEnum.end() )
	{
		vgLogDebug("(315, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(315, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 315 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(315) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 302 ) != m_toEnum.end() )
	{
		vgLogDebug("(302, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(302, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 302 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(302) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 342 ) != m_toEnum.end() )
	{
		vgLogDebug("(342, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(342, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 342 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(342) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 345 ) != m_toEnum.end() )
	{
		vgLogDebug("(345, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(345, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 345 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(345) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 299 ) != m_toEnum.end() )
	{
		vgLogDebug("(299, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(299, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 299 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(299) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(277, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(277) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 372 ) != m_toEnum.end() )
	{
		vgLogDebug("(372, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(372, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 372 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(372) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 266 ) != m_toEnum.end() )
	{
		vgLogDebug("(266, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(266, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 266 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(266) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 344 ) != m_toEnum.end() )
	{
		vgLogDebug("(344, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(344, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 344 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(344) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 263 ) != m_toEnum.end() )
	{
		vgLogDebug("(263, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(263, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 263 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(263) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 331 ) != m_toEnum.end() )
	{
		vgLogDebug("(331, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(331, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 331 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(331) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 329 ) != m_toEnum.end() )
	{
		vgLogDebug("(329, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(329, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 329 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(329) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 333 ) != m_toEnum.end() )
	{
		vgLogDebug("(333, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(333, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 333 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(333) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 281 ) != m_toEnum.end() )
	{
		vgLogDebug("(281, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(281, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 281 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(281) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(290, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(290) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 310 ) != m_toEnum.end() )
	{
		vgLogDebug("(310, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(310, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 310 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(310) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 367 ) != m_toEnum.end() )
	{
		vgLogDebug("(367, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(367, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 367 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(367) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 314 ) != m_toEnum.end() )
	{
		vgLogDebug("(314, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(314, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 314 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(314) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 328 ) != m_toEnum.end() )
	{
		vgLogDebug("(328, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(328, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 328 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(328) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 265 ) != m_toEnum.end() )
	{
		vgLogDebug("(265, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(265, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 265 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(265) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 279 ) != m_toEnum.end() )
	{
		vgLogDebug("(279, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(279, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 279 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(279) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 288 ) != m_toEnum.end() )
	{
		vgLogDebug("(288, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(288, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 288 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(288) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 274 ) != m_toEnum.end() )
	{
		vgLogDebug("(274, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(274, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 274 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(274) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 271 ) != m_toEnum.end() )
	{
		vgLogDebug("(271, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(271, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 271 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(271) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 264 ) != m_toEnum.end() )
	{
		vgLogDebug("(264, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(264, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 264 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(264) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 291 ) != m_toEnum.end() )
	{
		vgLogDebug("(291, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(291, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 291 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(291) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 352 ) != m_toEnum.end() )
	{
		vgLogDebug("(352, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(352, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 352 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(352) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 258 ) != m_toEnum.end() )
	{
		vgLogDebug("(258, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(258, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 258 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(258) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 300 ) != m_toEnum.end() )
	{
		vgLogDebug("(300, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(300, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 300 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(300) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 336 ) != m_toEnum.end() )
	{
		vgLogDebug("(336, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(336, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 336 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(336) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 317 ) != m_toEnum.end() )
	{
		vgLogDebug("(317, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(317, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 317 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(317) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 363 ) != m_toEnum.end() )
	{
		vgLogDebug("(363, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(363, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 363 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(363) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(280, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(280) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 294 ) != m_toEnum.end() )
	{
		vgLogDebug("(294, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(294, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 294 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(294) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 338 ) != m_toEnum.end() )
	{
		vgLogDebug("(338, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(338, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 338 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(338) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 337 ) != m_toEnum.end() )
	{
		vgLogDebug("(337, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(337, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 337 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(337) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 334 ) != m_toEnum.end() )
	{
		vgLogDebug("(334, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(334, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 334 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(334) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 332 ) != m_toEnum.end() )
	{
		vgLogDebug("(332, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(332, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 332 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(332) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 330 ) != m_toEnum.end() )
	{
		vgLogDebug("(330, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(330, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 330 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(330) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 354 ) != m_toEnum.end() )
	{
		vgLogDebug("(354, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(354, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 354 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(354) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 282 ) != m_toEnum.end() )
	{
		vgLogDebug("(282, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(282, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 282 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(282) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 296 ) != m_toEnum.end() )
	{
		vgLogDebug("(296, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(296, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 296 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(296) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(287, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::OutputBuffers::OutputValueType(287) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(286, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::OutputBuffers::OutputValueType(286) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, OutputValueType) already in m_toEnum enum registry");
		assert( false && "(285, OutputValueType) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::OutputBuffers::OutputValueType(285) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 347 ) != m_toEnum.end() )
	{
		vgLogDebug("(347, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(347, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 347 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(347) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 292 ) != m_toEnum.end() )
	{
		vgLogDebug("(292, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(292, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 292 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(292) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 289 ) != m_toEnum.end() )
	{
		vgLogDebug("(289, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(289, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 289 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(289) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 273 ) != m_toEnum.end() )
	{
		vgLogDebug("(273, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(273, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 273 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(273) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 369 ) != m_toEnum.end() )
	{
		vgLogDebug("(369, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(369, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 369 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(369) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 256 ) != m_toEnum.end() )
	{
		vgLogDebug("(256, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(256, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 256 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(256) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 311 ) != m_toEnum.end() )
	{
		vgLogDebug("(311, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(311, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 311 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(311) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 306 ) != m_toEnum.end() )
	{
		vgLogDebug("(306, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(306, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 306 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(306) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 307 ) != m_toEnum.end() )
	{
		vgLogDebug("(307, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(307, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 307 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(307) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 262 ) != m_toEnum.end() )
	{
		vgLogDebug("(262, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(262, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 262 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(262) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 356 ) != m_toEnum.end() )
	{
		vgLogDebug("(356, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(356, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 356 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(356) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 257 ) != m_toEnum.end() )
	{
		vgLogDebug("(257, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(257, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 257 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(257) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 313 ) != m_toEnum.end() )
	{
		vgLogDebug("(313, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(313, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 313 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(313) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 275 ) != m_toEnum.end() )
	{
		vgLogDebug("(275, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(275, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 275 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(275) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 270 ) != m_toEnum.end() )
	{
		vgLogDebug("(270, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(270, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 270 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(270) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 298 ) != m_toEnum.end() )
	{
		vgLogDebug("(298, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(298, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 298 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(298) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 348 ) != m_toEnum.end() )
	{
		vgLogDebug("(348, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(348, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 348 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(348) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 297 ) != m_toEnum.end() )
	{
		vgLogDebug("(297, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(297, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 297 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(297) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 308 ) != m_toEnum.end() )
	{
		vgLogDebug("(308, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(308, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 308 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(308) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 373 ) != m_toEnum.end() )
	{
		vgLogDebug("(373, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(373, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 373 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(373) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 312 ) != m_toEnum.end() )
	{
		vgLogDebug("(312, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(312, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 312 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(312) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 350 ) != m_toEnum.end() )
	{
		vgLogDebug("(350, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(350, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 350 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(350) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 327 ) != m_toEnum.end() )
	{
		vgLogDebug("(327, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(327, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 327 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(327) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 276 ) != m_toEnum.end() )
	{
		vgLogDebug("(276, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(276, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 276 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(276) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 259 ) != m_toEnum.end() )
	{
		vgLogDebug("(259, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(259, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 259 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(259) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 268 ) != m_toEnum.end() )
	{
		vgLogDebug("(268, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(268, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 268 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(268) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 370 ) != m_toEnum.end() )
	{
		vgLogDebug("(370, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(370, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 370 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(370) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 322 ) != m_toEnum.end() )
	{
		vgLogDebug("(322, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(322, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 322 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(322) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 309 ) != m_toEnum.end() )
	{
		vgLogDebug("(309, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(309, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 309 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(309) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 318 ) != m_toEnum.end() )
	{
		vgLogDebug("(318, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(318, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 318 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(318) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 267 ) != m_toEnum.end() )
	{
		vgLogDebug("(267, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(267, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 267 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(267) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 339 ) != m_toEnum.end() )
	{
		vgLogDebug("(339, Input2ValueType) already in m_toEnum enum registry");
		assert( false && "(339, Input2ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 339 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(339) );
	
}



} // namespace node

} // namespace vgd
