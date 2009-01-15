#include <vgSDL/event/Mouse.hpp>

#include <SDL_events.h>
#include <SDL_version.h>

//#include <vgd/Shp.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/Location2Event.hpp>

#include <vgSDL/event/EventHandler.hpp>

namespace vgSDL
{
namespace event
{

Mouse::Mouse()
{
	//EventHandler::connect(this);
}

Mouse::~Mouse()
{
	//EventHandler::disconnect(this);
}



void Mouse::handleEvent( const SDL_Event & event )
{

	vgd::Shp<Mouse> mouse = find(event.motion.which);
	if(!mouse)
		return;

	switch(event.type)
	{
	case SDL_MOUSEMOTION:
	{
		using ::vgd::event::Location2Event;
		using ::vgd::event::Location2;
		vgm::Vec2f location((float)event.motion.x,(float)event.motion.y);
		vgd::Shp<Location2Event> locationEvent(
			new vgd::event::Location2Event(
				mouse.get(),
				vgd::event::detail::GlobalButtonStateSet::get(),
				location,
				mouse->m_previousLocation,
				vgm::Vec2f(0,0),
#if (SDL_MINOR_VERSION == 3) // SDL 1.3
				event.motion.which
#else // SDL 1.2
				0
#endif
				)
			);
		mouse->fireEvent(locationEvent);
		break;
	}
	}
}



Mouse::MiceCollection	Mouse::m_mouseCache;



vgd::Shp< Mouse > Mouse::find( const int index )
{
	assert( index >= 0 );

	return (static_cast<size_t>(index) < m_mouseCache.size()) ? m_mouseCache[index].lock() : vgd::Shp< Mouse >();
}



vgd::Shp< Mouse > Mouse::get( const int index )
{
	assert( index >= 0 );
	//assert( SDL_WasInit(SDL_INIT_JOYSTICK) == SDL_INIT_JOYSTICK && "SDL joystick not initialized !" );

	// Adjusts the cache size to the number of joysticks.
#if SDL_MINOR_VERSION == 3 // SDL 1.3
	m_mouseCache.resize( SDL_GetNumMice());
#else
	m_mouseCache.resize( 1 );
#endif

	// Let's look for a joystick in the cache.
	vgd::Shp< Mouse >	result = find(index);

	if( ! result && (index<(int)m_mouseCache.size()))
	{
		result = vgd::makeShp(new Mouse());
		if(result)
		{
			m_mouseCache[ index ] = result;
		}
	}
	return result;
}


} // namespace event
} // namespace vgSDL
