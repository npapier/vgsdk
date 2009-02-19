// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/BasicManipulator.hpp"



namespace vgGTK
{



BasicManipulator::BasicManipulator()
:	m_keyboard( new vgGTK::event::device::Keyboard() ),
	m_mouse( new vgGTK::event::device::Mouse() ),
	m_timer( new vgGTK::event::device::Timer() )
{}



void BasicManipulator::on_realize()
{
	GenericCanvas< vgUI::BasicManipulator >::on_realize();

	// Connect GTK devices to the widget so they receive GTK events.
	m_keyboard->connect( this );
	m_mouse->connect( this );
	m_timer->connect( this );

	// Adds devices so we receive vgd events.
	addDevice( m_keyboard );
	addDevice( m_mouse );
	addDevice( m_timer );
}



void BasicManipulator::on_unrealize()
{
	m_keyboard->disconnect();
	m_mouse->disconnect();
	m_timer->disconnect();

	removeDevice( m_keyboard );
	removeDevice( m_mouse );
	removeDevice( m_timer );

	GenericCanvas< vgUI::BasicManipulator >::on_unrealize();
}




} // namespace vgGTK
