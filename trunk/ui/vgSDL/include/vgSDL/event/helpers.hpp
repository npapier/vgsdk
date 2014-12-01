// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller, Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Philippe Sengchanpheng

#ifndef _VSDL_EVENT_HELPERS_HPP_
#define _VSDL_EVENT_HELPERS_HPP_

#include <vgd/event/device/Keyboard.hpp>
#include <vgd/event/ButtonEvent.hpp>
#include <vgd/event/Location2.hpp>

#include <SDL_events.h>
struct SDL_KeyboardEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;

namespace vgSDL
{

namespace event
{

// keyboard
/**
 * @brief	Retrieves the vgSDK keyboard button identifier from the given SDL_KeyboardEvent.
 *
 * @param	event a pointer to a SDL Key event.
 *
 * @return	a vgSDK keyboard button.
 *
 * @see		vgd::event::KeyboardButtonEvent.
 */
	const int getKeyboardButton(const SDL_Event * event);

/**
 * @brief	Helper that retrieves the vgSDK button state from the given SDL_KeyboardEvent.
 *
 * @param	event	a pointer to a SDL Key event.
 *
 * @return	the vgSDK button state.
 */
	const ::vgd::event::ButtonEvent::State getButtonState(const SDL_Event * event);


/**
 * @brief	Helps to update the global button state for a given SDL_KeyboardEvent notification.
 *
 * @param	event	a pointer to an event.
 */
	void updateGlobalButtonStates(const SDL_Event * event);

/**
* @brief	Helper that retrieves the vgSDK mouse button identifier from the given SDL button event
*
* @param	event	a pointer to a SDL button event
*
* @return	the vgSDK button identifier
*/
const uint32 getButtonId(const SDL_MouseButtonEvent * event);



/**
* @brief	Helper that retrieves the vgSDK button state from the given SDL button event
*
* @param	event	a pointer to a SDL button event
*
* @return	the vgSDK button state
*/
const ::vgd::event::ButtonEvent::State getButtonState(const SDL_MouseButtonEvent * event);



/**
* @brief	Helps to update the global button state for a given @c SDL_MouseButtonEvent notification.
*
* @param	event	a pointer to an event
*/
void updateGlobalButtonStates(const SDL_MouseButtonEvent * event);



/**
* @brief	Helps to update the global button state for a given @c SDL_KeyboardEvent notification.
*
* @param	event	a pointer to an event
*/
void updateGlobalButtonStates(const SDL_KeyboardEvent * event);


/**
* @brief	Helper that retrieves the size of the surface (or window) for the given QWidget.
*
* @return	the vgSDK size.
*/
const ::vgd::event::Location2::Size getSize();

/**
* @brief	Helper that retrieves the location of the mouse for the given Qt mouse event.
*
* @remark	The location's coordinate system is translated so the origin is located in the bottom left
* 			corner of the window.
*
* @param	event	a pointer to a SDL mouse motion event.
*
* @return	the vgSDK location.
*/
const ::vgd::event::Location2::Location getLocation(const SDL_MouseMotionEvent * event);

/**
* @brief	Helper that retrieves the location of the mouse for the given Qt mouse event.
*
* @remark	The location's coordinate system is translated so the origin is located in the bottom left
* 			corner of the window.
*
* @param	event	a pointer to a SDL mouse button event.
*
* @return	the vgSDK location.
*/
const ::vgd::event::Location2::Location getLocation(const SDL_MouseButtonEvent * event);

} // namespace event
} // namespace vgSDL

#endif // _VSDL_EVENT_HELPERS_HPP_
