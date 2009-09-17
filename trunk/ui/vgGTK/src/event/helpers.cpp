// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/event/helpers.hpp"

#include <gdk/gdkkeysyms.h>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgDebug/Global.hpp>



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



// @todo checks this order compared to vgd::event::KeyboardButtonEvent order.
//@todo	Implementation to be done !
const int getKeyboardButton( const GdkEventKey * event )
{
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

	case GDK_Pause:		KeyboardButtonEvent::KEY_PAUSE;
//	KeyboardButtonEvent::KEY_CAPITAL;
	case GDK_Prior:		return KeyboardButtonEvent::KEY_PRIOR;  /*!< Page up */
	case GDK_Next:		return KeyboardButtonEvent::KEY_NEXT;   /*!< Page down */
	case GDK_End:		return KeyboardButtonEvent::KEY_END;
	case GDK_Home:		return KeyboardButtonEvent::KEY_HOME;
	case GDK_Left:		return KeyboardButtonEvent::KEY_LEFT;
	case GDK_Up:		return KeyboardButtonEvent::KEY_UP;
	case GDK_Right:		return KeyboardButtonEvent::KEY_RIGHT;
	case GDK_Down:		return KeyboardButtonEvent::KEY_DOWN;

	case GDK_Select:	return KeyboardButtonEvent::KEY_SELECT;
	case GDK_Print:		return KeyboardButtonEvent::KEY_PRINT;
	case GDK_Execute:	return KeyboardButtonEvent::KEY_EXEC;
//	KeyboardButtonEvent::KEY_SNAPSHOT
	case GDK_Insert:	return KeyboardButtonEvent::KEY_INSERT;
	case GDK_Help:		return KeyboardButtonEvent::KEY_HELP;
	case GDK_KP_0:			return KeyboardButtonEvent::KEY_NUMPAD0;
	case GDK_KP_1:			return KeyboardButtonEvent::KEY_NUMPAD1;
	case GDK_KP_2:			return KeyboardButtonEvent::KEY_NUMPAD2;
	case GDK_KP_3:			return KeyboardButtonEvent::KEY_NUMPAD3;
	case GDK_KP_4:			return KeyboardButtonEvent::KEY_NUMPAD4;
	case GDK_KP_5:			return KeyboardButtonEvent::KEY_NUMPAD5;
	case GDK_KP_6:			return KeyboardButtonEvent::KEY_NUMPAD6;
	case GDK_KP_7:			return KeyboardButtonEvent::KEY_NUMPAD7;
	case GDK_KP_8:			return KeyboardButtonEvent::KEY_NUMPAD8;
	case GDK_KP_9:			return KeyboardButtonEvent::KEY_NUMPAD9;
	case GDK_multiply:		return KeyboardButtonEvent::KEY_MULTIPLY;
//	KeyboardButtonEvent::KEY_SEPARATOR
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
//	KeyboardButtonEvent::KEY_NUMPAD_SEPARATOR
//	KeyboardButtonEvent::KEY_NUMPAD_DECIMAL
//	KeyboardButtonEvent::KEY_NUMPAD_DIVIDE

	case GDK_0:		return '0';
	case GDK_1:		return '1';
	case GDK_2:		return '2';
	case GDK_3:		return '3';
	case GDK_4:		return '4';
	case GDK_5:		return '5';
	case GDK_6:		return '6';
	case GDK_7:		return '7';
	case GDK_8:		return '8';
	case GDK_9:		return '9';
	case GDK_plus:	return KeyboardButtonEvent::KEY_ADD;
	case GDK_minus:	return KeyboardButtonEvent::KEY_SUBTRACT;

	case GDK_colon:			return ',';
	case GDK_semicolon:		return ';';
	case GDK_less:			return '<';
	case GDK_equal:			return '=';
	case GDK_greater:		return '>';
	case GDK_question:		return '?';
	case GDK_at:			return '@';


	case GDK_KP_Add:		return KeyboardButtonEvent::KEY_NUMPAD_ADD;
	case GDK_KP_Subtract:	return KeyboardButtonEvent::KEY_NUMPAD_SUBTRACT;

	case GDK_A:	return 'A';
	case GDK_B:	return 'B';
	case GDK_C:	return 'C';
	case GDK_D:	return 'D';
	case GDK_E:	return 'E';
	case GDK_F:	return 'F';
	case GDK_G:	return 'G';
	case GDK_H:	return 'H';
	case GDK_I:	return 'I';
	case GDK_J:	return 'J';
	case GDK_K:	return 'K';
	case GDK_L:	return 'L';
	case GDK_M:	return 'M';
	case GDK_N:	return 'N';
	case GDK_O:	return 'O';
	case GDK_P:	return 'P';
	case GDK_Q:	return 'Q';
	case GDK_R:	return 'R';
	case GDK_S:	return 'S';
	case GDK_T:	return 'T';
	case GDK_U:	return 'U';
	case GDK_V:	return 'V';
	case GDK_W:	return 'W';
	case GDK_X:	return 'X';
	case GDK_Y:	return 'Y';
	case GDK_Z:	return 'Z';

	case GDK_bracketleft:	return '[';
	case GDK_backslash:		return '\\';
	case GDK_bracketright:	return ']';
	case GDK_asciicircum:	return '^';
	case GDK_underscore:	return '_';
	case GDK_grave:			return '`';
//	case GDK_quoteleft:		return '\'';

	case GDK_a: return 'a';
	case GDK_b: return 'b';
	case GDK_c: return 'c';
	case GDK_d: return 'd';
	case GDK_e: return 'e';
	case GDK_f: return 'f';
	case GDK_g: return 'g';
	case GDK_h: return 'h';
	case GDK_i: return 'i';
	case GDK_j: return 'j';
	case GDK_k: return 'k';
	case GDK_l: return 'l';
	case GDK_m: return 'm';
	case GDK_n: return 'n';
	case GDK_o: return 'o';
	case GDK_p: return 'p';
	case GDK_q: return 'q';
	case GDK_r: return 'r';
	case GDK_s: return 's';
	case GDK_t: return 't';
	case GDK_u: return 'u';
	case GDK_v: return 'v';
	case GDK_w: return 'w';
	case GDK_x: return 'x';
	case GDK_y: return 'y';
	case GDK_z: return 'z';

	default:
		vgDebug::get().logDebug( "Unsupported keyboard key %c (%x).", event->keyval, event->keyval );
		return 0;
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
