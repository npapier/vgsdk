// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/event/device/Keyboard.hpp"

#include <iostream>
#include <gdk/gdkkeysyms.h>
#include <vgd/Shp.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>

#include "vgGTK/event/helpers.hpp"



namespace vgGTK
{

namespace event
{

namespace device
{


void Keyboard::connect( Gtk::Widget * widget )
{
	store( widget->signal_key_press_event()  .connect( ::sigc::mem_fun(this, &Keyboard::onKeyEvent) )	);
	store( widget->signal_key_release_event().connect( ::sigc::mem_fun(this, &Keyboard::onKeyEvent) )	);

	SignalHandler::connect( widget );
}



bool Keyboard::onKeyEvent( GdkEventKey * event )
{
	// We ignore the tab key since it causes state update problem
	// due to the focus lost of teh canvas.
	if( event->keyval == GDK_Tab )
	{
		return false;
	}


	// Update global button states
	updateGlobalButtonStates( event );


	// Creates the event.
	using namespace ::vgd::event;

	KeyboardButtonEvent	* keyboardEvent;
	keyboardEvent = new KeyboardButtonEvent(
			this,
			vgd::event::detail::GlobalButtonStateSet::get(),
			getKeyboardButton(event),
			getButtonState(event)
		);


	// Fires the event to the listeners.
	fireEvent( vgd::makeShp(keyboardEvent) );


	// Job's done.
	return false;
}



} // namespace device

} // namespace event

} // namespace vgGTK
