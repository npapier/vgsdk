// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/BasicManipulator.hpp"

#include <cassert>
#include <vgSDL/event/device/Joystick.hpp>

#include "vgGTK/event/device/Keyboard.hpp"
#include "vgGTK/event/device/Mouse.hpp"
#include "vgGTK/event/device/Timer.hpp"




namespace vgGTK
{



BasicManipulator::BasicManipulator()
{
	initDevices();
}



BasicManipulator::~BasicManipulator()
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
}



void BasicManipulator::initDevices()
{
	assert( m_keyboard == 0 && m_mouse == 0 && m_timer == 0 && m_joystick == 0 );

	// Creates device instances.
	m_keyboard.reset( new vgGTK::event::device::Keyboard() );
	m_mouse.reset( new vgGTK::event::device::Mouse() );
	m_timer.reset( new vgGTK::event::device::Timer() );
	m_joystick = vgSDL::event::device::Joystick::get(0);

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



} // namespace vgGTK
