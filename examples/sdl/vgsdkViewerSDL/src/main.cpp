// VGSDK - Copyright (C) 2014, Philippe Sengchanpheng, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Philippe Sengchanpheng
// Author Nicolas Papier

#include <vgOpenAssetImport/Loader.hpp>
#include <vgd/node/Box.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgSDL/BasicManipulator.hpp>

int main( int argc, char ** argv )
{
	vgOpenAssetImport::Loader foobar; // ?????????????

	using vgSDL::BasicManipulator;
	BasicManipulator canvas;

	// Scene graph initialization
	canvas.createOptionalNodes();

	using vgd::node::ClearFrameBuffer;
	vgd::Shp< ClearFrameBuffer > clear = canvas.getOptionalNodeAs< ClearFrameBuffer >(BasicManipulator::CLEAR_FRAME_BUFFER);
	clear->setClearColor(vgm::Vec4f(0.1f, 0.2f, 0.2f, 0.f));

	// Configures engine
	canvas.setDebugOverlay(true);

	// Default scene
	vgd::Shp< vgd::node::Box > box = vgd::node::Box::create("Default scene");
	canvas.getScene()->addChild(box);
	//canvas.load("D:\\Dev\\lib\\dtUlis\\share\\cavities\\1\\mesh\\liver.dae");

	//	Default light configuration
	using vgd::node::Switch;
	vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>(canvas.createOptionalNode(BasicManipulator::LIGHTS));

	// LIGHTS node is the first child of the setup group			@todo menu to switch between LIGHTS located on the camera (set in the camera) or located in the scene (set in the scene)
	canvas.getSetup()->removeChild(lightSwitcher);
	canvas.getSetup()->insertChild(lightSwitcher);

	if (lightSwitcher)
	{
		lightSwitcher->setWhichChild(0);
	}

	canvas.viewAll();
	//refreshForced();
	canvas.mainLoop();

	
	/*using vgd::Shp;
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
	}*/

	return 0;
}