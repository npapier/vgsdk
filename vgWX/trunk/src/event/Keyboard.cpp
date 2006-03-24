// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgWX/event/Keyboard.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include "vgWX/event/Helpers.hpp"



namespace vgWX
{
	
namespace event
{


BEGIN_EVENT_TABLE(Keyboard, wxEvtHandler)
	EVT_KEY_DOWN	(	Keyboard::onKeyDown	)
	EVT_KEY_UP		(	Keyboard::onKeyUp	)
END_EVENT_TABLE()
	
	
Keyboard::Keyboard()
{}


void Keyboard::onKeyDown( wxKeyEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	vgd::event::detail::GlobalButtonStateSet::update( event.GetKeyCode(), true );

	//
	vgd::event::KeyboardButtonEvent	*keyboardButtonEvent;
	
	keyboardButtonEvent = new vgd::event::KeyboardButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		event.GetKeyCode(),
		vgd::event::KeyboardButtonEvent::DOWN
	);
	this->fireEvent( vgd::Shp<vgd::event::Event>(keyboardButtonEvent) );
	
	event.Skip();
}


void Keyboard::onKeyUp( wxKeyEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	vgd::event::detail::GlobalButtonStateSet::update( event.GetKeyCode(), false );
		
	vgd::event::KeyboardButtonEvent	*keyboardButtonEvent;
	
	keyboardButtonEvent = new vgd::event::KeyboardButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		event.GetKeyCode(),
		vgd::event::KeyboardButtonEvent::UP
	);
	this->fireEvent( vgd::Shp<vgd::event::Event>(keyboardButtonEvent) );
	
	event.Skip();
}


	
} // namespace event

} // namespace vgWX
