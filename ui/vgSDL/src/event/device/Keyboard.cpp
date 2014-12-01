// VGSDK - Copyright (C) 2012, 2013, 2014 Guillaume Brocker, Bryan Schuller, Nicolas Papier, Philippe Sengchanpheng.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Philippe Sengchanpheng

#include "vgSDL/event/device/Keyboard.hpp"
#include "vgSDL/event/helpers.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/Shp.hpp>

#include <SDL_events.h>
#include <SDL_keyboard.h>

namespace vgSDL
{

namespace event
{

namespace device
{

vgd::Shp<Keyboard>	Keyboard::m_keyboard;

Keyboard::Keyboard(const uint identifier)
	: ::vgd::event::device::Keyboard(identifier)
{
	//EventHandler::connect(this);
}


Keyboard::~Keyboard()
{
	//EventHandler::disconnect(this);
}


void Keyboard::handleEvent(const SDL_Event & event)
{
	vgd::Shp<Keyboard> keyboard = get();

	if (!keyboard)
		return;

	// Skips processing if the event is not related to the keyboard.
	if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP && event.type != SDL_TEXTINPUT)
	{
		return;
	}

	// Update global button states
	updateGlobalButtonStates(&event);

	// Retrieves the effective event object.
	SDL_KeyboardEvent	 keyEvent = event.key;

	switch (keyEvent.type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		//case SDL_TEXTINPUT:
		{
			using vgd::event::KeyboardButtonEvent;

			KeyboardButtonEvent	* keyboardEvent = 0;

			keyboardEvent = new KeyboardButtonEvent(
				keyboard.get(),
				vgd::event::detail::GlobalButtonStateSet::get(),
				getKeyboardButton(&event),
				getButtonState(&event)
				);

			keyboard->fireEvent(vgd::makeShp(keyboardEvent));
			break;
		}
		default:
			assert(false);
	}
}




vgd::Shp< Keyboard > Keyboard::get()
{
	if (!m_keyboard)
	{
		m_keyboard = vgd::makeShp(new Keyboard());
	}
	return m_keyboard;
}

} // namespace device
} // namespace event
} // namespace vgSDL
