// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgSDL/event/Joystick.hpp"

#include <limits>

#include <SDL.h>

#include <vgd/event/AxisEvent.hpp>
#include <vgd/event/HatEvent.hpp>
#include <vgd/event/JoystickButtonEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>



namespace vgSDL
{

namespace event
{

namespace
{

	/**
	 * @brief	Normalizes any given number in a real number between -1 and 1.
	 *
	 * @param	in	the input number to normalize
	 *
	 * @return	the normalized value
	 */
	template< typename Number >
	const float normalize( const Number in )
	{
		return static_cast<float>(in) / ((in <= 0) ? -std::numeric_limits<Number>::min() : std::numeric_limits<Number>::max());
	}

}



Joystick::JoyCollection	Joystick::m_joyCache;



vgd::Shp< Joystick > Joystick::find( const int index )
{
	assert( index >= 0 );

	return (static_cast<size_t>(index) < m_joyCache.size()) ? m_joyCache[index].lock() : vgd::Shp< Joystick >();
}



vgd::Shp< Joystick > Joystick::get( const int index )
{
	assert( index >= 0 );
	assert( SDL_WasInit(SDL_INIT_JOYSTICK) == SDL_INIT_JOYSTICK && "SDL joystick not initialized !" );

	// Adjusts the cache size to the number of joysticks.
	m_joyCache.resize( SDL_NumJoysticks() );


	// Let's look for a joystick in the cache.
	vgd::Shp< Joystick >	result = find(index);

	if( ! result && (index<(int)m_joyCache.size()))
	{
		result = create(index);
		if(result)
		{
			m_joyCache[ index ] = result;
		}
	}
	return result;
}



void Joystick::handleEvent( const SDL_JoyAxisEvent & event )
{
	vgd::Shp< Joystick >	joystick = find( event.which );

	if( joystick )
	{
		using ::vgd::event::AxisEvent;
		using ::vgd::event::detail::GlobalButtonStateSet;

		const float value		= normalize(event.value);
		AxisEvent	* myEvent	= 0;

		myEvent = new AxisEvent(
				joystick.get(),
				GlobalButtonStateSet::get(),
				static_cast<int>(event.axis),
				value
			);
		joystick->fireEvent( vgd::makeShp(myEvent) );
	}
}



void Joystick::handleEvent( const SDL_JoyButtonEvent & event )
{
	vgd::Shp< Joystick >	joystick = find( event.which );

	if( joystick )
	{
		using ::vgd::event::JoystickButtonEvent;
		using ::vgd::event::detail::GlobalButtonStateSet;

		const bool			isDown		= (event.state == SDL_PRESSED);
		const int			buttonId	= BUTTON_1 + event.button;
		JoystickButtonEvent	* myEvent	= 0;

		GlobalButtonStateSet::update( buttonId, isDown );

		myEvent = new JoystickButtonEvent(
				joystick.get(),
				GlobalButtonStateSet::get(),
				buttonId,
				isDown ? JoystickButtonEvent::DOWN : JoystickButtonEvent::UP
			);
		joystick->fireEvent( vgd::makeShp(myEvent) );
	}
}



void Joystick::handleEvent( const SDL_JoyHatEvent & event )
{
	vgd::Shp< Joystick >	joystick = find( event.which );

	if( joystick )
	{
		using ::vgd::event::HatEvent;
		using ::vgd::event::detail::GlobalButtonStateSet;

		HatEvent	* myEvent	= 0;
		int			state		= HatEvent::CENTERED;

		if( event.value & SDL_HAT_UP	) state |= HatEvent::UP;
		if( event.value & SDL_HAT_RIGHT	) state |= HatEvent::RIGHT;
		if( event.value & SDL_HAT_DOWN	) state |= HatEvent::DOWN;
		if( event.value & SDL_HAT_LEFT	) state |= HatEvent::LEFT;

		myEvent = new HatEvent(
				joystick.get(),
				GlobalButtonStateSet::get(),
				event.hat,
				static_cast< HatEvent::State >( state )
			);
		joystick->fireEvent( vgd::makeShp(myEvent) );
	}
}



vgd::Shp<Joystick> Joystick::create( const int index )
{
	assert( SDL_WasInit(SDL_INIT_JOYSTICK) == SDL_INIT_JOYSTICK && "SDL joystick not initialized !" );

	// Opens the joytsick.
	SDL_Joystick* joystick = SDL_JoystickOpen( index );
	if(joystick != 0)
	{
		return vgd::makeShp(new Joystick(joystick));
	}
	else
	{
		return vgd::Shp<Joystick>();
	}
	//assert( m_joystick != 0 && "SDL joystick opening faled !" );
}


Joystick::Joystick( SDL_Joystick* joystick )
:	m_joystick( joystick )
{
	assert(joystick!=0 && "Invalid joystick");
}



Joystick::~Joystick()
{
	assert( m_joystick != 0 );

	SDL_JoystickClose( m_joystick );
}



const int Joystick::getIndex() const
{
	assert( m_joystick != 0 );

	return SDL_JoystickIndex( m_joystick );
}



const std::string Joystick::getName() const
{
	assert( SDL_WasInit(SDL_INIT_JOYSTICK) == SDL_INIT_JOYSTICK && "SDL joystick not initialized !" );

	return std::string( SDL_JoystickName(getIndex()) );
}



const float Joystick::getAxis( const int axis ) const
{
	assert( m_joystick != 0 );

	return normalize( getAxisRaw(axis) );
}



const int Joystick::getAxesNumber() const
{
	assert( m_joystick != 0 );

	return SDL_JoystickNumAxes( m_joystick );
}



const short Joystick::getAxisRaw( const int axis ) const
{
	assert( m_joystick != 0 );

	return SDL_JoystickGetAxis(m_joystick, axis);
}



const bool Joystick::getButton( const Button button ) const
{
	assert( m_joystick != 0 );

	return SDL_JoystickGetButton(m_joystick, button - BUTTON_1) == 1;
}



} // namespace event

} // namespace vgSDL
