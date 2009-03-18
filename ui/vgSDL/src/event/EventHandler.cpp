// VGSDK - Copyright (C) 2009, Clement Forest and Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Nicolas Papier

#include "vgSDL/event/EventHandler.hpp"

#include <SDL_version.h>
#include "vgSDL/event/device/Mouse.hpp"
#include "vgSDL/event/device/Joystick.hpp"



namespace vgSDL
{

namespace event
{


vgd::Shp<EventHandler> EventHandler::g_instance;

EventHandler::EventHandler()
:	m_events( new SDL_Event[ MAX_SDL_EVENTS ] ),
	m_nbEvents( 0 )
{
	// Init SDL
	SDL_Init( SDL_INIT_JOYSTICK | SDL_INIT_VIDEO );
#if SDL_MINOR_VERSION == 3 // SDL 1.3
	SDL_WindowID id = SDL_CreateWindow("SDL",0,0,0,0,0);
#else // SDL 1.2
	SDL_CreateRGBSurface(0,0,0,0,0,0,0,0);
#endif
	SDL_JoystickEventState(SDL_ENABLE);
}


EventHandler::~EventHandler()
{
	if ( m_events != 0 )
	{
		delete [] m_events;
	}
}


bool EventHandler::getEvents(int eventMask)
{
	if(!g_instance)
		g_instance.reset(new EventHandler);
	if(eventMask == -1)
		eventMask = SDL_ALLEVENTS;
	if(eventMask&SDL_JOYEVENTMASK)
	{
		SDL_JoystickUpdate();
	}
	g_instance->m_nbEvents = SDL_PeepEvents(g_instance->m_events, 10, SDL_GETEVENT, eventMask);
	return (g_instance->m_nbEvents>0);
}

void EventHandler::dispatchEvents()
{
	using ::vgSDL::event::device::Joystick;
	using ::vgSDL::event::device::Mouse;

	if(!g_instance)
		g_instance.reset(new EventHandler);
	for(int i=0;i<g_instance->m_nbEvents;++i)
	{
		switch( g_instance->m_events[i].type )
		{
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			Joystick::handleEvent( g_instance->m_events[i].jbutton );
			break;
	
		case SDL_JOYAXISMOTION:
			Joystick::handleEvent( g_instance->m_events[i].jaxis );
			break;

		case SDL_JOYHATMOTION:
			Joystick::handleEvent( g_instance->m_events[i].jhat );
			break;
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			Mouse::handleEvent(g_instance->m_events[i]);
			break;
		}
	}

	if(g_instance->m_nbEvents!=0)
	{
		g_instance->m_nbEvents=0;
	}
}

const uint EventHandler::MAX_SDL_EVENTS = 20;

} // namespace event

} // namespace vgSDL
