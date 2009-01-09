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

	/**
	 * @brief attach device.
	 * @return true if the device could be registered.
	 */

	static bool connect(vgd::event::Device* );

	/**
	 * @brief dettach device.
	 */

	static void disconnect(vgd::event::Device* );

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
	 * @brief list of Mice.
	 */
	std::list<Mouse*> m_mice;

	/**
	 * @brief list of Joystick.
	 */
	//std::list<Joystick*> m_joysticks;


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
