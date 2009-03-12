// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_DEVICE_TIMER_HPP_
#define _VGGTK_EVENT_DEVICE_TIMER_HPP_

#include <vgd/event/device/Timer.hpp>

#include "vgGTK/event/SignalHandler.hpp"



namespace vgGTK
{

namespace event
{

namespace device
{



/**
 * @brief	Implements a timer event device for GTK widgets.
 *
 * @ingroup g_time
 *
 * @todo onIdle()
 */
struct VGGTK_API Timer : public ::vgd::event::device::Timer, public vgGTK::event::SignalHandler
{

	/**
	 * @name	Overrides
	 */
	//@{
	void connect( Gtk::Widget * widget );
	//@}


private:

	/**
	 * @name	GTK Signal Callbacks
	 */
	//@{
	/**
	 * @brief	Handles timeout event notifications.
	 */
	bool onTimeout( int timerNumber );
	//@}
};



} // namespace device

} // namespace event

} // namespace vgGTK



#endif // #ifndef _VGGTK_EVENT_DEVICE_TIMER_HPP_
