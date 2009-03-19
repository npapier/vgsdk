// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/BasicManipulator.hpp"

#include "vgGTK/event/device/Keyboard.hpp"
#include "vgGTK/event/device/Mouse.hpp"
#include "vgGTK/event/device/Timer.hpp"
#include <vgSDL/event/device/Joystick.hpp>



namespace vgGTK
{



BasicManipulator::BasicManipulator()
:	m_keyboard(	new vgGTK::event::device::Keyboard()	),
	m_mouse(	new vgGTK::event::device::Mouse()		),
	m_timer(	new vgGTK::event::device::Timer()		),
	m_joystick(	vgSDL::event::device::Joystick::get(0)	)
{}



void BasicManipulator::on_realize()
{
	GenericCanvas< vgUI::BasicManipulator >::on_realize();

	// Connects GTK devices to the widget so they receive GTK events.
	m_keyboard->connect( this );
	m_mouse->connect( this );
	m_timer->connect( this );

	// Adds devices so we receive vgd events.
	addDevice( m_keyboard );
	addDevice( m_mouse );
	addDevice( m_timer );

	// Adds joystick (if present)
	if( m_joystick )
	{
		addDevice( m_joystick );
	}
	else
	{
		vgDebug::get().logWarning( "No joystick found." );
	}
}



void BasicManipulator::on_unrealize()
{
	// Disconnects GTK devices to the widget so they no more receive GTK events
	m_keyboard->disconnect();
	m_mouse->disconnect();
	m_timer->disconnect();

	// Removes devices
	removeDevice( m_keyboard );
	removeDevice( m_mouse );
	removeDevice( m_timer );

	// Removes joystick (if present)
	if ( m_joystick )
	{
		removeDevice( m_joystick );
	}

	GenericCanvas< vgUI::BasicManipulator >::on_unrealize();
}



} // namespace vgGTK
