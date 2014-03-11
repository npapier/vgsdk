// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/event/device/Keyboard.hpp"

#include <QKeyEvent>

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/Shp.hpp>

#include "vgQt/event/helpers.hpp"


namespace vgQt
{

namespace event
{

namespace device
{


void Keyboard::onEvent( QEvent * event )
{
	// Skips processing if the event is not related to the keyboard.
	if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease)
	{
		return;
	}


	// Retrieves the effective event object.
	QKeyEvent	* keyEvent = static_cast< QKeyEvent* >(event);


    // We ignore the tab key since it causes state update problem
    // due to the focus lost of teh canvas.
    if( keyEvent->key() == Qt::Key_Tab )
    {
        return;
    }

    // Update global button states
    updateGlobalButtonStates( keyEvent );

    // Creates the keyEvent.
    using namespace ::vgd::event;

    KeyboardButtonEvent	* keyboardEvent = new KeyboardButtonEvent(
            this,
            vgd::event::detail::GlobalButtonStateSet::get(),
            getKeyboardButton(keyEvent),
            getButtonState(keyEvent)
		);

    // Fires the keyEvent to the listeners.
    this->fireEvent( vgd::makeShp(keyboardEvent) );
}


} // namespace device
} // namespace event
} // namespace vgQt
