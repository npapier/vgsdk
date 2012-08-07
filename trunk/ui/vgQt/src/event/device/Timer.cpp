// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/event/device/Timer.hpp"

#include <QTimer>

#include <vgd/Shp.hpp>
#include <vgd/event/TimerEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>


namespace vgQt
{

namespace event
{

namespace device
{

Timer::Timer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

#ifdef _DEBUG
    timer->start(1000/15);
#else
    timer->start(1000/30);
#endif
}


bool Timer::onTimeout()
{
    // Creates the event.
    using namespace ::vgd::event;

    TimerEvent	* timerEvent = new TimerEvent( this, vgd::event::detail::GlobalButtonStateSet::get() );

    // Fires the event to the listeners.
    fireEvent( vgd::makeShp(timerEvent) );

    // Job's done, but keep going (do not disconnect yet)
    return true;
}


} // namespace device
} // namespace event
} // namespace vgQt
