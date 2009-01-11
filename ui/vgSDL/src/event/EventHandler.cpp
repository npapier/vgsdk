#include <vgSDL/event/EventHandler.hpp>

#include <vgSDL/event/Mouse.hpp>
#include <vgSDL/event/Joystick.hpp>

#define MAX_SDL_EVENTS 20

namespace vgSDL
{
namespace event
{


vgd::Shp<EventHandler> EventHandler::g_instance;

EventHandler::EventHandler()
{
	// Init SDL
	//SDL_WindowID id = SDL_CreateWindow("SDL",0,0,0,0,0);
	SDL_CreateRGBSurface(0,0,0,0,0,0,0,0);
	SDL_Init( SDL_INIT_JOYSTICK | SDL_INIT_VIDEO );
	SDL_JoystickEventState(SDL_ENABLE);
	m_events = new SDL_Event[ MAX_SDL_EVENTS ];
	m_nbEvents = 0;
}


bool EventHandler::getEvents()
{
	if(!g_instance)
		g_instance.reset(new EventHandler);
	SDL_JoystickUpdate();
	g_instance->m_nbEvents = SDL_PeepEvents(g_instance->m_events, 10, SDL_GETEVENT, SDL_ALLEVENTS);
	return (g_instance->m_nbEvents>0);
}

void EventHandler::dispatchEvents()
{
	if(!g_instance)
		g_instance.reset(new EventHandler);
	for(int i=0;i<g_instance->m_nbEvents;++i)
	{
		std::list<Mouse*>::iterator itm;
		std::list<Joystick*>::iterator itj;
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

} // namespace event
} // namespace vgSDL
