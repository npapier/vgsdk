// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGD_EVENT_LOCATION2EVENT_HPP
#define _VGD_EVENT_LOCATION2EVENT_HPP

#include <vgm/Vector.hpp>

#include "vgd/vgd.hpp"
#include "vgd/event/Event.hpp"


namespace vgd
{

namespace event
{
	
	
/**
 * @brief	Defines the event class for location notifications.
 */
struct VGD_API Location2Event : public Event
{
	/**
	 * @brief	Defines the location vector type.
	 */
	typedef vgm::Vec2f Location;

	/**
	 * @brief	Defines the difference of two location type.
	 */
	typedef vgm::Vec2f LocationDelta;
		
	/**
	 * @brief	Defines the canvas size type.
	 */
	typedef vgm::Vec2f Size;

	/**
	 * @brief	Constructor.
	 * 
	 * @param	source				a pointer to event source
	 * @param	location				a location to pass through the event
	 * @param	previousLocation	the previous location. If there is no previous location, initialize each vector components
	 * 									with std::numeric_limits<float>::max()
	 * @param	size					the size of the 'canvas' where location2event occurs
	 */
	Location2Event( Source *source, const Location& location, const Location& previousLocation, const Size& size );
	
	/**
	 * @brief	Destructor.
	 */
	virtual ~Location2Event();
	
	/**
	 * @brief	Retrieves the location passed through the event.
	 * 
	 * @return	a location
	 */
	const Location& getLocation() const;
	
	/**
	 * @brief	Retrives the previous location
	 * 
	 * @return	the previous location
	 */
	const Location& getPreviousLocation() const;
	
	/**
	 * @brief	Retrives the difference between the current location and the previous location
	 * 
	 * @return	the delta
	 * 
	 * @remarks Returns LocationDelta(0,0) if there is no previous location.
	 */
	const LocationDelta getDelta() const;
	
	/**
	 * @brief	Retrieves the size passed through the event.
	 * 
	 * @return	a size
	 */
	const Size& getSize() const;
	
private:

	/**
	 * The location passed through the event.
	 */
	const Location m_location;
	
	/**
	 * The previous location passed through the event.
	 */
	const Location m_previous;	
	
	/**
	 * The size passed through the event.
	 */
	const Size		m_size;	
};


} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_LOCATION2EVENT_HPP
