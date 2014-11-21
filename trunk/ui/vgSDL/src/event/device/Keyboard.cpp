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
	vgd::Shp<Keyboard> keyboard = find(event.key.which);

	if (!keyboard)
		return;

	// Skips processing if the event is not related to the keyboard.
	if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
	{
		return;
	}

	// Retrieves the effective event object.
	SDL_KeyboardEvent	 keyEvent = event.key;

	switch (keyEvent.type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			using vgd::event::KeyboardButtonEvent;

			KeyboardButtonEvent	* keyboardEvent = 0;

			keyboardEvent = new KeyboardButtonEvent(
				keyboard.get(),
				vgd::event::detail::GlobalButtonStateSet::get(),
				getKeyboardButton(&keyEvent),
				getButtonState(&keyEvent)
				);

			keyboard->fireEvent(vgd::makeShp(keyboardEvent));
			break;
		}
		default:
			assert(false);
	}
}


Keyboard::KeyboardCollection	Keyboard::m_keyboardCache;



vgd::Shp< Keyboard > Keyboard::find(const int index)
{
	assert(index >= 0);

	return (static_cast<size_t>(index) < m_keyboardCache.size()) ? m_keyboardCache[index].lock() : vgd::Shp< Keyboard >();
}



vgd::Shp< Keyboard > Keyboard::get(const int index)
{
	assert(index >= 0);

	// Adjusts the cache size to the number of keyboards.
	m_keyboardCache.resize(1);

	// Let's look for a joystick in the cache.
	vgd::Shp< Keyboard >	result = find(index);

	if (!result && (index<(int)m_keyboardCache.size()))
	{
		result = vgd::makeShp(new Keyboard(index));

		if (result)
		{
			m_keyboardCache[index] = result;
		}
	}
	return result;
}

} // namespace device
} // namespace event
} // namespace vgSDL
