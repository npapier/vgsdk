// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_UTILITIES_H
#define _VGM_UTILITIES_H

#include "vgm/vgm.hpp"



namespace vgm
{



/**
 * @brief Some useful utility methods.
 * 
 * @ingroup vgmGroup
 */
struct Utilities
{
	/**
	 * @brief Returns the next power of 2 for non power of 2 number, otherwise returns the same value.
	 *
	 * @param	num : a number.
	 * @return	the next power of 2 for non power of 2 number, otherwise returns the same value.
	 *
	 */
	VGM_API static int32 nextPower2( const int32 num );

	/**
	 * @brief Transform angle in degrees to angle in radians.
	 *
	 * @param	deg		angle in degrees.
	 * @return	angle in radians.
	 */
	VGM_API static float deg2rad( const float deg );

	/**
	 * @brief Transform angle in radians to angle in degrees.
	 *
	 * @param	rad		angle in radians.
	 * @return	angle in degrees.
	 */
	VGM_API static float rad2deg( const float rad );
	
	
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
	VGM_API static const float linearInterpolation( const float x1, const float y1, const float x2, const float y2, const float x );

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
	VGM_API static void linearInterpolation(	const float x1, const float y1, const float x2, const float y2, 
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
	VGM_API static const float linearInterpolation( const float a, const float b, const float x );
	
	//@}
};



} // namespace vgm

#endif // #ifndef _VGM_UTILITIES_H
