// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BSC_TRANSFERFUNCTION_HPP
#define _VGD_BSC_TRANSFERFUNCTION_HPP

#include <map>
#include <vector>

#include "vgd/vgd.hpp"


namespace vgd
{

namespace basic
{


/**
 * @brief Defines a transfer function with a type and a set of points.
 * 
 * @remarks A transfer function is a mathematical representation of the relation between the input and output of 
 * a linear time-invariant system (from wikipedia).
 * 
 * @remarks \b Assignable and \b DefaultConstructible.
 */
struct VGD_API TransferFunction
{
	/**
	 * @brief Type of transfer function
	 */
	enum Type
	{
		IDENTITY,	/*!<The identity is the function defined by ouput = input.*/
		TABLE,		/*!<The table function is defined by the points which provides informations in order to identify n interpolation ranges.*/
		DISCRETE,	/*!<The discrete function is defined by the points in order to identify a step function consisting of n steps.*/
		//LINEAR,
		//GAMMA
	};

	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 * 
	 * @post getType() == IDENTITY
	 * @post getNumPoints() == 0
	 */
	TransferFunction();
	
	//@}
	
	
	/**
	 * @name Accessors to the type of transfer function
	 * 
	 * The type of function determines the applicability of the points set.
	 */
	//@{
	
	/**
	 * @brief Returns the type of the transfer function
	 * 
	 * @return the type of the transfer function
	 */
	const Type getType() const;
	
	/**
	 * @brief Sets the type of the transfer function.
	 * 
	 * @param type	the type of the transfer function
	 */
	void setType( const Type type );
	
	//@}
	
	
	/**
	 * @name Accessors to the points set
	 */
	//@{
	
	/**
	 * @brief Inserts a new point or updates an existing one.
	 * 
	 * @param input		x-coordinate of the new point
	 * @param output	y-coordinate of the new point
	 */
	void insertPoint( const float input, const float output );
	
	/**
	 * @brief Removes a point.
	 * 
	 * @param input		x-coordinate of the new point
	 * 
	 * @return true if the desired point has been removed, false otherwise.
	 */
	const bool removePoint( const float input );
	
	/**
	 * @brief Removes all points.
	 */
	void removePoints();
	
	/**
	 * @brief Returns the number of points
	 * 
	 * @return the number of points
	 */
	const uint32 getNumPoints() const;

	//@}
	
	
	/**
	 * @name Lookup table(LUT) related method
	 */
	//@{
	
	/**
	 * @brief Generates a lookup table.
	 * 
	 * @param lutInputBegin		the first input value of the lookup table
	 * @param lutInputEnd		the last input value of the lookup table
	 * @param lut				an empty container that would be filled by the LUT
	 * 
	 * @pre getNumPoints() >= 2
	 * @pre lut.size() == 0
	 * @pre The x-coordinates of the two extrem points must be differents.
	 */
	template< typename T >
	void getLookupTable( T& lutInputBegin, T& lutInputEnd, std::vector< T >& lut );

	//@}


private:

	/**
	 * @brief Type of the container of points defining the transfer function.
	 */
	typedef std::map< float , float > PointsContainer;
	
	/**
	 * @brief The type of transfer function
	 * 
	 * Indicates how to interpret points stored in container.
	 */
	Type				m_type;
	
	/**
	 * @brief The points defining the transfer function.
	 */
	PointsContainer		m_points;
};


} // namespace basic

} // namespace vgd

#include "vgd/basic/TransferFunction.hxx"

#endif //#ifndef _VGD_BSC_TRANSFERFUNCTION_HPP
