// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_KEYBOARD_HPP_
#define _VGGTK_EVENT_KEYBOARD_HPP_

#include <vgd/event/Keyboard.hpp>

#include "vgGTK/event/SignalHandler.hpp"



namespace vgGTK
{

namespace event
{



/**
 * @brief	Implements a keyboard event device for GTK widgets.
 *
 * @remark	This device will not handle the @code tab key since it can involve inconsistancy in the global
 *		button state set due to the focus lost.
 */
struct VGGTK_API Keyboard : public ::vgd::event::Keyboard, public SignalHandler
{

	/**
	 * @name	Overrides
	 */
	//@{
	void connect( Gtk::Widget * widget );
	//@}


private:

	/**
	 * @name	GTK Signal Callbacks
	 */
	//@{
	/**
	 * @brief	Handles any key event notifications (press or release).
	 *
	 * @remark Will skip @code tab key events to avoid inconsistancy problems due to
	 *		the focus lost.
	 */
	bool onKeyEvent( GdkEventKey * event );
	//@}
};



} // namespace event

} // namespace vgGTK



#endif /*_VGGTK_EVENT_KEYBOARD_HPP_*/
