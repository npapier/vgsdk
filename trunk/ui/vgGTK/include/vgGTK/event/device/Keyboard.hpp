// VGSDK - Copyright (C) 2008, 2009, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_DEVICE_KEYBOARD_HPP_
#define _VGGTK_EVENT_DEVICE_KEYBOARD_HPP_

#include <gtkmm/Widget.h>
#include <vgd/event/device/Keyboard.hpp>
#include <sigc++/trackable.h>

#include "vgGTK/vgGTK.hpp"


namespace vgGTK
{

namespace event
{

namespace device
{



/**
 * @brief	Implements a keyboard device that translates GTK key events into vgSDK events.
 *
 * @remark	This device will not handle the @code tab key since it can involve inconsistancy in the global
 *		button state set due to the focus lost.
 */
struct VGGTK_API Keyboard : public vgd::event::device::Keyboard, public sigc::trackable
{
	/**
	 * @name	Constructor
	 *
	 * @param	widget	a pointer to a widget whose key events will be translated
	 */
	Keyboard( Gtk::Widget * widget );

private:

	/**
	 * @brief	Handles GTK key events of the widget passed at construction
	 */
	bool onKeyEvent( GdkEventKey * event );
};



} // namespace device

} // namespace event

} // namespace vgGTK



#endif /*_VGGTK_EVENT_DEVICE_KEYBOARD_HPP_*/
