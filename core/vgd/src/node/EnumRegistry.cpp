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
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, FLOAT32) already in m_toString enum registry");
		assert( false && "(265, FLOAT32) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("FLOAT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 296 ) != m_toString.end() )
	{
		vgLogDebug("(296, ORIGINAL_COLOR) already in m_toString enum registry");
		assert( false && "(296, ORIGINAL_COLOR) already in registry" );
	}
	#endif

	m_toString[ 296 ] = std::string("ORIGINAL_COLOR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, COLOR_EDGE_DETECT) already in m_toString enum registry");
		assert( false && "(291, COLOR_EDGE_DETECT) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("COLOR_EDGE_DETECT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 303 ) != m_toString.end() )
	{
		vgLogDebug("(303, SHADOW) already in m_toString enum registry");
		assert( false && "(303, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 303 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 318 ) != m_toString.end() )
	{
		vgLogDebug("(318, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(318, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 318 ] = std::string("MIN_FILTER");

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
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, SHADOW_MAPPING_32UM) already in m_toString enum registry");
		assert( false && "(278, SHADOW_MAPPING_32UM) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("SHADOW_MAPPING_32UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, COLOR_TO_MONOCHROME) already in m_toString enum registry");
		assert( false && "(285, COLOR_TO_MONOCHROME) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("COLOR_TO_MONOCHROME");

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
	if ( m_toString.find( 310 ) != m_toString.end() )
	{
		vgLogDebug("(310, WRAP_T) already in m_toString enum registry");
		assert( false && "(310, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 310 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 307 ) != m_toString.end() )
	{
		vgLogDebug("(307, DEPTH_COMPONENT_32) already in m_toString enum registry");
		assert( false && "(307, DEPTH_COMPONENT_32) already in registry" );
	}
	#endif

	m_toString[ 307 ] = std::string("DEPTH_COMPONENT_32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 314 ) != m_toString.end() )
	{
		vgLogDebug("(314, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(314, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 314 ] = std::string("CLAMP_TO_EDGE");

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
	if ( m_toString.find( 309 ) != m_toString.end() )
	{
		vgLogDebug("(309, WRAP_S) already in m_toString enum registry");
		assert( false && "(309, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 309 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 311 ) != m_toString.end() )
	{
		vgLogDebug("(311, WRAP_R) already in m_toString enum registry");
		assert( false && "(311, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 311 ] = std::string("WRAP_R");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, BLUR_HORIZ) already in m_toString enum registry");
		assert( false && "(287, BLUR_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("BLUR_HORIZ");

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
	if ( m_toString.find( 297 ) != m_toString.end() )
	{
		vgLogDebug("(297, ORIGINAL_NORMAL) already in m_toString enum registry");
		assert( false && "(297, ORIGINAL_NORMAL) already in registry" );
	}
	#endif

	m_toString[ 297 ] = std::string("ORIGINAL_NORMAL");

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
	if ( m_toString.find( 261 ) != m_toString.end() )
	{
		vgLogDebug("(261, CW) already in m_toString enum registry");
		assert( false && "(261, CW) already in registry" );
	}
	#endif

	m_toString[ 261 ] = std::string("CW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 306 ) != m_toString.end() )
	{
		vgLogDebug("(306, DEPTH_COMPONENT_24) already in m_toString enum registry");
		assert( false && "(306, DEPTH_COMPONENT_24) already in registry" );
	}
	#endif

	m_toString[ 306 ] = std::string("DEPTH_COMPONENT_24");

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
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, INT32) already in m_toString enum registry");
		assert( false && "(264, INT32) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("INT32");

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
	if ( m_toString.find( 258 ) != m_toString.end() )
	{
		vgLogDebug("(258, FRONT) already in m_toString enum registry");
		assert( false && "(258, FRONT) already in registry" );
	}
	#endif

	m_toString[ 258 ] = std::string("FRONT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 312 ) != m_toString.end() )
	{
		vgLogDebug("(312, REPEAT) already in m_toString enum registry");
		assert( false && "(312, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 312 ] = std::string("REPEAT");

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
	if ( m_toString.find( 315 ) != m_toString.end() )
	{
		vgLogDebug("(315, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(315, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 315 ] = std::string("CLAMP_TO_BORDER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 302 ) != m_toString.end() )
	{
		vgLogDebug("(302, IMAGE) already in m_toString enum registry");
		assert( false && "(302, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 302 ] = std::string("IMAGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 294 ) != m_toString.end() )
	{
		vgLogDebug("(294, COMBINE) already in m_toString enum registry");
		assert( false && "(294, COMBINE) already in registry" );
	}
	#endif

	m_toString[ 294 ] = std::string("COMBINE");

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
	if ( m_toString.find( 260 ) != m_toString.end() )
	{
		vgLogDebug("(260, CCW) already in m_toString enum registry");
		assert( false && "(260, CCW) already in registry" );
	}
	#endif

	m_toString[ 260 ] = std::string("CCW");

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
	if ( m_toString.find( 271 ) != m_toString.end() )
	{
		vgLogDebug("(271, SHADOW_OFF) already in m_toString enum registry");
		assert( false && "(271, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toString[ 271 ] = std::string("SHADOW_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 298 ) != m_toString.end() )
	{
		vgLogDebug("(298, PREVIOUS_COLOR) already in m_toString enum registry");
		assert( false && "(298, PREVIOUS_COLOR) already in registry" );
	}
	#endif

	m_toString[ 298 ] = std::string("PREVIOUS_COLOR");

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
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, SHADOW_MAPPING_64UM) already in m_toString enum registry");
		assert( false && "(280, SHADOW_MAPPING_64UM) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("SHADOW_MAPPING_64UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 300 ) != m_toString.end() )
	{
		vgLogDebug("(300, INPUT1_ORIGINAL_COLOR) already in m_toString enum registry");
		assert( false && "(300, INPUT1_ORIGINAL_COLOR) already in registry" );
	}
	#endif

	m_toString[ 300 ] = std::string("INPUT1_ORIGINAL_COLOR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 293 ) != m_toString.end() )
	{
		vgLogDebug("(293, UP_FILTER4) already in m_toString enum registry");
		assert( false && "(293, UP_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 293 ] = std::string("UP_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 308 ) != m_toString.end() )
	{
		vgLogDebug("(308, DEPTH_COMPONENT_32F) already in m_toString enum registry");
		assert( false && "(308, DEPTH_COMPONENT_32F) already in registry" );
	}
	#endif

	m_toString[ 308 ] = std::string("DEPTH_COMPONENT_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 299 ) != m_toString.end() )
	{
		vgLogDebug("(299, NONE) already in m_toString enum registry");
		assert( false && "(299, NONE) already in registry" );
	}
	#endif

	m_toString[ 299 ] = std::string("NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 292 ) != m_toString.end() )
	{
		vgLogDebug("(292, DOWN_FILTER4) already in m_toString enum registry");
		assert( false && "(292, DOWN_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 292 ] = std::string("DOWN_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 325 ) != m_toString.end() )
	{
		vgLogDebug("(325, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(325, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 325 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 321 ) != m_toString.end() )
	{
		vgLogDebug("(321, LINEAR) already in m_toString enum registry");
		assert( false && "(321, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 321 ] = std::string("LINEAR");

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
	if ( m_toString.find( 316 ) != m_toString.end() )
	{
		vgLogDebug("(316, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(316, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 316 ] = std::string("MIRRORED_REPEAT");

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
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, BLOOM_VERT) already in m_toString enum registry");
		assert( false && "(290, BLOOM_VERT) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("BLOOM_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, BLUR_VERT) already in m_toString enum registry");
		assert( false && "(288, BLUR_VERT) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("BLUR_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 304 ) != m_toString.end() )
	{
		vgLogDebug("(304, AUTOMATIC) already in m_toString enum registry");
		assert( false && "(304, AUTOMATIC) already in registry" );
	}
	#endif

	m_toString[ 304 ] = std::string("AUTOMATIC");

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
	if ( m_toString.find( 313 ) != m_toString.end() )
	{
		vgLogDebug("(313, CLAMP) already in m_toString enum registry");
		assert( false && "(313, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 313 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, BLOOM_HORIZ) already in m_toString enum registry");
		assert( false && "(289, BLOOM_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("BLOOM_HORIZ");

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
	if ( m_toString.find( 305 ) != m_toString.end() )
	{
		vgLogDebug("(305, DEPTH_COMPONENT_16) already in m_toString enum registry");
		assert( false && "(305, DEPTH_COMPONENT_16) already in registry" );
	}
	#endif

	m_toString[ 305 ] = std::string("DEPTH_COMPONENT_16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 317 ) != m_toString.end() )
	{
		vgLogDebug("(317, ONCE) already in m_toString enum registry");
		assert( false && "(317, ONCE) already in registry" );
	}
	#endif

	m_toString[ 317 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 322 ) != m_toString.end() )
	{
		vgLogDebug("(322, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(322, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 322 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 324 ) != m_toString.end() )
	{
		vgLogDebug("(324, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(324, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 324 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 295 ) != m_toString.end() )
	{
		vgLogDebug("(295, NO_FILTER) already in m_toString enum registry");
		assert( false && "(295, NO_FILTER) already in registry" );
	}
	#endif

	m_toString[ 295 ] = std::string("NO_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 323 ) != m_toString.end() )
	{
		vgLogDebug("(323, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(323, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 323 ] = std::string("LINEAR_MIPMAP_NEAREST");

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
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, COLOR_INVERSE) already in m_toString enum registry");
		assert( false && "(286, COLOR_INVERSE) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("COLOR_INVERSE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 319 ) != m_toString.end() )
	{
		vgLogDebug("(319, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(319, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 319 ] = std::string("MAG_FILTER");

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
	if ( m_toString.find( 320 ) != m_toString.end() )
	{
		vgLogDebug("(320, NEAREST) already in m_toString enum registry");
		assert( false && "(320, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 320 ] = std::string("NEAREST");

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
	if ( m_toString.find( 301 ) != m_toString.end() )
	{
		vgLogDebug("(301, INPUT1_NONE) already in m_toString enum registry");
		assert( false && "(301, INPUT1_NONE) already in registry" );
	}
	#endif

	m_toString[ 301 ] = std::string("INPUT1_NONE");

	// Initializes m_toEnum map

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
	if ( m_toEnum.find( 296 ) != m_toEnum.end() )
	{
		vgLogDebug("(296, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(296, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 296 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(296) );
	
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
	if ( m_toEnum.find( 303 ) != m_toEnum.end() )
	{
		vgLogDebug("(303, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(303, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 303 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(303) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 318 ) != m_toEnum.end() )
	{
		vgLogDebug("(318, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(318, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 318 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(318) );
	
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
	if ( m_toEnum.find( 278 ) != m_toEnum.end() )
	{
		vgLogDebug("(278, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(278, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 278 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(278) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(285, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(285) );
	
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
	if ( m_toEnum.find( 310 ) != m_toEnum.end() )
	{
		vgLogDebug("(310, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(310, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 310 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(310) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 307 ) != m_toEnum.end() )
	{
		vgLogDebug("(307, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(307, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 307 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(307) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 314 ) != m_toEnum.end() )
	{
		vgLogDebug("(314, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(314, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 314 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(314) );
	
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
	if ( m_toEnum.find( 309 ) != m_toEnum.end() )
	{
		vgLogDebug("(309, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(309, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 309 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(309) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 311 ) != m_toEnum.end() )
	{
		vgLogDebug("(311, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(311, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 311 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(311) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(287, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(287) );
	
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
	if ( m_toEnum.find( 297 ) != m_toEnum.end() )
	{
		vgLogDebug("(297, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(297, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 297 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(297) );
	
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
	if ( m_toEnum.find( 261 ) != m_toEnum.end() )
	{
		vgLogDebug("(261, OrientationValueType) already in m_toEnum enum registry");
		assert( false && "(261, OrientationValueType) already in registry" );
	}
	#endif

	m_toEnum[ 261 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(261) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 306 ) != m_toEnum.end() )
	{
		vgLogDebug("(306, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(306, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 306 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(306) );
	
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
	if ( m_toEnum.find( 264 ) != m_toEnum.end() )
	{
		vgLogDebug("(264, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(264, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 264 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(264) );
	
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
	if ( m_toEnum.find( 258 ) != m_toEnum.end() )
	{
		vgLogDebug("(258, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(258, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 258 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(258) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 312 ) != m_toEnum.end() )
	{
		vgLogDebug("(312, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(312, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 312 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(312) );
	
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
	if ( m_toEnum.find( 315 ) != m_toEnum.end() )
	{
		vgLogDebug("(315, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(315, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 315 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(315) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 302 ) != m_toEnum.end() )
	{
		vgLogDebug("(302, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(302, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 302 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(302) );
	
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
	if ( m_toEnum.find( 257 ) != m_toEnum.end() )
	{
		vgLogDebug("(257, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(257, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 257 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(257) );
	
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
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(277, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(277) );
	
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
	if ( m_toEnum.find( 298 ) != m_toEnum.end() )
	{
		vgLogDebug("(298, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(298, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 298 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(298) );
	
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
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(280, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(280) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 300 ) != m_toEnum.end() )
	{
		vgLogDebug("(300, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(300, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 300 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(300) );
	
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
	if ( m_toEnum.find( 308 ) != m_toEnum.end() )
	{
		vgLogDebug("(308, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(308, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 308 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(308) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 299 ) != m_toEnum.end() )
	{
		vgLogDebug("(299, Input0ValueType) already in m_toEnum enum registry");
		assert( false && "(299, Input0ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 299 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(299) );
	
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
	if ( m_toEnum.find( 325 ) != m_toEnum.end() )
	{
		vgLogDebug("(325, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(325, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 325 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(325) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 321 ) != m_toEnum.end() )
	{
		vgLogDebug("(321, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(321, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 321 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(321) );
	
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
	if ( m_toEnum.find( 316 ) != m_toEnum.end() )
	{
		vgLogDebug("(316, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(316, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 316 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(316) );
	
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
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(290, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(290) );
	
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
	if ( m_toEnum.find( 304 ) != m_toEnum.end() )
	{
		vgLogDebug("(304, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(304, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 304 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(304) );
	
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
	if ( m_toEnum.find( 313 ) != m_toEnum.end() )
	{
		vgLogDebug("(313, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(313, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 313 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(313) );
	
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
	if ( m_toEnum.find( 305 ) != m_toEnum.end() )
	{
		vgLogDebug("(305, InternalFormatValueType) already in m_toEnum enum registry");
		assert( false && "(305, InternalFormatValueType) already in registry" );
	}
	#endif

	m_toEnum[ 305 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(305) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 317 ) != m_toEnum.end() )
	{
		vgLogDebug("(317, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(317, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 317 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(317) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 322 ) != m_toEnum.end() )
	{
		vgLogDebug("(322, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(322, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 322 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(322) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 324 ) != m_toEnum.end() )
	{
		vgLogDebug("(324, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(324, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 324 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(324) );
	
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
	if ( m_toEnum.find( 323 ) != m_toEnum.end() )
	{
		vgLogDebug("(323, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(323, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 323 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(323) );
	
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
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(286, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(286) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 319 ) != m_toEnum.end() )
	{
		vgLogDebug("(319, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(319, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 319 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(319) );
	
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
	if ( m_toEnum.find( 320 ) != m_toEnum.end() )
	{
		vgLogDebug("(320, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(320, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 320 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(320) );
	
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
	if ( m_toEnum.find( 301 ) != m_toEnum.end() )
	{
		vgLogDebug("(301, Input1ValueType) already in m_toEnum enum registry");
		assert( false && "(301, Input1ValueType) already in registry" );
	}
	#endif

	m_toEnum[ 301 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(301) );
	
}



} // namespace node

} // namespace vgd
