// VGSDK - Copyright (C) 2009, Nicolas Papier.
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
		vgLogDebug("(265, AT_INFINITY) already in m_toString enum registry");
		assert( false && "(265, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("AT_INFINITY");

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
	if ( m_toString.find( 256 ) != m_toString.end() )
	{
		vgLogDebug("(256, DISABLED) already in m_toString enum registry");
		assert( false && "(256, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 256 ] = std::string("DISABLED");

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
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, AT_EYE) already in m_toString enum registry");
		assert( false && "(266, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("AT_EYE");

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
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, LIGHTING_OFF) already in m_toString enum registry");
		assert( false && "(262, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("LIGHTING_OFF");

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
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, NONE) already in m_toString enum registry");
		assert( false && "(267, NONE) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("NONE");

	// Initializes m_toEnum map

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
	if ( m_toEnum.find( 261 ) != m_toEnum.end() )
	{
		vgLogDebug("(261, OrientationValueType) already in m_toEnum enum registry");
		assert( false && "(261, OrientationValueType) already in registry" );
	}
	#endif

	m_toEnum[ 261 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(261) );
	
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
	if ( m_toEnum.find( 256 ) != m_toEnum.end() )
	{
		vgLogDebug("(256, ModeValueType) already in m_toEnum enum registry");
		assert( false && "(256, ModeValueType) already in registry" );
	}
	#endif

	m_toEnum[ 256 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(256) );
	
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
	if ( m_toEnum.find( 266 ) != m_toEnum.end() )
	{
		vgLogDebug("(266, ViewerValueType) already in m_toEnum enum registry");
		assert( false && "(266, ViewerValueType) already in registry" );
	}
	#endif

	m_toEnum[ 266 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(266) );
	
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
	if ( m_toEnum.find( 262 ) != m_toEnum.end() )
	{
		vgLogDebug("(262, ModelValueType) already in m_toEnum enum registry");
		assert( false && "(262, ModelValueType) already in registry" );
	}
	#endif

	m_toEnum[ 262 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(262) );
	
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
	if ( m_toEnum.find( 267 ) != m_toEnum.end() )
	{
		vgLogDebug("(267, ShadowValueType) already in m_toEnum enum registry");
		assert( false && "(267, ShadowValueType) already in registry" );
	}
	#endif

	m_toEnum[ 267 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(267) );
	
}



} // namespace node

} // namespace vgd
