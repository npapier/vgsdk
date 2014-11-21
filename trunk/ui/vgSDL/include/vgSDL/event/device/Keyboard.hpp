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
	* @brief	Searches for a keyboard at the given index.
	*
	* @param	index	an index for a keyboard
	*
	* @return	a shared pointer to a keyboard, empty if none
	*/
	static vgd::Shp< Keyboard > find(const int index);

	/**
	* @brief	Retrieves the keyboard with the given index, or create
	* 			one if none exists.
	*
	*
	* @param	index	an index for a keyboard
	*
	* @return	a shared pointer to a keyboard, empty on error
	*
	* @see		getNames, find
	*/
	static vgd::Shp< Keyboard > get(const int index);

private:

	/**
	* @brief Constructor
	*
	* @param identifier	the device identifier
	*/
	Keyboard(const uint identifier = 0);

	typedef std::vector< vgd::Wkp< Keyboard >  >	KeyboardCollection;

	/**
	* @brief The collection of keyboard already in use.
	*/
	static KeyboardCollection	m_keyboardCache;

};

} // namespace device
} // namespace event
} // namespace vgSDL


#endif // _VGSDL_EVENT_DEVICE_KEYBOARD_HPP_
