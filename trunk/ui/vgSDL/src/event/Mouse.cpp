#include <vgSDL/event/Mouse.hpp>
#include <vgSDL/event/EventHandler.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>

#include <vgd/event/Location2Event.hpp>

#include <SDL_events.h>

namespace vgSDL
{
namespace event
{

Mouse::Mouse()
{
	EventHandler::connect(this);
}

Mouse::~Mouse()
{
	EventHandler::disconnect(this);
}



void Mouse::handleEvent( const SDL_Event & event )
{
	switch(event.type)
	{
	case SDL_MOUSEMOTION:
	{
		using ::vgd::event::Location2Event;
		using ::vgd::event::Location2;
		vgm::Vec2f location((float)event.motion.x,(float)event.motion.y);
		vgd::Shp<Location2Event> locationEvent(
			new vgd::event::Location2Event(
				this,
				vgd::event::detail::GlobalButtonStateSet::get(),
				location,
				m_previousLocation,
				vgm::Vec2f(0,0),
				event.motion.which
				)
			);
		fireEvent(locationEvent);
		break;
	}
	}
}



} // namespace event
} // namespace vgSDL
