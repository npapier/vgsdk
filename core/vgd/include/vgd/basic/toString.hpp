// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_TOSTRING_HPP
#define _VGD_BASIC_TOSTRING_HPP

#include <boost/lexical_cast.hpp>
#include <vgBase/Type.hpp>




namespace vgd
{

namespace basic
{



/**
 * @brief Converts the given value to a string using boost::lexical_cast
 *
 * @todo a specialized version for int/uint with a []
 */
template< typename T >
const std::string toString( const T& value )
{
	const std::string retVal = boost::lexical_cast< std::string >( value );
	return retVal;
}

template<>
const std::string toString( const int8& value );

template<>
const std::string toString( const uint8& value );



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_TOSTRING_HPP
