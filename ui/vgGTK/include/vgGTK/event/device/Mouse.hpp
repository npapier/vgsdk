// VGSDK - Copyright (C) 2008, 2009, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_MOUSE_HPP_
#define _VGGTK_EVENT_MOUSE_HPP_

//#include <gdk/gdk.h>
#include <gtkmm/Widget.h>
#include <vgd/event/device/Mouse.hpp>
#include <vgd/event/Location2.hpp>
#include <sigc++/trackable.h>

#include "vgGTK/vgGTK.hpp"


namespace vgGTK
{

namespace event
{

namespace device
{

/**
 * @brief	Implements a mouse device that will translate GTK mouse events into vgSDK events.
 */
struct VGGTK_API Mouse : public vgd::event::device::Mouse, public sigc::trackable
{
	/**
	 * @brief	Constructor
	 *
	 * @param	widget		a pointer to the widget whose events will be translated
	 * @param	identifier	the device identifier
	 */
	Mouse( Gtk::Widget * widget, const uint identifier = 0 );
	
private:

	::vgd::event::Location2::Location	m_previousLocation;	///< Holds the previous mouse location.

	/**
	 * @name	GTK Signal Handlers
	 */
	//@{
	/**
	 * @brief	Handles mouse button press and release events.
	 *
	 * @remark This method is intended to get connected to @c button_press_event signals
	 */
	bool onButtonEvent( GdkEventButton * event );

	/**
	 * @brief	Handles motion notificiation events
	 *
	 * @remark This method is intended to get connected to @c motion_notify_event signals
	 */
	bool onMotionNotifyEvent( GdkEventMotion * event );

	/**
	 * @brief	Handles scroll notification events
	 *
	 * @remark This method is intended to get connected to @c scroll_event signals
	 */
	bool onScrollEvent( GdkEventScroll * event );
	//@}

};



} // namespace device

} // namespace event

} // namespace vgGTK



#endif /*_VGGTK_EVENT_MOUSE_HPP_*/
