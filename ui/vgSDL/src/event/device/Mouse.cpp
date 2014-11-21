// VGSDK - Copyright (C) 2009, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Nicolas Papier

#include <vgSDL/event/device/Mouse.hpp>

#include <SDL_events.h>
#include <SDL_version.h>

#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/Location2Event.hpp>

#include <vgSDL/event/EventHandler.hpp>
#include <vgSDL/event/helpers.hpp>



namespace vgSDL
{

namespace event
{

namespace device
{



Mouse::Mouse( const uint identifier )
:	::vgd::event::device::Mouse( identifier )
{
	//EventHandler::connect(this);
}


Mouse::~Mouse()
{
	//EventHandler::disconnect(this);
}


void Mouse::handleEvent( const SDL_MouseMotionEvent & event )
{
	vgd::Shp<Mouse> mouse = find(event.which);

	if ( !mouse )
		return;

	using ::vgd::event::Location2Event;
	using ::vgd::event::Location2;
	const vgm::Vec2f location = getLocation(&event);
	vgd::Shp<Location2Event> locationEvent(
		new vgd::event::Location2Event(
			mouse.get(),
			vgd::event::detail::GlobalButtonStateSet::get(),
			location,
			mouse->m_previousLocation,
			getSize() ) );

	mouse->fireEvent(locationEvent);

	// Update previous location
	mouse->m_previousLocation = location;
}

void Mouse::handleEvent(const SDL_MouseButtonEvent & event)
{
	vgd::Shp<Mouse> mouse = find(event.which);

	if (!mouse)
	{
		vgAssert(false);
		return;
	}

	// Update global button states
	updateGlobalButtonStates(&event);
	// update the position
	mouse->m_previousLocation = getLocation(&event);

	// Processes normal buttons (left, middle and right).
	if (event.button == SDL_BUTTON_LEFT || event.button == SDL_BUTTON_RIGHT || event.button == SDL_BUTTON_MIDDLE)
	{
		vgd::event::MouseButtonEvent	* mouseEvent = 0;
		mouseEvent = new vgd::event::MouseButtonEvent(
			mouse.get(),
			vgd::event::detail::GlobalButtonStateSet::get(),
			getButtonId(&event),
			getButtonState(&event),
			getLocation(&event),
			getSize()
			);
		mouse->fireEvent(vgd::makeShp(mouseEvent));
	}
	// Processes mouse wheel events.
	else if (event.button == SDL_BUTTON_WHEELDOWN || event.button == SDL_BUTTON_WHEELUP)
	{
		vgd::event::MouseWheelEvent * mouseWheelEvent = 0;
		const int32		delta = (event.button == SDL_BUTTON_WHEELDOWN) ? -10 : +10;

		mouseWheelEvent = new vgd::event::MouseWheelEvent(
			mouse.get(),
			vgd::event::detail::GlobalButtonStateSet::get(),
			vgd::event::MouseWheelEvent::VERTICAL,
			delta
			);
		mouse->fireEvent(vgd::makeShp(mouseWheelEvent));
	}
	else
	{
		assert(false && "Unsupported mouse button.");
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
		result = vgd::makeShp( new Mouse( index ) );

		if(result)
		{
			m_mouseCache[ index ] = result;
		}
	}
	return result;
}


} // namespace device

} // namespace event

} // namespace vgSDL
