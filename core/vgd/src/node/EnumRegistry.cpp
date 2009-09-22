// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/EnumRegistry.hpp"

#include <vgDebug/convenience.hpp>



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



EnumRegistry::ToStringType EnumRegistry::m_toString;



void EnumRegistry::initialize()
{
	//
	#ifdef _DEBUG
	if ( m_toString.find( 256 ) != m_toString.end() )
	{
		vgLogDebug("(256, DISABLED) already in enum registry");
		assert( false && "(256, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 256 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 260 ) != m_toString.end() )
	{
		vgLogDebug("(260, CCW) already in enum registry");
		assert( false && "(260, CCW) already in registry" );
	}
	#endif

	m_toString[ 260 ] = std::string("CCW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, LIGHTING_OFF) already in enum registry");
		assert( false && "(262, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("LIGHTING_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, AT_EYE) already in enum registry");
		assert( false && "(266, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("AT_EYE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, AT_INFINITY) already in enum registry");
		assert( false && "(265, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("AT_INFINITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 258 ) != m_toString.end() )
	{
		vgLogDebug("(258, FRONT) already in enum registry");
		assert( false && "(258, FRONT) already in registry" );
	}
	#endif

	m_toString[ 258 ] = std::string("FRONT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 259 ) != m_toString.end() )
	{
		vgLogDebug("(259, FRONT_AND_BACK) already in enum registry");
		assert( false && "(259, FRONT_AND_BACK) already in registry" );
	}
	#endif

	m_toString[ 259 ] = std::string("FRONT_AND_BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 261 ) != m_toString.end() )
	{
		vgLogDebug("(261, CW) already in enum registry");
		assert( false && "(261, CW) already in registry" );
	}
	#endif

	m_toString[ 261 ] = std::string("CW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 268 ) != m_toString.end() )
	{
		vgLogDebug("(268, SHADOW_MAPPING) already in enum registry");
		assert( false && "(268, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toString[ 268 ] = std::string("SHADOW_MAPPING");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, STANDARD_PER_VERTEX) already in enum registry");
		assert( false && "(263, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("STANDARD_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, STANDARD_PER_PIXEL) already in enum registry");
		assert( false && "(264, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("STANDARD_PER_PIXEL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, NONE) already in enum registry");
		assert( false && "(267, NONE) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 257 ) != m_toString.end() )
	{
		vgLogDebug("(257, BACK) already in enum registry");
		assert( false && "(257, BACK) already in registry" );
	}
	#endif

	m_toString[ 257 ] = std::string("BACK");

}



} // namespace node

} // namespace vgd
