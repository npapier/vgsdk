// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

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
	 * @brief	Defines the location vector type.
	 */
	typedef vgm::Vec2f Location;

	/**
	 * @brief	Defines the canvas size type.
	 */
	typedef vgm::Vec2f Size;

	/**
	 * @brief	Constructor.
	 * 
	 * @param	location			a location to pass through the event
	 * @param	size				the size of the 'canvas' where Location2event occurs
	 */
	Location2( const Location& location, const Size& size );
	
	/**
	 * @brief	Destructor.
	 */
	virtual ~Location2();
	
	/**
	 * @brief	Retrieves the location passed through the event.
	 * 
	 * @return	a location
	 */
	const Location& getLocation() const;
	
	/**
	 * @brief	Retrieves the 'canvas size' passed through the event.
	 * 
	 * @return	a size
	 */
	const Size& getSize() const;
	
	
protected:
	/**
	 * @brief The location passed through the event.
	 */
	Location	m_location;

	/**
	 * @brief The size passed through the event.
	 */
	Size		m_size;	
};



} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_LOCATION2_HPP
