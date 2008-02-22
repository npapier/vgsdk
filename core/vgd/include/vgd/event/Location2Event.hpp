// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGD_EVENT_LOCATION2EVENT_HPP
#define _VGD_EVENT_LOCATION2EVENT_HPP

#include <vgm/Vector.hpp>

#include "vgd/vgd.hpp"
#include "vgd/event/Event.hpp"
#include "vgd/event/Location2.hpp"


namespace vgd
{

namespace event
{
	
	
	
/**
 * @brief	Defines the event class for location notifications.
 */
struct VGD_API Location2Event : public Location2, public Event
{
	/**
	 * @brief	Defines the difference of two location type.
	 */
	typedef vgm::Vec2f LocationDelta;

	/**
	 * @brief	Constructor.
	 * 
	 * @param	source				a pointer to event source
	 * @param	buttonStates		a reference to the button state set
	 * @param	location			a location to pass through the event
	 * @param	previousLocation	the previous location. If there is no previous location, initialize each vector components
	 * 								with std::numeric_limits<float>::max()
	 * @param	size				the size of the 'canvas' where Location2event occurs
	 */
	Location2Event( Source *source, const ButtonStateSet& buttonStates, const Location& location, const Location& previousLocation, const Size& size );
	
	/**
	 * @brief	Destructor.
	 */
	virtual ~Location2Event();
	
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
	

	// overridden method
	void accept( vgd::event::EventVisitor& eventVisitor );	


private:

	/**
	 * @brief The previous location passed through the event.
	 */
	Location m_previous;	
};



} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_LOCATION2EVENT_HPP
