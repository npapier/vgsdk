// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/field/Enum.hpp"

#include <limits>
#include "vgd/node/EnumRegistry.hpp"



namespace vgd
{

namespace field
{



Enum::Enum()
: m_value( std::numeric_limits<int>::min() )
{
}



Enum::Enum( const int v )
: m_value(v)
{
}



Enum& Enum::operator = ( const Enum& other )
{
	if ( this != &other )
	{
		m_value = other.m_value;
	}

	return (*this);
}



const bool Enum::operator < ( const Enum& other ) const
{
	return value() < other.value();
}



const bool Enum::operator ==( const Enum& other ) const
{
	return value() == other.value();
}



const bool Enum::operator !=( const Enum& other ) const
{
	return value() != other.value();
}



const int Enum::value() const
{
	return m_value;
}



const std::string Enum::str() const
{
	assert( isValid() );

	const std::string enumString = vgd::node::EnumRegistry::toString( value() );

	return enumString;
}



const bool Enum::isValid() const
{
	return value() != std::numeric_limits<int>::min();
}



} // namespace field

} // namespace vgd
