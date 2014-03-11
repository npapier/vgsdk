// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/toString.hpp"



namespace vgd
{

namespace basic
{



template<>
const std::string toString( const int8& value )
{
	const std::string retVal = boost::lexical_cast< std::string >( static_cast<int>(value) );
	return retVal;
}

template<>
const std::string toString( const uint8& value )
{
	const std::string retVal = boost::lexical_cast< std::string >( static_cast<uint>(value) );
	return retVal;
}



} // namespace basic

} // namespace vgd
