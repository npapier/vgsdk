// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/BasicManipulator.hpp"



namespace vgGTK
{



BasicManipulator::BasicManipulator()
{
	set_events( Gdk::SCROLL_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK );
	set_flags( Gtk::CAN_FOCUS );
	grab_focus();
}



void BasicManipulator::on_realize()
{
	GenericCanvas< vgUI::BasicManipulator >::on_realize();

	m_keyboard.connect( this );
	m_keyboard.attachEventListener( this );

	m_mouse.connect( this );
	m_mouse.attachEventListener( this );
}



void BasicManipulator::on_unrealize()
{
	m_keyboard.detachEventListener( this );
	m_keyboard.disconnect();

	m_mouse.detachEventListener( this );
	m_mouse.disconnect();

	GenericCanvas< vgUI::BasicManipulator >::on_unrealize();
}




} // namespace vgGTK
