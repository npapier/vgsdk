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
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, SHADOW) already in m_toString enum registry");
		assert( false && "(285, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 295 ) != m_toString.end() )
	{
		vgLogDebug("(295, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(295, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 295 ] = std::string("MIN_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, SHADOW_MAPPING_64U) already in m_toString enum registry");
		assert( false && "(278, SHADOW_MAPPING_64U) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("SHADOW_MAPPING_64U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 277 ) != m_toString.end() )
	{
		vgLogDebug("(277, SHADOW_MAPPING_32UM) already in m_toString enum registry");
		assert( false && "(277, SHADOW_MAPPING_32UM) already in registry" );
	}
	#endif

	m_toString[ 277 ] = std::string("SHADOW_MAPPING_32UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 273 ) != m_toString.end() )
	{
		vgLogDebug("(273, SHADOW_MAPPING_4DM) already in m_toString enum registry");
		assert( false && "(273, SHADOW_MAPPING_4DM) already in registry" );
	}
	#endif

	m_toString[ 273 ] = std::string("SHADOW_MAPPING_4DM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, WRAP_T) already in m_toString enum registry");
		assert( false && "(287, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, CLAMP) already in m_toString enum registry");
		assert( false && "(290, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(291, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("CLAMP_TO_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, VERY_HIGH) already in m_toString enum registry");
		assert( false && "(280, VERY_HIGH) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("VERY_HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, WRAP_S) already in m_toString enum registry");
		assert( false && "(286, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, WRAP_R) already in m_toString enum registry");
		assert( false && "(288, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("WRAP_R");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, STANDARD_PER_VERTEX) already in m_toString enum registry");
		assert( false && "(266, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("STANDARD_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 272 ) != m_toString.end() )
	{
		vgLogDebug("(272, SHADOW_MAPPING_4U) already in m_toString enum registry");
		assert( false && "(272, SHADOW_MAPPING_4U) already in registry" );
	}
	#endif

	m_toString[ 272 ] = std::string("SHADOW_MAPPING_4U");

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
	if ( m_toString.find( 297 ) != m_toString.end() )
	{
		vgLogDebug("(297, NEAREST) already in m_toString enum registry");
		assert( false && "(297, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 297 ] = std::string("NEAREST");

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
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, INT32) already in m_toString enum registry");
		assert( false && "(263, INT32) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("INT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 271 ) != m_toString.end() )
	{
		vgLogDebug("(271, SHADOW_MAPPING) already in m_toString enum registry");
		assert( false && "(271, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toString[ 271 ] = std::string("SHADOW_MAPPING");

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
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, REPEAT) already in m_toString enum registry");
		assert( false && "(289, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, INT16) already in m_toString enum registry");
		assert( false && "(264, INT16) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("INT16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 284 ) != m_toString.end() )
	{
		vgLogDebug("(284, IMAGE) already in m_toString enum registry");
		assert( false && "(284, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 284 ] = std::string("IMAGE");

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
	if ( m_toString.find( 276 ) != m_toString.end() )
	{
		vgLogDebug("(276, SHADOW_MAPPING_32U) already in m_toString enum registry");
		assert( false && "(276, SHADOW_MAPPING_32U) already in registry" );
	}
	#endif

	m_toString[ 276 ] = std::string("SHADOW_MAPPING_32U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 270 ) != m_toString.end() )
	{
		vgLogDebug("(270, SHADOW_OFF) already in m_toString enum registry");
		assert( false && "(270, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toString[ 270 ] = std::string("SHADOW_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 274 ) != m_toString.end() )
	{
		vgLogDebug("(274, SHADOW_MAPPING_16U) already in m_toString enum registry");
		assert( false && "(274, SHADOW_MAPPING_16U) already in registry" );
	}
	#endif

	m_toString[ 274 ] = std::string("SHADOW_MAPPING_16U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 269 ) != m_toString.end() )
	{
		vgLogDebug("(269, AT_EYE) already in m_toString enum registry");
		assert( false && "(269, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 269 ] = std::string("AT_EYE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 301 ) != m_toString.end() )
	{
		vgLogDebug("(301, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(301, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 301 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 302 ) != m_toString.end() )
	{
		vgLogDebug("(302, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(302, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 302 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 298 ) != m_toString.end() )
	{
		vgLogDebug("(298, LINEAR) already in m_toString enum registry");
		assert( false && "(298, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 298 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, LIGHTING_OFF) already in m_toString enum registry");
		assert( false && "(265, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("LIGHTING_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 293 ) != m_toString.end() )
	{
		vgLogDebug("(293, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(293, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 293 ] = std::string("MIRRORED_REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 281 ) != m_toString.end() )
	{
		vgLogDebug("(281, HIGH) already in m_toString enum registry");
		assert( false && "(281, HIGH) already in registry" );
	}
	#endif

	m_toString[ 281 ] = std::string("HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 292 ) != m_toString.end() )
	{
		vgLogDebug("(292, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(292, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 292 ] = std::string("CLAMP_TO_BORDER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 279 ) != m_toString.end() )
	{
		vgLogDebug("(279, SHADOW_MAPPING_64UM) already in m_toString enum registry");
		assert( false && "(279, SHADOW_MAPPING_64UM) already in registry" );
	}
	#endif

	m_toString[ 279 ] = std::string("SHADOW_MAPPING_64UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 275 ) != m_toString.end() )
	{
		vgLogDebug("(275, SHADOW_MAPPING_16UM) already in m_toString enum registry");
		assert( false && "(275, SHADOW_MAPPING_16UM) already in registry" );
	}
	#endif

	m_toString[ 275 ] = std::string("SHADOW_MAPPING_16UM");

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
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, STANDARD_PER_PIXEL) already in m_toString enum registry");
		assert( false && "(267, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("STANDARD_PER_PIXEL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 294 ) != m_toString.end() )
	{
		vgLogDebug("(294, ONCE) already in m_toString enum registry");
		assert( false && "(294, ONCE) already in registry" );
	}
	#endif

	m_toString[ 294 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 299 ) != m_toString.end() )
	{
		vgLogDebug("(299, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(299, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 299 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 300 ) != m_toString.end() )
	{
		vgLogDebug("(300, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(300, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 300 ] = std::string("LINEAR_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, FLOAT) already in m_toString enum registry");
		assert( false && "(262, FLOAT) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("FLOAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 283 ) != m_toString.end() )
	{
		vgLogDebug("(283, LOW) already in m_toString enum registry");
		assert( false && "(283, LOW) already in registry" );
	}
	#endif

	m_toString[ 283 ] = std::string("LOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 296 ) != m_toString.end() )
	{
		vgLogDebug("(296, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(296, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 296 ] = std::string("MAG_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 268 ) != m_toString.end() )
	{
		vgLogDebug("(268, AT_INFINITY) already in m_toString enum registry");
		assert( false && "(268, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 268 ] = std::string("AT_INFINITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 282 ) != m_toString.end() )
	{
		vgLogDebug("(282, MEDIUM) already in m_toString enum registry");
		assert( false && "(282, MEDIUM) already in registry" );
	}
	#endif

	m_toString[ 282 ] = std::string("MEDIUM");

	// Initializes m_toEnum map

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(285, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(285) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 295 ) != m_toEnum.end() )
	{
		vgLogDebug("(295, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(295, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 295 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(295) );
	
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
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(277, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(277) );
	
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
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(287, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(287) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(290, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(290) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 291 ) != m_toEnum.end() )
	{
		vgLogDebug("(291, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(291, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 291 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(291) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(280, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(280) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(286, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(286) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 288 ) != m_toEnum.end() )
	{
		vgLogDebug("(288, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(288, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 288 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(288) );
	
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
	if ( m_toEnum.find( 272 ) != m_toEnum.end() )
	{
		vgLogDebug("(272, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(272, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 272 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(272) );
	
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
	if ( m_toEnum.find( 297 ) != m_toEnum.end() )
	{
		vgLogDebug("(297, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(297, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 297 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(297) );
	
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
	if ( m_toEnum.find( 263 ) != m_toEnum.end() )
	{
		vgLogDebug("(263, ShadowMapTypeValueType) already in m_toEnum enum registry");
		assert( false && "(263, ShadowMapTypeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 263 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(263) );
	
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
	if ( m_toEnum.find( 258 ) != m_toEnum.end() )
	{
		vgLogDebug("(258, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(258, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 258 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(258) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 289 ) != m_toEnum.end() )
	{
		vgLogDebug("(289, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(289, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 289 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(289) );
	
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
	if ( m_toEnum.find( 284 ) != m_toEnum.end() )
	{
		vgLogDebug("(284, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(284, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 284 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(284) );
	
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
	if ( m_toEnum.find( 276 ) != m_toEnum.end() )
	{
		vgLogDebug("(276, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(276, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 276 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(276) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 270 ) != m_toEnum.end() )
	{
		vgLogDebug("(270, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(270, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 270 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(270) );
	
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
	if ( m_toEnum.find( 269 ) != m_toEnum.end() )
	{
		vgLogDebug("(269, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(269, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 269 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(269) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 301 ) != m_toEnum.end() )
	{
		vgLogDebug("(301, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(301, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 301 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(301) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 302 ) != m_toEnum.end() )
	{
		vgLogDebug("(302, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(302, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 302 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(302) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 298 ) != m_toEnum.end() )
	{
		vgLogDebug("(298, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(298, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 298 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(298) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 265 ) != m_toEnum.end() )
	{
		vgLogDebug("(265, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(265, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 265 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(265) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 293 ) != m_toEnum.end() )
	{
		vgLogDebug("(293, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(293, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 293 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(293) );
	
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
	if ( m_toEnum.find( 292 ) != m_toEnum.end() )
	{
		vgLogDebug("(292, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(292, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 292 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(292) );
	
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
	if ( m_toEnum.find( 275 ) != m_toEnum.end() )
	{
		vgLogDebug("(275, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(275, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 275 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(275) );
	
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
	if ( m_toEnum.find( 267 ) != m_toEnum.end() )
	{
		vgLogDebug("(267, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(267, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 267 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(267) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 294 ) != m_toEnum.end() )
	{
		vgLogDebug("(294, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(294, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 294 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(294) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 299 ) != m_toEnum.end() )
	{
		vgLogDebug("(299, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(299, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 299 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(299) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 300 ) != m_toEnum.end() )
	{
		vgLogDebug("(300, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(300, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 300 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(300) );
	
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
	if ( m_toEnum.find( 283 ) != m_toEnum.end() )
	{
		vgLogDebug("(283, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(283, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 283 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(283) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 296 ) != m_toEnum.end() )
	{
		vgLogDebug("(296, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(296, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 296 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(296) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 268 ) != m_toEnum.end() )
	{
		vgLogDebug("(268, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(268, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 268 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(268) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 282 ) != m_toEnum.end() )
	{
		vgLogDebug("(282, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(282, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 282 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(282) );
	
}



} // namespace node

} // namespace vgd
