// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_MOUSE_HPP_
#define _VGGTK_EVENT_MOUSE_HPP_

#include <gdk/gdk.h>
#include <vgd/event/Location2.hpp>
#include <vgd/event/Mouse.hpp>

#include <vgGTK/vgGTK.hpp>
#include "vgGTK/event/SignalHandler.hpp"



namespace vgGTK
{

namespace event
{



/**
 * @brief	Implements a mouse event device for GTK widgets
 *
 * In order to generate events for the vgSDK objects,
 * you must connect an Mouse instance as a signal handler to a Gtk::Widget.
 */
struct VGGTK_API Mouse : public ::vgd::event::Mouse, public SignalHandler
{

	/**
	 * @brief	Constructor
	 */
	Mouse();


	/**
	 * @name	Overrides
	 */
	//@{
	void connect( Gtk::Widget * widget );
	//@}


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



} // namespace event

} // namespace vgGTK



#endif /*_VGGTK_EVENT_MOUSE_HPP_*/
