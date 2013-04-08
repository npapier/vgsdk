// VGSDK - Copyright (C) 2006, 2010, 2011, 2012, 2013, Nicolas Papier.
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
{
	/**
	 * @brief Returns the epsilon value for T datatype.
	 * 
	 * @return epsilon value
	 */
	static const T value() //const
	{
		return static_cast<T>(0);
	}
};

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
template< typename T >
const bool equals( const T value1, const T value2, const float tolerance = vgm::Epsilon<T>::value() )
{
	const T diff = fabs( value1 - value2 );

	return diff <= tolerance;
}

/**
 * @brief Inequality comparison within tolerance
 */
template< typename T >
const bool notEquals( const T value1, const T value2, const float tolerance = vgm::Epsilon<T>::value() )
{
	const T diff = fabs( value1 - value2 );

	return diff > tolerance;
}

/**
 * @brief Returns true if value1 > value2 within tolerance
 */
template< typename T >
const bool greaterThan( const T value1, const T value2, const float tolerance = vgm::Epsilon<T>::value() )
{
	const double diff = value1 - value2;

	return diff > tolerance;
}

/**
 * @brief Returns true if value1 >= value2 within tolerance
 */
template< typename T >
const bool greaterThanEqual( const T value1, const T value2, const float tolerance = vgm::Epsilon<T>::value() )
{
	return greaterThan( value1, value2, tolerance ) || equals( value1, value2, tolerance );
}

/**
 * @brief Returns true if value1 < value2 within tolerance
 */
template< typename T >
const bool lessThan( const T value1, const T value2, const float tolerance = vgm::Epsilon<T>::value() )
{
	return greaterThan( value2, value1, tolerance );
}

/**
 * @brief Returns true if value1 <= value2 within tolerance
 */
template< typename T >
const bool lessThanEqual( const T value1, const T value2, const float tolerance = vgm::Epsilon<T>::value() )
{
	return greaterThanEqual( value2, value1, tolerance );
}

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
 * @name Degree/radians functions
 */
//@{

/**
 * @brief Transform angle in degrees to angle in radians
 *
 * @param	deg		angle in degrees
 * @return	angle in radians
 */
VGM_API const float deg2rad( const float deg );

/**
 * @brief Transform angle in radians to angle in degrees
 *
 * @param	rad		angle in radians
 * @return	angle in degrees
 */
VGM_API const float rad2deg( const float rad );

//@}



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



/**
 * @name Linear interpolation
 */
//@{

/**
 * @brief Computes a linear interpolation.
 * 
 * The coordinates (x1, y1) and (x2, y2) defines a line. This method computes points on this line with the given x.
 * 
 * @param	x1		the x-coordinate of the first point defining the line
 * @param	y1		the y-coordinate of the first point defining the line
 * @param	x2		the x-coordinate of the second point defining the line
 * @param	y2		the y-coordinate of the second point defining the line
 * @param	x		the x-coordinate of the point that must be computed
 * 
 * @return the y-coordinate of the point that must be computed
 * 
 * @pre x2-x1 != 0
 */
VGM_API const float linearInterpolation( const float x1, const float y1, const float x2, const float y2, const float x );

/**
 * @brief Computes linear equation parameters of a line.
 * 
 * The coordinates (x1, y1) and (x2, y2) defines a line. This method computes linear equation parameters (a and b)
 * of a line (y=ax+b).
 * 
 * @param	x1		the x-coordinate of the first point defining the line
 * @param	y1		the y-coordinate of the first point defining the line
 * @param	x2		the x-coordinate of the second point defining the line
 * @param	y2		the y-coordinate of the second point defining the line
 * @param	a		parameter defining the line
 * @param	b		parameter defining the line
 * 
 * @pre x2-x1 != 0
 */
VGM_API void linearInterpolation(	const float x1, const float y1, const float x2, const float y2, 
									float& a, float& b );

/**
 * @brief Computes a linear interpolation.
 * 
 * The values a and b defines a line (y=ax+b). This method computes points on this line with the given x.
 * 
 * @param	a		parameter defining the line
 * @param	b		parameter defining the line
 * @param	x		the x-coordinate of the point that must be computed
 * 
 * @return the y-coordinate of the point that must be computed
 */
VGM_API const float linearInterpolation( const float a, const float b, const float x );

//@}


} // namespace vgm

#endif // #ifndef _VGM_OPERATIONS_HPP
