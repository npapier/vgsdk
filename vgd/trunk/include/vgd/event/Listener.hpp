// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_LISTENER_HPP
#define _VGD_EVENT_LISTENER_HPP

#include "vgd/Shp.hpp"

namespace vgd
{
	
namespace event
{
	
class Event;
	
/**
 * @brief	Defines the abstract interface for objects that can receive events.
 * 
 * Objects of this class must be attached to a event source to get notified on
 * new events.
 * 
 * @see	::vgd::event::source
 */
class Listener
{
public:
	/**
	 * @brief	Notifies the listener about the raise of an event.
	 * 
	 * @param	event	a shared pointer to the raised event
	 */
	virtual void onEvent( vgd::Shp<Event> event ) = 0;
};
	
} // namespace event
	
} // namespace vgd

#endif // _VGD_EVENT_LISTENER_HPP
