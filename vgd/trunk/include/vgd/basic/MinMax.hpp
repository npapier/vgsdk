// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_MINMAX_H
#define _VGD_BASIC_MINMAX_H

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
	MinMax()
	 :	m_min( std::numeric_limits<float>::max() ),
		m_max( std::numeric_limits<float>::min() )
	{}

	/**
	 * @brief Constructor
	 */
	MinMax( const float min, const float max )
	 :	m_min( min ),
		m_max( max )
	{}

	/**
	 * @brief Returns if the (min,max) pair is valid
	 * 
	 * @return true if valid, false otherwise.
	 */
	const bool isValid() const
	{
		return (	(m_min != std::numeric_limits<float>::max()) &&
					(m_max != std::numeric_limits<float>::min())	);
	}

	/**
	 * @brief Gets the minimum.
	 * 
	 * @return the minimum value
	 */
	const float getMin() const { return ( m_min ); }
	
	/**
	 * @brief Sets the minimum.
	 * 
	 * @param minimum	the minimum value
	 */
	void setMin( const float min ) { m_min = min; }

	/**
	 * @brief Gets the maximum.
	 * 
	 * @return the maximum value
	 */
	const float getMax() const { return ( m_max ); }

	/**
	 * @brief Sets the maximum.
	 * 
	 * @param maximum	the maximum value
	 */
	void setMax( const float max ) { m_max = max; }
	
private:
	float m_min;
	float m_max;
};


} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_MINMAX_H
