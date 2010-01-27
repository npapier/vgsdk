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
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, SHADOW) already in m_toString enum registry");
		assert( false && "(278, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(288, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("MIN_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(286, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("MIRRORED_REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, WRAP_T) already in m_toString enum registry");
		assert( false && "(280, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 283 ) != m_toString.end() )
	{
		vgLogDebug("(283, CLAMP) already in m_toString enum registry");
		assert( false && "(283, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 283 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 284 ) != m_toString.end() )
	{
		vgLogDebug("(284, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(284, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 284 ] = std::string("CLAMP_TO_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 273 ) != m_toString.end() )
	{
		vgLogDebug("(273, VERY_HIGH) already in m_toString enum registry");
		assert( false && "(273, VERY_HIGH) already in registry" );
	}
	#endif

	m_toString[ 273 ] = std::string("VERY_HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 279 ) != m_toString.end() )
	{
		vgLogDebug("(279, WRAP_S) already in m_toString enum registry");
		assert( false && "(279, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 279 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 281 ) != m_toString.end() )
	{
		vgLogDebug("(281, WRAP_R) already in m_toString enum registry");
		assert( false && "(281, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 281 ] = std::string("WRAP_R");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, STANDARD_PER_VERTEX) already in m_toString enum registry");
		assert( false && "(263, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("STANDARD_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 269 ) != m_toString.end() )
	{
		vgLogDebug("(269, SHADOW_MAPPING_4U) already in m_toString enum registry");
		assert( false && "(269, SHADOW_MAPPING_4U) already in registry" );
	}
	#endif

	m_toString[ 269 ] = std::string("SHADOW_MAPPING_4U");

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
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, NEAREST) already in m_toString enum registry");
		assert( false && "(290, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("NEAREST");

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
	if ( m_toString.find( 270 ) != m_toString.end() )
	{
		vgLogDebug("(270, SHADOW_MAPPING_4D) already in m_toString enum registry");
		assert( false && "(270, SHADOW_MAPPING_4D) already in registry" );
	}
	#endif

	m_toString[ 270 ] = std::string("SHADOW_MAPPING_4D");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 268 ) != m_toString.end() )
	{
		vgLogDebug("(268, SHADOW_MAPPING) already in m_toString enum registry");
		assert( false && "(268, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toString[ 268 ] = std::string("SHADOW_MAPPING");

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
	if ( m_toString.find( 282 ) != m_toString.end() )
	{
		vgLogDebug("(282, REPEAT) already in m_toString enum registry");
		assert( false && "(282, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 282 ] = std::string("REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 277 ) != m_toString.end() )
	{
		vgLogDebug("(277, IMAGE) already in m_toString enum registry");
		assert( false && "(277, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 277 ] = std::string("IMAGE");

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
	if ( m_toString.find( 272 ) != m_toString.end() )
	{
		vgLogDebug("(272, SHADOW_MAPPING_32U) already in m_toString enum registry");
		assert( false && "(272, SHADOW_MAPPING_32U) already in registry" );
	}
	#endif

	m_toString[ 272 ] = std::string("SHADOW_MAPPING_32U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, SHADOW_OFF) already in m_toString enum registry");
		assert( false && "(267, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("SHADOW_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 271 ) != m_toString.end() )
	{
		vgLogDebug("(271, SHADOW_MAPPING_16U) already in m_toString enum registry");
		assert( false && "(271, SHADOW_MAPPING_16U) already in registry" );
	}
	#endif

	m_toString[ 271 ] = std::string("SHADOW_MAPPING_16U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, AT_EYE) already in m_toString enum registry");
		assert( false && "(266, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("AT_EYE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 294 ) != m_toString.end() )
	{
		vgLogDebug("(294, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(294, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 294 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 295 ) != m_toString.end() )
	{
		vgLogDebug("(295, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(295, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 295 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, LINEAR) already in m_toString enum registry");
		assert( false && "(291, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, LIGHTING_OFF) already in m_toString enum registry");
		assert( false && "(262, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("LIGHTING_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 274 ) != m_toString.end() )
	{
		vgLogDebug("(274, HIGH) already in m_toString enum registry");
		assert( false && "(274, HIGH) already in registry" );
	}
	#endif

	m_toString[ 274 ] = std::string("HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(285, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("CLAMP_TO_BORDER");

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
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, STANDARD_PER_PIXEL) already in m_toString enum registry");
		assert( false && "(264, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("STANDARD_PER_PIXEL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, ONCE) already in m_toString enum registry");
		assert( false && "(287, ONCE) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 292 ) != m_toString.end() )
	{
		vgLogDebug("(292, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(292, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 292 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 293 ) != m_toString.end() )
	{
		vgLogDebug("(293, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(293, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 293 ] = std::string("LINEAR_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 276 ) != m_toString.end() )
	{
		vgLogDebug("(276, LOW) already in m_toString enum registry");
		assert( false && "(276, LOW) already in registry" );
	}
	#endif

	m_toString[ 276 ] = std::string("LOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(289, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("MAG_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, AT_INFINITY) already in m_toString enum registry");
		assert( false && "(265, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("AT_INFINITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 275 ) != m_toString.end() )
	{
		vgLogDebug("(275, MEDIUM) already in m_toString enum registry");
		assert( false && "(275, MEDIUM) already in registry" );
	}
	#endif

	m_toString[ 275 ] = std::string("MEDIUM");

	// Initializes m_toEnum map

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 278 ) != m_toEnum.end() )
	{
		vgLogDebug("(278, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(278, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 278 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(278) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 288 ) != m_toEnum.end() )
	{
		vgLogDebug("(288, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(288, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 288 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(288) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(286, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(286) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(280, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(280) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 283 ) != m_toEnum.end() )
	{
		vgLogDebug("(283, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(283, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 283 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(283) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 284 ) != m_toEnum.end() )
	{
		vgLogDebug("(284, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(284, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 284 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(284) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 273 ) != m_toEnum.end() )
	{
		vgLogDebug("(273, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(273, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 273 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(273) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 279 ) != m_toEnum.end() )
	{
		vgLogDebug("(279, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(279, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 279 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(279) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 281 ) != m_toEnum.end() )
	{
		vgLogDebug("(281, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(281, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 281 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(281) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 263 ) != m_toEnum.end() )
	{
		vgLogDebug("(263, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(263, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 263 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(263) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 269 ) != m_toEnum.end() )
	{
		vgLogDebug("(269, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(269, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 269 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(269) );
	
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
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(290, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(290) );
	
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
	if ( m_toEnum.find( 270 ) != m_toEnum.end() )
	{
		vgLogDebug("(270, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(270, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 270 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(270) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 268 ) != m_toEnum.end() )
	{
		vgLogDebug("(268, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(268, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 268 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(268) );
	
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
	if ( m_toEnum.find( 282 ) != m_toEnum.end() )
	{
		vgLogDebug("(282, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(282, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 282 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(282) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(277, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(277) );
	
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
	if ( m_toEnum.find( 272 ) != m_toEnum.end() )
	{
		vgLogDebug("(272, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(272, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 272 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(272) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 267 ) != m_toEnum.end() )
	{
		vgLogDebug("(267, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(267, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 267 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(267) );
	
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
	if ( m_toEnum.find( 266 ) != m_toEnum.end() )
	{
		vgLogDebug("(266, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(266, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 266 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(266) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 294 ) != m_toEnum.end() )
	{
		vgLogDebug("(294, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(294, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 294 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(294) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 295 ) != m_toEnum.end() )
	{
		vgLogDebug("(295, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(295, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 295 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(295) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 291 ) != m_toEnum.end() )
	{
		vgLogDebug("(291, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(291, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 291 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(291) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 262 ) != m_toEnum.end() )
	{
		vgLogDebug("(262, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(262, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 262 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(262) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 274 ) != m_toEnum.end() )
	{
		vgLogDebug("(274, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(274, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 274 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(274) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(285, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(285) );
	
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
	if ( m_toEnum.find( 264 ) != m_toEnum.end() )
	{
		vgLogDebug("(264, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(264, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 264 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(264) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(287, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(287) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 292 ) != m_toEnum.end() )
	{
		vgLogDebug("(292, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(292, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 292 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(292) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 293 ) != m_toEnum.end() )
	{
		vgLogDebug("(293, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(293, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 293 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(293) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 276 ) != m_toEnum.end() )
	{
		vgLogDebug("(276, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(276, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 276 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(276) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 289 ) != m_toEnum.end() )
	{
		vgLogDebug("(289, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(289, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 289 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(289) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 265 ) != m_toEnum.end() )
	{
		vgLogDebug("(265, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(265, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 265 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(265) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 275 ) != m_toEnum.end() )
	{
		vgLogDebug("(275, ShadowQualityValueType) already in m_toEnum enum registry");
		assert( false && "(275, ShadowQualityValueType) already in registry" );
	}
	#endif

	m_toEnum[ 275 ] = vgd::makeShp( new vgd::node::LightModel::ShadowQualityValueType(275) );
	
}



} // namespace node

} // namespace vgd
