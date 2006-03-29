// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_MINMAX_HPP
#define _VGD_BASIC_MINMAX_HPP

#include "vgd/vgd.hpp"

#include <limits>



namespace vgd
{
	
namespace basic
{

/**
 * @brief Could be used to store two values (a minimum and a maximum).
 */
struct VGD_API MinMax
{
	/**
	 * @brief Default constructor
	 * 
	 * @post isValid() == false
	 */
	MinMax();

	/**
	 * @brief Constructor
	 * 
	 * @pre min <= max
	 */
	MinMax( const float min, const float max );

	/**
	 * @brief Returns if the (min,max) pair is valid
	 * 
	 * @return true if valid, false otherwise.
	 */
	const bool isValid() const;

	/**
	 * @brief Invalidates the (min,max) pair
	 * 
	 * @post isValid() == false
	 */
	void invalidate();

	/**
	 * @brief Gets the minimum.
	 * 
	 * @return the minimum value
	 */
	const float getMin() const;
	
	/**
	 * @brief Sets the minimum.
	 * 
	 * @param minimum	the minimum value
	 * 
	 * @pre min <= getMax()
	 */
	void setMin( const float min );

	/**
	 * @brief Gets the maximum.
	 * 
	 * @return the maximum value
	 */
	const float getMax() const;

	/**
	 * @brief Sets the maximum.
	 * 
	 * @param maximum	the maximum value
	 * 
	 * @pre getMin() <= max
	 */
	void setMax( const float max );
	
	/**
	 * @brief Sets the minimum and maximum values.
	 * 
	 * @param minimum	the minimum value
	 * @param maximum	the maximum value
	 * 
	 * @pre min <= max
	 */
	void set( const float min, const float max );
	 
	/**
	 * @brief Returns the difference between maximum and minimum.
	 * 
	 * @pre isValid()
	 * 
	 * @return the difference between maximum and minimum
	 */
	const float getDelta() const;

private:
	float m_min;
	float m_max;
};


} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_MINMAX_HPP
