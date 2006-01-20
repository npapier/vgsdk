// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_LISTENER_HPP
#define _VGD_EVENT_LISTENER_HPP


#include "vgd/vgd.hpp"
#include "vgd/Shp.hpp"
#include "vgd/event/Event.hpp"


namespace vgd
{
	
namespace event
{
	
/**
 * @brief	Defines the abstract interface for objects that can receive events.
 * 
 * Objects of this class must be attached to a event source to get notified on
 * new events.
 * 
 * @see	::vgd::event::source
 */
struct VGD_API Listener
{
	/**
	 * @brief	Notifies the listener about the raise of an event.
	 * 
	 * @param	event	a shared pointer to the raised event
	 */
	virtual void onEvent( vgd::Shp<vgd::event::Event> event ) = 0;
};
	
} // namespace event
	
} // namespace vgd

#endif // _VGD_EVENT_LISTENER_HPP
