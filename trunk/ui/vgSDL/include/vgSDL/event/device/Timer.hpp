// VGSDK - Copyright (C) 2012, 2014 Guillaume Brocker, Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Philippe Sengchanpheng

#ifndef _VGSDL_EVENT_DEVICE_TIMER_HPP_
#define _VGSDL_EVENT_DEVICE_TIMER_HPP_

#include <vgd/event/device/Timer.hpp>

#include "vgSDL/vgSDL.hpp"

#include <SDL_timer.h>

namespace vgSDL
{

namespace event
{

namespace device
{

struct VGSDL_API Timer :public vgd::event::device::Timer
{
	/**
	 * @brief	Constructor
	 */
	Timer();
	void fireEvent(vgd::Shp<vgd::event::Event> event);
};

} // namespace device
} // namespace event
} // namespace vgSDL


#endif // _VGSDL_EVENT_DEVICE_TIMER_HPP_
