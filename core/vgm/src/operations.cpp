// VGSDK - Copyright (C) 2006, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgm/operations.hpp"

#include <cmath>



namespace vgm
{


const bool equals( const float value1, const float value2 )
{
	const float diff = fabs( value1 - value2 );

	return diff <= vgm::Epsilon<float>::value();
}


const bool notEquals( const float value1, const float value2 )
{
	const float diff = fabs( value1 - value2 );

	return diff > vgm::Epsilon<float>::value();
}


const bool equals( const double value1, const double value2 )
{
	const double diff = fabs( value1 - value2 );

	return diff <= vgm::Epsilon<double>::value();
}


const bool notEquals( const double value1, const double value2 )
{
	const double diff = fabs( value1 - value2 );

	return diff > vgm::Epsilon<double>::value();
}


const double round( const double inputValue )
{
	return floor(inputValue + 0.5f);
}


const float roundf( const float inputValue )
{
	return floorf(inputValue + 0.5f);
}


} // namespace vgm
