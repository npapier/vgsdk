// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_DEVICE_MOUSE_HPP_
#define _VGQT_EVENT_DEVICE_MOUSE_HPP_

#include <vgd/event/device/Mouse.hpp>
#include <vgd/event/Location2.hpp>
#include <QMouseEvent>
#include <vgQt/event/device/Device.hpp>
#include <QObject>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace event
{

namespace device
{

/**
 * @brief	Implements a mouse event device for Qt widgets.
 *
 */
class VGQT_API Mouse : public Device, public vgd::event::device::Mouse
{
    Q_OBJECT
public:
    ::vgd::event::Location2::Location	m_previousLocation;	///< Holds the previous mouse location.

    /**
     * @brief	Constructor
     *
     * @param identifier	the device identifier.
     *
     */
    Mouse( const uint identifier = 0 );

    /**
     * @name	Overrides
     */
    void connect( QWidget * widget );

 public Q_SLOTS:
    /**
     * @brief	Handles scroll notification events.
     *
     */
    bool onScrollEvent( QWheelEvent * event );

    /**
     * @brief	Handles mouse button press and release events.
     *
     */
    bool onButtonEvent( QMouseEvent * event );

    /**
     * @brief	Handles motion notificiation events.
     *
     */
    bool onMotionNotifyEvent( QMouseEvent * event );
};

} // namespace device
} // namespace event
} // namespace vgQt


#endif // _VGQT_EVENT_DEVICE_MOUSE_HPP_
