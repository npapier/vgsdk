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
	if ( m_toString.find( 274 ) != m_toString.end() )
	{
		vgLogDebug("(274, SHADOW) already in m_toString enum registry");
		assert( false && "(274, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 274 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 284 ) != m_toString.end() )
	{
		vgLogDebug("(284, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(284, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 284 ] = std::string("MIN_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 276 ) != m_toString.end() )
	{
		vgLogDebug("(276, WRAP_T) already in m_toString enum registry");
		assert( false && "(276, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 276 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 279 ) != m_toString.end() )
	{
		vgLogDebug("(279, CLAMP) already in m_toString enum registry");
		assert( false && "(279, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 279 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(280, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("CLAMP_TO_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 275 ) != m_toString.end() )
	{
		vgLogDebug("(275, WRAP_S) already in m_toString enum registry");
		assert( false && "(275, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 275 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 277 ) != m_toString.end() )
	{
		vgLogDebug("(277, WRAP_R) already in m_toString enum registry");
		assert( false && "(277, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 277 ] = std::string("WRAP_R");

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
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, NEAREST) already in m_toString enum registry");
		assert( false && "(286, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("NEAREST");

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
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, REPEAT) already in m_toString enum registry");
		assert( false && "(278, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 273 ) != m_toString.end() )
	{
		vgLogDebug("(273, IMAGE) already in m_toString enum registry");
		assert( false && "(273, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 273 ] = std::string("IMAGE");

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
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(290, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(291, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, LINEAR) already in m_toString enum registry");
		assert( false && "(287, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("LINEAR");

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
	if ( m_toString.find( 281 ) != m_toString.end() )
	{
		vgLogDebug("(281, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(281, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 281 ] = std::string("CLAMP_TO_BORDER");

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
	if ( m_toString.find( 283 ) != m_toString.end() )
	{
		vgLogDebug("(283, ONCE) already in m_toString enum registry");
		assert( false && "(283, ONCE) already in registry" );
	}
	#endif

	m_toString[ 283 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(288, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(289, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("LINEAR_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(285, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("MAG_FILTER");

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
	if ( m_toString.find( 282 ) != m_toString.end() )
	{
		vgLogDebug("(282, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(282, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 282 ] = std::string("MIRRORED_REPEAT");

	// Initializes m_toEnum map

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 274 ) != m_toEnum.end() )
	{
		vgLogDebug("(274, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(274, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 274 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(274) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 284 ) != m_toEnum.end() )
	{
		vgLogDebug("(284, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(284, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 284 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(284) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 276 ) != m_toEnum.end() )
	{
		vgLogDebug("(276, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(276, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 276 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(276) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 279 ) != m_toEnum.end() )
	{
		vgLogDebug("(279, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(279, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 279 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(279) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(280, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(280) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 275 ) != m_toEnum.end() )
	{
		vgLogDebug("(275, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(275, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 275 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(275) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, WrapParameterType) already in m_toEnum enum registry");
		assert( false && "(277, WrapParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::Texture::WrapParameterType(277) );
	
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
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(286, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(286) );
	
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
	if ( m_toEnum.find( 278 ) != m_toEnum.end() )
	{
		vgLogDebug("(278, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(278, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 278 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(278) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 273 ) != m_toEnum.end() )
	{
		vgLogDebug("(273, UsageValueType) already in m_toEnum enum registry");
		assert( false && "(273, UsageValueType) already in registry" );
	}
	#endif

	m_toEnum[ 273 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(273) );
	
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
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(290, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(290) );
	
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
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(287, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(287) );
	
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
	if ( m_toEnum.find( 281 ) != m_toEnum.end() )
	{
		vgLogDebug("(281, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(281, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 281 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(281) );
	
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
	if ( m_toEnum.find( 283 ) != m_toEnum.end() )
	{
		vgLogDebug("(283, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(283, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 283 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(283) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 288 ) != m_toEnum.end() )
	{
		vgLogDebug("(288, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(288, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 288 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(288) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 289 ) != m_toEnum.end() )
	{
		vgLogDebug("(289, FilterValueType) already in m_toEnum enum registry");
		assert( false && "(289, FilterValueType) already in registry" );
	}
	#endif

	m_toEnum[ 289 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(289) );
	
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, FilterParameterType) already in m_toEnum enum registry");
		assert( false && "(285, FilterParameterType) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::Texture::FilterParameterType(285) );
	
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
	if ( m_toEnum.find( 282 ) != m_toEnum.end() )
	{
		vgLogDebug("(282, WrapValueType) already in m_toEnum enum registry");
		assert( false && "(282, WrapValueType) already in registry" );
	}
	#endif

	m_toEnum[ 282 ] = vgd::makeShp( new vgd::node::Texture::WrapValueType(282) );
	
}



} // namespace node

} // namespace vgd
