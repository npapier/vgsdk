// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/event/helpers.hpp"

#include <gdk/gdkkeysyms.h>
#include <vgd/event/KeyboardButtonEvent.hpp>



namespace vgGTK
{

namespace event
{

namespace
{

	template< typename GdkEventType >
	void updateGlobalModifierButtonStates( const GdkEventType * event )
	{
		using ::vgd::event::KeyboardButtonEvent;
		using ::vgd::event::detail::GlobalButtonStateSet;

		GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_CONTROL,	(event->state & GDK_CONTROL_MASK) != 0 );
		GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_SHIFT,	(event->state & GDK_SHIFT_MASK) != 0 );
		GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_ALT,		(event->state & GDK_MOD1_MASK) != 0 );
	}
}



const uint32 getButtonId( const GdkEventButton * event )
{
	switch( event->button )
	{
	case 1:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_1;

	case 2:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_2;

	case 3:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_3;

	default:
		assert( false && "Unsupported mouse button number.");
		return 0;
	}
}



const ::vgd::event::ButtonEvent::State getButtonState( const GdkEventButton * event )
{
	switch( event->type )
	{
	case GDK_BUTTON_PRESS:
		return ::vgd::event::ButtonEvent::DOWN;

	case GDK_BUTTON_RELEASE:
		return ::vgd::event::ButtonEvent::UP;

	case GDK_2BUTTON_PRESS:
	case GDK_3BUTTON_PRESS:	// @todo Handle properly triple clicks.
		return ::vgd::event::ButtonEvent::DCLICK;

	default:
		assert( false && "Unsupported mouse button state." );
		return ::vgd::event::ButtonEvent::UP;
	}
}



const ::vgd::event::ButtonEvent::State getButtonState( const GdkEventKey * event )
{
	switch( event->type )
	{
	case GDK_KEY_PRESS:		return ::vgd::event::ButtonEvent::DOWN;
	case GDK_KEY_RELEASE:	return ::vgd::event::ButtonEvent::UP;

	default:
		assert( false && "Unsupported keyboard button state." );
		return ::vgd::event::ButtonEvent::UP;
	}
}



