// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/event/device/Mouse.hpp"

#include <iostream>
#include <limits>
#include <vgd/Shp.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>

#include "vgGTK/event/helpers.hpp"



namespace vgGTK
{

namespace event
{

namespace device
{



Mouse::Mouse( const uint identifier )
:	::vgd::event::device::Mouse(identifier),
	m_previousLocation( std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{}



void Mouse::connect( Gtk::Widget * widget )
{
	using vgGTK::event::device::Mouse;

	store( widget->signal_button_press_event()  .connect( ::sigc::mem_fun(this, &Mouse::onButtonEvent) )			);
	store( widget->signal_button_release_event().connect( ::sigc::mem_fun(this, &Mouse::onButtonEvent) )			);
	store( widget->signal_motion_notify_event() .connect( ::sigc::mem_fun(this, &Mouse::onMotionNotifyEvent) )	);
	store( widget->signal_scroll_event()        .connect( ::sigc::mem_fun(this, &Mouse::onScrollEvent ) )			);

	SignalHandler::connect( widget );
}



bool Mouse::onButtonEvent( GdkEventButton * event )
{
	// Update global button states
	updateGlobalButtonStates( event );

	// Processes normal buttons (left, middle and right).
	if( event->button == 1 || event->button == 2 || event->button == 3 )
	{
		vgd::event::MouseButtonEvent * mouseButtonEvent = 0;

		mouseButtonEvent = new vgd::event::MouseButtonEvent(
				this,
				vgd::event::detail::GlobalButtonStateSet::get(),
				getButtonId(event),
				getButtonState(event),
				getLocation(event),
				getSize(event)
			 );
		this->fireEvent( vgd::makeShp(mouseButtonEvent) );
	}
	// Processes mouse wheel events.
	else if( event->button == 4 || event->button == 5 )
	{
		vgd::event::MouseWheelEvent * mouseWheelEvent = 0;
		const int32					delta = (event->button == 4) ? -10 : +10;

		mouseWheelEvent = new vgd::event::MouseWheelEvent(
				this,
				vgd::event::detail::GlobalButtonStateSet::get(),
				vgd::event::MouseWheelEvent::VERTICAL,
				delta
			);
		this->fireEvent( vgd::makeShp(mouseWheelEvent) );
	}
	else
	{
		assert( false && "Unsupported mouse button." );
	}

	return true;
}



bool Mouse::onMotionNotifyEvent( GdkEventMotion * event )
{
	// Update global button states
	updateGlobalButtonStates( event );


	// Fires the notification.
	using ::vgd::event::Location2Event;

	const Location2Event::Location	location = getLocation(event);
	Location2Event					* locationEvent = 0;

	locationEvent = new vgd::event::Location2Event(
			this,
			vgd::event::detail::GlobalButtonStateSet::get(),
			location,
			m_previousLocation,
			getSize(event)
		);

	this->fireEvent( vgd::makeShp(locationEvent) );

	// Update previous location
	m_previousLocation = location;

	return false;
}



bool Mouse::onScrollEvent( GdkEventScroll * event )
{
	// Update global button states
	updateGlobalButtonStates( event );


	// Fires the notification .
	vgd::event::MouseWheelEvent * 	mouseWheelEvent = 0;
	int32							delta = 0;

	switch( event->direction )
	{
	case GDK_SCROLL_UP:		delta = +50; break;
	case GDK_SCROLL_DOWN:	delta = -50; break;
	case GDK_SCROLL_LEFT:	/*nothing*/  break;
	case GDK_SCROLL_RIGHT:	/*nothing*/  break;
	}

	mouseWheelEvent = new vgd::event::MouseWheelEvent(
			this,
			vgd::event::detail::GlobalButtonStateSet::get(),
			vgd::event::MouseWheelEvent::VERTICAL,
			delta
		);
	this->fireEvent( vgd::makeShp(mouseWheelEvent) );


	return true;
}



} // namespace device

} // namespace event

} // namespace vgGTK
