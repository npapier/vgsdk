#ifndef _VGSDL_EVENT_EVENTHANDLER_HPP_
#define _VGSDL_EVENT_EVENTHANDLER_HPP_

#include <vgSDL/vgSDL.hpp>

#include <vgd/Shp.hpp>
#include <list>

namespace vgd { namespace event {
struct Device;
} }


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
	 * @brief Get events.
	 */

	static bool getEvents();

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

};
} // namespace event
} // namespace vgSDL


#endif // _VGSDL_EVENT_EVENTHANDLER_HPP_
