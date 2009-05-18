// VGSDK - Copyright (C) 2004-2006,2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_LOCATION2_HPP
#define _VGD_EVENT_LOCATION2_HPP

#include <vgm/Vector.hpp>

#include "vgd/vgd.hpp"


namespace vgd
{

namespace event
{



/**
 * @brief	Defines the class for location in 2D.
 */
struct VGD_API Location2
{
	/**
	 * @name	Type Definitions
	 */
	//@{
	typedef vgm::Vec2f Location;	///< Defines the location vector type.
	typedef vgm::Vec2f Size;		///< Defines the canvas size type.
	//@}


	/**
	 * @name	Constructors & Destructor
	 */
	//@{
	/**
	 * @brief	Constructor.
	 *
	 * @param	location	a 2D location
	 * @param	size		the size of the 'canvas' containing the location
	 */
	Location2( const Location& location, const Size & size );

	/**
	 * @brief	Constructor
	 *
	 * @param	x		the x coordinate of the location
	 * @param	y		the y coordinate of the location
	 * @param	size	the size of the 'canvas' containing the location
	 */
	Location2( const float x, const float y, const Size & size );

	/**
	 * @brief	Destructor.
	 */
	virtual ~Location2();
	//@}


	/**
	 * @brief	Retrieves the location passed through the event.
	 *
	 * @return	a location
	 */
	const Location & getLocation() const;

	/**
	 * @brief	Retrieves the 'canvas size' passed through the event.
	 *
	 * @return	a size
	 */
	const Size & getSize() const;


protected:

	Location	m_location;	///< Contains the location coordinates.
	Size		m_size;		///< Contains the size of the surface containing the location.
};



} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_LOCATION2_HPP
