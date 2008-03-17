// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>

#include <vgd/event/AxisEvent.hpp>
#include <vgd/event/HatEvent.hpp>
#include <vgd/event/JoystickButtonEvent.hpp>
#include <vgd/event/Listener.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/detail/helpers.hpp>
#include <vgSDL/event/event.hpp>
#include <vgSDL/event/Joystick.hpp>



bool combo = false;



struct MyListener : public vgd::event::Listener
{
	void onEvent( vgd::Shp<vgd::event::Event> event )
	{
		using ::vgd::event::AxisEvent;
		using ::vgd::event::HatEvent;
		using ::vgd::event::Joystick;
		using ::vgd::event::JoystickButtonEvent;

		vgd::Shp< AxisEvent >			axisEvent		= vgd::dynamic_pointer_cast< AxisEvent >(event);
		vgd::Shp< HatEvent >			hatEvent		= vgd::dynamic_pointer_cast< HatEvent >(event);
		vgd::Shp< JoystickButtonEvent >	joyButtonEvent	= vgd::dynamic_pointer_cast< JoystickButtonEvent >(event);

		if( axisEvent )
		{
			std::cout << "AxisEvent : " << axisEvent->getIndex() << " " << axisEvent->getValue() << std::endl;
		}
		else if( hatEvent )
		{
			std::cout << "HatEvent : ";
			std::cout << hatEvent->getIndex();
			std::cout << " ";
			std::cout << ::vgd::event::detail::toString( hatEvent->getState() );
			std::cout << std::endl;
		}
		else if( joyButtonEvent )
		{
			std::cout << "JoysticButtonEvent : ";
			std::cout << ::vgd::event::detail::toString( joyButtonEvent->getButtonID() );
			std::cout << " ";
			std::cout << ::vgd::event::detail::toString( joyButtonEvent->getState() );
			std::cout << std::endl;

			using ::vgd::event::detail::GlobalButtonStateSet;

			combo =	GlobalButtonStateSet::get().isDown(Joystick::BUTTON_1) &&
					GlobalButtonStateSet::get().isDown(Joystick::BUTTON_2) &&
					GlobalButtonStateSet::get().isDown(Joystick::BUTTON_3) &&
					GlobalButtonStateSet::get().isDown(Joystick::BUTTON_4);
		}
	}
};




int main( int argc, char ** argv )
{
	using vgd::Shp;
	using vgSDL::event::Joystick;

	// Initializes SDL systems.
	// VIDEO is required in order to have the event system enabled.
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );

	typedef std::vector< std::string >		Strings;
	typedef std::vector< Shp< Joystick > >	Joysticks;

	const Strings	joyNames = vgSDL::event::Joystick::getNames< Strings >();
	Joysticks		joys;
	MyListener		myListener;

	std::cout << "Found " << joyNames.size() << " joystick(s)." << std::endl;
	for( Strings::const_iterator i = joyNames.begin(); i != joyNames.end(); ++i )
	{
		std::cout << " * " << *i << std::endl;

		vgd::Shp< Joystick >	joystick = Joystick::get( std::distance(joyNames.begin(), i) );

		joys.push_back( joystick );
		joystick->attachEventListener( & myListener );
	}


	// Enables joystick events and polls them.
	SDL_JoystickEventState(SDL_ENABLE);
	while( !combo )
	{
		if( vgSDL::event::processEvent() == 0 )
		{
			SDL_Delay( 10 );
		}
	}

	return 0;
}