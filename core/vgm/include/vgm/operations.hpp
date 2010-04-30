// VGSDK - Copyright (C) 2006, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_OPERATIONS_HPP
#define _VGM_OPERATIONS_HPP

#include <algorithm>
#include "vgm/vgm.hpp"



namespace vgm
{



/**
 * @brief Tolerance for floating-point
 * 
 * Epsilon value to specify some tolerance in IEEE floating-point representation of real numbers.
 */
template< typename T >
struct Epsilon
{};

/**
 * @brief Tolerance for floating-point
 * 
 * @copydoc Epsilon
 */
template<>
struct Epsilon<float>
{
	/**
	 * @brief Returns the epsilon value for float datatype.
	 * 
	 * @return epsilon value
	 */
	static const float value() //const
	{
		return 1.e-7f;
	}
};

/**
 * @brief Tolerance for floating-point
 * 
 * @copydoc Epsilon
 */
template<>
struct Epsilon<double>
{
	/**
	 * @brief Returns the epsilon value for double datatype.
	 * 
	 * @return epsilon value
	 */	
	static const double value() //const
	{
		return 1.e-10l;
	}
};


/**
 * @name Equality comparisons within tolerance
 */
//@{ 
 
/**
 * @brief Equality comparison within tolerance
 */
VGM_API const bool equals( const float value1, const float value2 );

/**
 * @brief Inequality comparison within tolerance
 */
VGM_API const bool notEquals( const float value1, const float value2 );

/**
 * @brief Equality comparison within tolerance
 */
VGM_API const bool equals( const double value1, const double value2 );

/**
 * @brief Inequality comparison within tolerance
 */
VGM_API const bool notEquals( const double value1, const double value2 );

//@}


/**
 * @brief Returns the maximum of the parameters.
 * 
 * Compares three objects and returns the larger of the three.
 * 
 * @param first		the first object
 * @param second	the second object
 * @param third		the third object
 * 
 * @return the larger objet of the three.
 */
template< typename T >
const T max( const T first, const T second, const T third )
{
	const T firstMax	= std::max( first, second );
	const T secondMax	= std::max( firstMax, third );
	
	return secondMax;
}



/**
 * @name Rounding functions
 */
//@{

/**
 * @brief Rounds to integral value
 * 
 * @param inputValue	input value that must be rounded
 * 
 * @return the integral value nearest to inputValue rounding half-way cases away from zero, regardless of the current 
 * rounding direction.
 */
VGM_API const double round( const double inputValue );

VGM_API const float roundf( const float inputValue );

//@}



/**
 * @name GLSL like built-in functions
 */
//@{

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

//@}



} // namespace vgm

#endif // #ifndef _VGM_OPERATIONS_HPP
