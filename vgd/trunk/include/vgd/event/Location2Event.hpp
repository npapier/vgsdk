// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker


#ifndef _VGD_EVENT_LOCATION2EVENT_HPP
#define _VGD_EVENT_LOCATION2EVENT_HPP


#include "vgd/event/Event.hpp"
#include <vgm/Vector.hpp>


namespace vgd
{

namespace event
{
	
	
/**
 * @brief	Defines the event class for location notifications.
 */
class Location2Event : public Event
{
public:

	/**
	 * @brief	Defines the location vector type.
	 */
	typedef vgm::Vector<unsigned int, 2> Location;

	/**
	 * @brief	Constructor.
	 * 
	 * @param	source		a pointer to event source
	 * @param	location	a location to pass through the event
	 */
	Location2Event( Source *source, const Location& location );
	
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
	
private:

	/**
	 * The location passed through the event.
	 */
	const Location m_location;
};


} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_LOCATION2EVENT_HPP
