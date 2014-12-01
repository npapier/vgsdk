// VGSDK - Copyright (C) 2014 Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Philippe Sengchanpheng

#ifndef _VGSDL_EVENT_DEVICE_KEYBOARD_HPP_
#define _VGSDL_EVENT_DEVICE_KEYBOARD_HPP_

#include <vgd/Wkp.hpp>
#include <vgd/event/device/Keyboard.hpp>

#include "vgSDL/vgSDL.hpp"

#include <vector>

union SDL_Event;

namespace vgSDL
{

namespace event
{

namespace device
{

/**
 * @brief	Implements a keyboard event device for SDL.
 *
 */
struct VGSDL_API Keyboard : public vgd::event::device::Keyboard
{
	/**
	* @brief Destructor.
	*/
	~Keyboard();

	/**
	* @name	SDL Event Handling
	*
	* @remark	Will skip \c tab key events to avoid inconsistancy problems due to the lost of the focus.
	*/
	//@{
	static void handleEvent(const SDL_Event & event);
	//@}

	/**
	* @brief	Retrieves the keyboard with the given index, or create
	* 			one if none exists.
	*
	*
	* @return	a shared pointer to a keyboard, empty on error
	*
	*/
	static vgd::Shp< Keyboard > get();

private:

	/**
	* @brief Constructor
	*
	* @param identifier	the device identifier
	*/
	Keyboard(const uint identifier = 0);

	/**
	* @brief The keyboard in use.
	*/
	static vgd::Shp<Keyboard>	m_keyboard;

};

} // namespace device
} // namespace event
} // namespace vgSDL


#endif // _VGSDL_EVENT_DEVICE_KEYBOARD_HPP_
