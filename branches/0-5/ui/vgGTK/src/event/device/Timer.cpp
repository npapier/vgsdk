// VGSDK - Copyright (C) 2009, 2011, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgGTK/event/device/Timer.hpp"

#include <glibmm/main.h>

#include <sigc++/slot.h>
#include <sigc++/adaptors/bind.h>

#include <vgd/Shp.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/TimerEvent.hpp>



namespace vgGTK
{

namespace event
{

namespace device
{



Timer::Timer()
{
	// Connects the slot to the Glib::signal_timeout()
	sigc::slot<bool> mySlot = sigc::bind( ::sigc::mem_fun(this, &Timer::onTimeout), 1 );

#ifdef _DEBUG
	Glib::signal_timeout().connect( mySlot, 1000/15 );
#else
	Glib::signal_timeout().connect( mySlot, 1000/30 );
#endif
}



bool Timer::onTimeout( int timerNumber )
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

} // namespace vgGTK
