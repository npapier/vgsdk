// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <limits>
#include <vgQt/event/device/Mouse.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgQt/event/helpers.hpp>
#include <vgd/Shp.hpp>
#include <QMouseEvent>
#include <QObject>

namespace vgQt
{

namespace event
{

namespace device
{

Mouse::Mouse( const uint identifier )
:	::vgd::event::device::Mouse(identifier),
    m_previousLocation( std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{}

void Mouse::connect( QWidget *widget )
{
    QObject::connect(widget,SIGNAL(wheel( QWheelEvent * )), this, SLOT(onScrollEvent( QWheelEvent * )));
    QObject::connect(widget,SIGNAL(clic( QMouseEvent * )), this, SLOT(onButtonEvent( QMouseEvent * )));
    QObject::connect(widget,SIGNAL(move( QMouseEvent * )), this, SLOT(onMotionNotifyEvent( QMouseEvent * )));

    Device::connect( widget );
}

bool Mouse::onButtonEvent( QMouseEvent * event )
{
    // Update global button states
    updateGlobalButtonStates( event );

    // update the position
    m_previousLocation = getLocation(m_connectedWidget, event);

    // Processes normal buttons (left, middle and right).
    if( event->button() == Qt::LeftButton || event->button() == Qt::RightButton || event->button() == Qt::MiddleButton )
    {
        vgd::event::MouseButtonEvent * mouseButtonEvent = 0;

        mouseButtonEvent = new vgd::event::MouseButtonEvent(
                this,
                vgd::event::detail::GlobalButtonStateSet::get(),
                getButtonId(event),
                getButtonState(event),
                getLocation(m_connectedWidget, event),
                getSize(m_connectedWidget)
             );
        this->fireEvent( vgd::makeShp(mouseButtonEvent) );
    }
    else
    {
        assert( false && "Unsupported mouse button." );
    }
    return false;
}

bool Mouse::onMotionNotifyEvent( QMouseEvent * event )
{
    // Fires the notification.
    using ::vgd::event::Location2Event;

    const Location2Event::Location	location = getLocation(m_connectedWidget, event);
    Location2Event					* locationEvent = 0;

    locationEvent = new vgd::event::Location2Event(
            this,
            vgd::event::detail::GlobalButtonStateSet::get(),
            location,
            m_previousLocation,
            getSize(m_connectedWidget)
        );

    this->fireEvent( vgd::makeShp(locationEvent) );

    // Update previous location
    m_previousLocation = location;

    return false;
}

bool Mouse::onScrollEvent( QWheelEvent * event )
{
    // Processes mouse wheel events.

    // Fires the notification .
    vgd::event::MouseWheelEvent * 	mouseWheelEvent = 0;
    int32							delta = 0;

    delta = (event->delta() > 0) ? 50 : -50;

    mouseWheelEvent = new vgd::event::MouseWheelEvent(
            this,
            vgd::event::detail::GlobalButtonStateSet::get(),
            vgd::event::MouseWheelEvent::VERTICAL,
            delta
        );
    this->fireEvent( vgd::makeShp(mouseWheelEvent) );

    return false;
}

} // namespace device
} // namespace event
} // namespace vgQt
