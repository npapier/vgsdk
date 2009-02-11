// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_LISTENER_HPP
#define _VGD_EVENT_LISTENER_HPP

#include "vgd/vgd.hpp"

namespace vgd
{
	template<class T> struct Shp;

	namespace event
	{
		struct Event;
	}
}



namespace vgd
{

namespace event
{

/**
 * @brief	Defines the abstract interface for objects that can receive events.
 * 
 * Objects of this class must be attached to a event Source to get notified on
 * new events.
 * 
 * @see	vgd::event::Source
 */
struct VGD_API Listener
{
	/**
	 * @brief Virtual destructor
	 */
	virtual ~Listener();

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
