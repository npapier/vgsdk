// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_OPERATIONS_HPP
#define _VGM_OPERATIONS_HPP

//#include "vgm/vgm.hpp"

#include <algorithm>



namespace vgm
{

/**
 * @brief Returns the clamped x
 * 
 * @param x				value to be clamped
 * @param minVal		minimum value
 * @param maxVal		maximum value
 * 
 * @return  the value min (max (x, minVal), maxVal)
 */
template< typename T >
const T clamp( T x, T minVal, T maxVal )
{
	const T retVal = std::min( std::max( x, minVal ), maxVal );
	
	return retVal;
}



} // namespace vgm

#endif // #ifndef _VGM_OPERATIONS_HPP
