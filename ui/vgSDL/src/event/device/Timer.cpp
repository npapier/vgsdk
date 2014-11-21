// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgSDL/event/device/Timer.hpp"

#include <vgd/Shp.hpp>
#include <vgd/event/TimerEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>

#include <vgDebug/helpers.hpp>

#include <SDL.h>

namespace
{
	Uint32 onTimeout(Uint32 interval, void *param)
	{
		// Creates the event.
		using vgSDL::event::device::Timer;
		using vgd::event::TimerEvent;
		Timer* timer = static_cast<Timer *>(param);
		TimerEvent * timerEvent = new TimerEvent(timer, vgd::event::detail::GlobalButtonStateSet::get());

		// Fires the event to the listeners.
		timer->fireEvent(vgd::makeShp(timerEvent));

		// Job's done, but keep going (do not disconnect yet)
		return interval;
	}
}

namespace vgSDL
{

namespace event
{

namespace device
{

Timer::Timer()
{
	if (SDL_WasInit(SDL_INIT_TIMER) == 0)
	{
		if (SDL_Init(SDL_INIT_TIMER) != 0)
		{
			vgLogDebug("Unable to initialize SDL timer: %s\n", SDL_GetError());
			return;
		}
	}

	// Connects the slot to the Glib::signal_timeout()
	uint32 freq;

#ifdef _DEBUG
	freq = 1000 / 15;
#else
	freq = 1000 / 30;
#endif
	SDL_TimerID timer = SDL_AddTimer(freq, onTimeout, this);
}

void Timer::fireEvent(vgd::Shp<vgd::event::Event> event)
{
	vgd::event::device::Timer::fireEvent(event);
}


} // namespace device
} // namespace event
} // namespace vgSDL
