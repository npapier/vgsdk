// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_DEVICE_TIMER_HPP_
#define _VGQT_EVENT_DEVICE_TIMER_HPP_

#include <vgd/event/device/Timer.hpp>
#include <QWidget>
#include <vgQt/event/device/Device.hpp>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace event
{

namespace device
{

struct VGQT_API Timer : public Device, public vgd::event::device::Timer
{
Q_OBJECT
public:
    void connect( QWidget * widget );

public Q_SLOTS:
    bool onTimeout();
};

} // namespace device
} // namespace event
} // namespace vgQt


#endif // _VGQT_EVENT_DEVICE_TIMER_HPP_
