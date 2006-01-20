// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/event/Helpers.hpp"



namespace vgWX
{
	
namespace event
{



template<>
void updateModifiersOfGlobalButtonStates<wxMouseEvent>( wxMouseEvent& event )
{
	using vgd::event::KeyboardButtonEvent;	
	using vgd::event::MouseButtonEvent;
	using vgd::event::detail::GlobalButtonStateSet;

	// clean all
	GlobalButtonStateSet::clear();
		
	// Keyboard
	GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_CONTROL,	event.ControlDown() );
	GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_SHIFT,	event.ShiftDown() );
	GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_ALT,		event.AltDown() );

	// Mouse
	GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_1, event.LeftIsDown() );
	GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_2, event.MiddleIsDown() );
	GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_3, event.RightIsDown() );

	// Capture/Release mouse
	wxWindow *pWindow = dynamic_cast<wxWindow*>(event.GetEventObject());
	assert( pWindow != 0 );

	if ( GlobalButtonStateSet::get().isDown() )
	{
		if ( pWindow->HasCapture() == false )
		{
			pWindow->SetFocus();
			pWindow->CaptureMouse();
		}
	}
	else
	{
		if ( pWindow->HasCapture() )
		{
			pWindow->ReleaseMouse();
		}
	}
}



} // namespace vgWX

} // namespace event
