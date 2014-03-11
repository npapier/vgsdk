// VGSDK - Copyright (C) 2009, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest

#ifndef _VGSDL_EVENT_EVENTHANDLER_HPP_
#define _VGSDL_EVENT_EVENTHANDLER_HPP_

#include <list>
#include <vgd/Shp.hpp>

#include "vgSDL/vgSDL.hpp"


namespace vgd { namespace event { struct Device; } }

union SDL_Event;



namespace vgSDL
{
namespace event
{

struct Mouse;
struct Joystick;


/**
 * @brief SDL event handler.
 */
struct VGSDL_API EventHandler
{
	/**
	 * @brief Destructor.
	 */
	~EventHandler();

	/**
	 * @brief Get events.
	 * @param eventMask the SDL_EVENTMASK we want to retrieve (default = SDL_ALLEVENTS)
	 */
	static bool getEvents(int eventMask = -1);

	/**
	 * @brief Dispatch events
	 */
	static void dispatchEvents();


private:

	/**
	 * @brief Creator.
	 */
	EventHandler();

	/**
	 * @brief Singleton.
	 */
	static vgd::Shp <EventHandler> g_instance;

	/**
	 * @brief List of events.
	 */
	SDL_Event* m_events;

	/**
	 * @brief Number of events.
	 */
	int m_nbEvents;

	/**
	 * @brief Maximum number of event in m_events
	 */
	static const uint MAX_SDL_EVENTS;
};

} // namespace event

} // namespace vgSDL

#endif // _VGSDL_EVENT_EVENTHANDLER_HPP_
