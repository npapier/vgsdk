// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgSDL/event/event.hpp"

#include <SDL.h>

#include "vgSDL/event/Joystick.hpp"



namespace vgSDL
{

namespace event
{

namespace
{

	/**
	 * @brief	Dispatch the given SDL event to the right sub-system.
	 *
	 * @param	event	a reference to an event to displatch.
	 */
	void dispatchEvent( const SDL_Event & event )
	{
		switch( event.type )
		{
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			Joystick::handleEvent( event.jbutton );
			break;

		case SDL_JOYAXISMOTION:
			Joystick::handleEvent( event.jaxis );
			break;

		case SDL_JOYHATMOTION:
			Joystick::handleEvent( event.jhat );
			break;
		}
	}
}



const int processEvent()
{
	SDL_Event	event;
	int			result = 0;

	if( SDL_PollEvent(&event) == 1 )
	{
		dispatchEvent( event );
		result = 1;
	}
	return result;
}



const int processEvents( const int number )
{
	assert( number > 0 );

	// Retrieves events
	SDL_Event	* events = new SDL_Event[ number ];
	int			storedNumber;

	SDL_PumpEvents();
	storedNumber = SDL_PeepEvents(
			events,
			number,
			SDL_GETEVENT,
			SDL_EVENTMASK(SDL_JOYAXISMOTION) | SDL_EVENTMASK(SDL_JOYBALLMOTION) | SDL_EVENTMASK(SDL_JOYHATMOTION) | SDL_EVENTMASK(SDL_JOYBUTTONDOWN) | SDL_EVENTMASK(SDL_JOYBUTTONUP)
		);

	// Dispatch events.
	for( int i = 0; i < storedNumber; ++i )
	{
		dispatchEvent( events[i] );
	}

	// Clean-up.
	delete [] events;

	return storedNumber;
}



} // namespace event

} // namespace vgSDL