const int getKeyboardButton( const GdkEventKey * event )
{
//@todo	Implementation to be done !
	
	using vgd::event::KeyboardButtonEvent;

	switch( event->keyval )
	{
	case GDK_BackSpace:	return KeyboardButtonEvent::KEY_BACK;
	case GDK_Tab:		return KeyboardButtonEvent::KEY_TAB;
	case GDK_Return:	return KeyboardButtonEvent::KEY_RETURN;
	case GDK_Escape:	return KeyboardButtonEvent::KEY_ESCAPE;
	case ' ':			return KeyboardButtonEvent::KEY_SPACE;
	case GDK_Delete:	return KeyboardButtonEvent::KEY_DELETE;

//	KeyboardButtonEvent::KEY_START
//	KeyboardButtonEvent::KEY_LBUTTON
//	KeyboardButtonEvent::KEY_RBUTTON
//	KeyboardButtonEvent::KEY_CANCEL
//	KeyboardButtonEvent::KEY_MBUTTON
//	KeyboardButtonEvent::KEY_CLEAR

	case GDK_Shift_L:	return KeyboardButtonEvent::KEY_SHIFT;
	case GDK_Shift_R:	return KeyboardButtonEvent::KEY_SHIFT;
	case GDK_Alt_L:		return KeyboardButtonEvent::KEY_ALT;
	case GDK_Alt_R:		return KeyboardButtonEvent::KEY_ALT;
	case GDK_Control_L:	return KeyboardButtonEvent::KEY_CONTROL;
	case GDK_Control_R:	return KeyboardButtonEvent::KEY_CONTROL;
	case GDK_Meta_L:	return KeyboardButtonEvent::KEY_MENU;
	case GDK_Meta_R:	return KeyboardButtonEvent::KEY_MENU;

//	KeyboardButtonEvent::KEY_PAUSE;
//	KeyboardButtonEvent::KEY_CAPITAL;
//	KeyboardButtonEvent::KEY_PRIOR  /*!< Page up */
//	KeyboardButtonEvent::KEY_NEXT   /*!< Page down */
//	KeyboardButtonEvent::KEY_END
//	KeyboardButtonEvent::KEY_HOME
//	KeyboardButtonEvent::KEY_LEFT
//	KeyboardButtonEvent::KEY_UP
//	KeyboardButtonEvent::KEY_RIGHT
//	KeyboardButtonEvent::KEY_DOWN
//	KeyboardButtonEvent::KEY_SELECT
//	KeyboardButtonEvent::KEY_PRINT
//	KeyboardButtonEvent::KEY_EXEC
//	KeyboardButtonEvent::KEY_SNAPSHOT
//	KeyboardButtonEvent::KEY_INSERT
//	KeyboardButtonEvent::KEY_HELP
//	KeyboardButtonEvent::KEY_NUMPAD0
//	KeyboardButtonEvent::KEY_NUMPAD1
//	KeyboardButtonEvent::KEY_NUMPAD2
//	KeyboardButtonEvent::KEY_NUMPAD3
//	KeyboardButtonEvent::KEY_NUMPAD4
//	KeyboardButtonEvent::KEY_NUMPAD5
//	KeyboardButtonEvent::KEY_NUMPAD6
//	KeyboardButtonEvent::KEY_NUMPAD7
//	KeyboardButtonEvent::KEY_NUMPAD8
//	KeyboardButtonEvent::KEY_NUMPAD9
//	KeyboardButtonEvent::KEY_MULTIPLY
//	KeyboardButtonEvent::KEY_ADD
//	KeyboardButtonEvent::KEY_SEPARATOR
//	KeyboardButtonEvent::KEY_SUBTRACT
//	KeyboardButtonEvent::KEY_DECIMAL
//	KeyboardButtonEvent::KEY_DIVIDE
//
//	KeyboardButtonEvent::KEY_F1
//	KeyboardButtonEvent::KEY_F2
//	KeyboardButtonEvent::KEY_F3
//	KeyboardButtonEvent::KEY_F4
//	KeyboardButtonEvent::KEY_F5
//	KeyboardButtonEvent::KEY_F6
//	KeyboardButtonEvent::KEY_F7
//	KeyboardButtonEvent::KEY_F8
//	KeyboardButtonEvent::KEY_F9
//	KeyboardButtonEvent::KEY_F10
//	KeyboardButtonEvent::KEY_F11
//	KeyboardButtonEvent::KEY_F12
//	KeyboardButtonEvent::KEY_F13
//	KeyboardButtonEvent::KEY_F14
//	KeyboardButtonEvent::KEY_F15
//	KeyboardButtonEvent::KEY_F16
//	KeyboardButtonEvent::KEY_F17
//	KeyboardButtonEvent::KEY_F18
//	KeyboardButtonEvent::KEY_F19
//	KeyboardButtonEvent::KEY_F20
//	KeyboardButtonEvent::KEY_F21
//	KeyboardButtonEvent::KEY_F22
//	KeyboardButtonEvent::KEY_F23
//	KeyboardButtonEvent::KEY_F24
//	KeyboardButtonEvent::KEY_NUMLOCK
//	KeyboardButtonEvent::KEY_SCROLL
//	KeyboardButtonEvent::KEY_PAGEUP
//	KeyboardButtonEvent::KEY_PAGEDOWN
//
//	KeyboardButtonEvent::KEY_NUMPAD_SPACE
//	KeyboardButtonEvent::KEY_NUMPAD_TAB
//	KeyboardButtonEvent::KEY_NUMPAD_ENTER
//	KeyboardButtonEvent::KEY_NUMPAD_F1
//	KeyboardButtonEvent::KEY_NUMPAD_F2
//	KeyboardButtonEvent::KEY_NUMPAD_F3
//	KeyboardButtonEvent::KEY_NUMPAD_F4
//	KeyboardButtonEvent::KEY_NUMPAD_HOME
//	KeyboardButtonEvent::KEY_NUMPAD_LEFT
//	KeyboardButtonEvent::KEY_NUMPAD_UP
//	KeyboardButtonEvent::KEY_NUMPAD_RIGHT
//	KeyboardButtonEvent::KEY_NUMPAD_DOWN
//	KeyboardButtonEvent::KEY_NUMPAD_PRIOR
//	KeyboardButtonEvent::KEY_NUMPAD_PAGEUP
//	KeyboardButtonEvent::KEY_NUMPAD_NEXT
//	KeyboardButtonEvent::KEY_NUMPAD_PAGEDOWN
//	KeyboardButtonEvent::KEY_NUMPAD_END
//	KeyboardButtonEvent::KEY_NUMPAD_BEGIN
//	KeyboardButtonEvent::KEY_NUMPAD_INSERT
//	KeyboardButtonEvent::KEY_NUMPAD_DELETE
//	KeyboardButtonEvent::KEY_NUMPAD_EQUAL
//	KeyboardButtonEvent::KEY_NUMPAD_MULTIPLY
//	KeyboardButtonEvent::KEY_NUMPAD_ADD
//	KeyboardButtonEvent::KEY_NUMPAD_SEPARATOR
//	KeyboardButtonEvent::KEY_NUMPAD_SUBTRACT
//	KeyboardButtonEvent::KEY_NUMPAD_DECIMAL
//	KeyboardButtonEvent::KEY_NUMPAD_DIVIDE

	default:	return 0;
	}
}



void updateGlobalButtonStates( const GdkEventButton * event )
{
	using ::vgd::event::MouseButtonEvent;
	using ::vgd::event::detail::GlobalButtonStateSet;

	// Clean all
//	GlobalButtonStateSet::clear();

	updateGlobalModifierButtonStates( event );

	// Mouse
	GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_1, event->type == GDK_BUTTON_PRESS && event->button == 1 );
	GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_2, event->type == GDK_BUTTON_PRESS && event->button == 2 );
	GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_3, event->type == GDK_BUTTON_PRESS && event->button == 3 );

}



void updateGlobalButtonStates( const GdkEventKey * event )
{
	using ::vgd::event::ButtonEvent;
	using ::vgd::event::detail::GlobalButtonStateSet;

	updateGlobalModifierButtonStates( event );

	GlobalButtonStateSet::update( getKeyboardButton(event), (getButtonState(event) == ButtonEvent::DOWN) );
}



void updateGlobalButtonStates( const GdkEventMotion * event )
{
	updateGlobalModifierButtonStates( event );
}



void updateGlobalButtonStates( const GdkEventScroll * event )
{
	updateGlobalModifierButtonStates( event );
}



} // namespace event

} // namespace vgGTK
