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



Enum::Enum( const Enum& o )
: m_value( o.m_value )
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



const bool Enum::operator <= ( const Enum& other ) const
{
	return value() <= other.value();
}



const bool Enum::operator > ( const Enum& other ) const
{
	return value() > other.value();
}



const bool Enum::operator >= ( const Enum& other ) const
{
	return value() >= other.value();
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



const std::vector< std::pair< int, std::string> > Enum::valuesAndStrings() const
{
	std::vector< std::pair< int, std::string> > retVal;

	const std::vector< int >			allValues(	values()	);
	const std::vector< std::string >	allStrings(	strings()	);
	assert( allValues.size() == allStrings.size() && "values() and strings() must returned vector<> with the same size." );

	retVal.reserve( allValues.size() );

	for( uint i = 0; i < allValues.size(); ++i )
	{
		retVal.push_back( std::make_pair( allValues[i], allStrings[i] ) );
	}

	return retVal;
}



const std::vector< int > Enum::values() const
{
	std::vector< int > retVal;

	assert( false && "This method should be overriden." );

	return retVal;
}



const std::vector< std::string > Enum::strings() const
{
	std::vector< std::string > retVal;

	assert( false && "This method should be overriden." );

	return retVal;
}



const bool Enum::isValid() const
{
	return value() != std::numeric_limits<int>::min();
}



} // namespace field

} // namespace vgd
