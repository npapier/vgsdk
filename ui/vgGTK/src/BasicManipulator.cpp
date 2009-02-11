// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/BasicManipulator.hpp"



namespace vgGTK
{



BasicManipulator::BasicManipulator()
:	m_keyboard( new vgGTK::event::Keyboard() ),
	m_mouse( new vgGTK::event::Mouse() )
{}



void BasicManipulator::on_realize()
{
	GenericCanvas< vgUI::BasicManipulator >::on_realize();

	// Connect GTK devices to the widget so they receive GTK events.
	m_keyboard->connect( this );
	m_mouse->connect( this );
	
	// Adds devices so we receive vgd events.
	addDevice( m_keyboard );
	addDevice( m_mouse );
}



void BasicManipulator::on_unrealize()
{
	m_keyboard->disconnect();
	m_mouse->disconnect();
	
	removeDevice( m_keyboard );
	removeDevice( m_mouse );

	GenericCanvas< vgUI::BasicManipulator >::on_unrealize();
}




} // namespace vgGTK
