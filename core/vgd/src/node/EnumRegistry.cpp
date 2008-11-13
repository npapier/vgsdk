// VGSDK - Copyright (C) 2008, Nicolas Papier.
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
		vgLogDebug("(256, ON) already in enum registry");
		assert( false && "(256, ON) already in registry" );
	}
	#endif

	m_toString[ 256 ] = std::string("ON");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 261 ) != m_toString.end() )
	{
		vgLogDebug("(261, CCW) already in enum registry");
		assert( false && "(261, CCW) already in registry" );
	}
	#endif

	m_toString[ 261 ] = std::string("CCW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, EMISSION) already in enum registry");
		assert( false && "(266, EMISSION) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("EMISSION");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 258 ) != m_toString.end() )
	{
		vgLogDebug("(258, BACK) already in enum registry");
		assert( false && "(258, BACK) already in registry" );
	}
	#endif

	m_toString[ 258 ] = std::string("BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 260 ) != m_toString.end() )
	{
		vgLogDebug("(260, FRONT_AND_BACK) already in enum registry");
		assert( false && "(260, FRONT_AND_BACK) already in registry" );
	}
	#endif

	m_toString[ 260 ] = std::string("FRONT_AND_BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 257 ) != m_toString.end() )
	{
		vgLogDebug("(257, DISABLED) already in enum registry");
		assert( false && "(257, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 257 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, SHININESS) already in enum registry");
		assert( false && "(267, SHININESS) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("SHININESS");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, SPECULAR) already in enum registry");
		assert( false && "(265, SPECULAR) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("SPECULAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, AMBIENT) already in enum registry");
		assert( false && "(263, AMBIENT) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("AMBIENT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 259 ) != m_toString.end() )
	{
		vgLogDebug("(259, FRONT) already in enum registry");
		assert( false && "(259, FRONT) already in registry" );
	}
	#endif

	m_toString[ 259 ] = std::string("FRONT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, CW) already in enum registry");
		assert( false && "(262, CW) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("CW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, DIFFUSE) already in enum registry");
		assert( false && "(264, DIFFUSE) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("DIFFUSE");

}



} // namespace node

} // namespace vgd
