// VGSDK - Copyright (C) 2009, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_EVENT_DEVICE_TIMER_HPP_
#define _VGGTK_EVENT_DEVICE_TIMER_HPP_

#include <vgd/event/device/Timer.hpp>
#include <sigc++/trackable.h>

#include "vgGTK/vgGTK.hpp"


namespace vgGTK
{

namespace event
{

namespace device
{



/**
 * @brief	Implements a timer device that will GTK's timer API to produce vgSDK timer events.
 *
 * @ingroup g_time
 *
 * @todo onIdle()
 */
struct VGGTK_API Timer : public vgd::event::device::Timer, public sigc::trackable
{
	/** 
	 * @brief	Constructor
	 */
	Timer();

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
