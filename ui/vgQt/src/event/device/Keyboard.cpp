// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <vgQt/event/device/Keyboard.hpp>
#include <vgQt/event/helpers.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/Shp.hpp>
#include <QKeyEvent>

namespace vgQt
{

namespace event
{

namespace device
{

void Keyboard::connect( QWidget *widget )
{
    QObject::connect(widget,SIGNAL(key( QKeyEvent * )), this, SLOT(onKeyEvent( QKeyEvent * )));

    Device::connect( widget );
}

bool Keyboard::onKeyEvent( QKeyEvent * event )
{
    // We ignore the tab key since it causes state update problem
    // due to the focus lost of teh canvas.
    if( event->key() == Qt::Key_Tab )
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
            getButtonState(event));


    // Fires the event to the listeners.
    this->fireEvent( vgd::makeShp(keyboardEvent) );


    // Job's done.
    return false;
}

} // namespace device
} // namespace event
} // namespace vgQt
