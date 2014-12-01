// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgd/event/detail/helpers.hpp"

#include "vgd/event/device/Joystick.hpp"
#include "vgd/event/KeyboardButtonEvent.hpp"
#include "vgd/event/MouseButtonEvent.hpp"



namespace vgd
{

namespace event
{

namespace detail
{



const std::string toString( const ButtonEvent::State state )
{
	switch( state )
	{
		case ButtonEvent::UP:		return "Up";
		case ButtonEvent::DOWN:		return "Down";
		case ButtonEvent::DCLICK:	return "Double Click";
		default:					return "Unknown Button State";
	}
}



// @todo Several keys not supported
const std::string toString( const int32 button )
{
	using ::vgd::event::device::Joystick;

	if ( button >= 32 && button <= 126 )
	{
		return std::string( 1, static_cast<char>(button) );
	}

	switch( button )
	{
		case MouseButtonEvent::MOUSE_BUTTON_1:	return "Mouse Button 1";
		case MouseButtonEvent::MOUSE_BUTTON_2:	return "Mouse Button 2";
		case MouseButtonEvent::MOUSE_BUTTON_3:	return "Mouse Button 3";
		case MouseButtonEvent::MOUSE_BUTTON_4:	return "Mouse Button 4";
		case MouseButtonEvent::MOUSE_BUTTON_5:	return "Mouse Button 5";

		case KeyboardButtonEvent::KEY_BACK:		return "Keyboard Button Back";
		case KeyboardButtonEvent::KEY_TAB:		return "Keyboard Button Tabulation";
		case KeyboardButtonEvent::KEY_RETURN:	return "Keyboard Button Return";
		case KeyboardButtonEvent::KEY_ESCAPE:	return "Keyboard Button Escape";
		case KeyboardButtonEvent::KEY_SPACE:	return "Keyboard Button Space";
		case KeyboardButtonEvent::KEY_DELETE:	return "Keyboard Button Delete";
		case KeyboardButtonEvent::KEY_START:	return "Keyboard Button Start";
		case KeyboardButtonEvent::KEY_LBUTTON:	return "Keyboard Button LButton";
		case KeyboardButtonEvent::KEY_RBUTTON:	return "Keyboard Button RButton";
		case KeyboardButtonEvent::KEY_CANCEL:	return "Keyboard Button Cancel";
		case KeyboardButtonEvent::KEY_MBUTTON:	return "Keyboard Button MButton";
		case KeyboardButtonEvent::KEY_CLEAR:	return "Keyboard Button Clear";
		case KeyboardButtonEvent::KEY_SHIFT:	return "Keyboard Button Shift";
		case KeyboardButtonEvent::KEY_ALT:		return "Keyboard Button Alt";
		case KeyboardButtonEvent::KEY_CONTROL:	return "Keyboard Button Control";
		case KeyboardButtonEvent::KEY_MENU:		return "Keyboard Button Menu";
		case KeyboardButtonEvent::KEY_PAUSE:	return "Keyboard Button Pause";
		case KeyboardButtonEvent::KEY_CAPITAL:	return "Keyboard Button Capital";
		case KeyboardButtonEvent::KEY_PRIOR:	return "Keyboard Button Prior";
		case KeyboardButtonEvent::KEY_NEXT :	return "Keyboard Button Next";
		case KeyboardButtonEvent::KEY_END:		return "Keyboard Button End";
		case KeyboardButtonEvent::KEY_HOME:		return "Keyboard Button Home";
		case KeyboardButtonEvent::KEY_LEFT:		return "Keyboard Button Left";
		case KeyboardButtonEvent::KEY_UP:		return "Keyboard Button Up";
		case KeyboardButtonEvent::KEY_RIGHT:	return "Keyboard Button Right";
		case KeyboardButtonEvent::KEY_DOWN:		return "Keyboard Button Down";
		case KeyboardButtonEvent::KEY_SELECT:	return "Keyboard Button Select";
		case KeyboardButtonEvent::KEY_PRINT:	return "Keyboard Button Print";
		case KeyboardButtonEvent::KEY_EXEC:		return "Keyboard Button Exec";
		case KeyboardButtonEvent::KEY_SNAPSHOT:	return "Keyboard Button Snapshot";
		case KeyboardButtonEvent::KEY_INSERT:	return "Keyboard Button Insert";
		case KeyboardButtonEvent::KEY_HELP:		return "Keyboard Button Help";

		case KeyboardButtonEvent::KEY_NUMPAD0:	return "Keyboard Button Numpad 0";
		case KeyboardButtonEvent::KEY_NUMPAD1:	return "Keyboard Button Numpad 1";
		case KeyboardButtonEvent::KEY_NUMPAD2:	return "Keyboard Button Numpad 2";
		case KeyboardButtonEvent::KEY_NUMPAD3:	return "Keyboard Button Numpad 3";
		case KeyboardButtonEvent::KEY_NUMPAD4:	return "Keyboard Button Numpad 4";
		case KeyboardButtonEvent::KEY_NUMPAD5:	return "Keyboard Button Numpad 5";
		case KeyboardButtonEvent::KEY_NUMPAD6:	return "Keyboard Button Numpad 6";
		case KeyboardButtonEvent::KEY_NUMPAD7:	return "Keyboard Button Numpad 7";
		case KeyboardButtonEvent::KEY_NUMPAD8:	return "Keyboard Button Numpad 8";
		case KeyboardButtonEvent::KEY_NUMPAD9:	return "Keyboard Button Numpad 9";

		case KeyboardButtonEvent::KEY_MULTIPLY:	return "Keyboard Button Multiply";
		case KeyboardButtonEvent::KEY_ADD:		return "Keyboard Button Add";
		case KeyboardButtonEvent::KEY_SEPARATOR:return "Keyboard Button Separator";
		case KeyboardButtonEvent::KEY_SUBTRACT:	return "Keyboard Button Substract";
		case KeyboardButtonEvent::KEY_DECIMAL:	return "Keyboard Button Decimal";
		case KeyboardButtonEvent::KEY_DIVIDE:	return "Keyboard Button Divide";

		case KeyboardButtonEvent::KEY_F1:		return "Keyboard Button F1";
		case KeyboardButtonEvent::KEY_F2:		return "Keyboard Button F2";
		case KeyboardButtonEvent::KEY_F3:		return "Keyboard Button F3";
		case KeyboardButtonEvent::KEY_F4:		return "Keyboard Button F4";
		case KeyboardButtonEvent::KEY_F5:		return "Keyboard Button F5";
		case KeyboardButtonEvent::KEY_F6:		return "Keyboard Button F6";
		case KeyboardButtonEvent::KEY_F7:		return "Keyboard Button F7";
		case KeyboardButtonEvent::KEY_F8:		return "Keyboard Button F8";
		case KeyboardButtonEvent::KEY_F9:		return "Keyboard Button F9";
		case KeyboardButtonEvent::KEY_F10:		return "Keyboard Button F10";
		case KeyboardButtonEvent::KEY_F11:		return "Keyboard Button F11";
		case KeyboardButtonEvent::KEY_F12:		return "Keyboard Button F12";
		case KeyboardButtonEvent::KEY_F13:		return "Keyboard Button F13";
		case KeyboardButtonEvent::KEY_F14:		return "Keyboard Button F14";
		case KeyboardButtonEvent::KEY_F15:		return "Keyboard Button F15";
		case KeyboardButtonEvent::KEY_F16:		return "Keyboard Button F16";
		case KeyboardButtonEvent::KEY_F17:		return "Keyboard Button F17";
		case KeyboardButtonEvent::KEY_F18:		return "Keyboard Button F18";
		case KeyboardButtonEvent::KEY_F19:		return "Keyboard Button F19";
		case KeyboardButtonEvent::KEY_F20:		return "Keyboard Button F20";
		case KeyboardButtonEvent::KEY_F21:		return "Keyboard Button F21";
		case KeyboardButtonEvent::KEY_F22:		return "Keyboard Button F22";
		case KeyboardButtonEvent::KEY_F23:		return "Keyboard Button F23";
		case KeyboardButtonEvent::KEY_F24:		return "Keyboard Button F24";

		case KeyboardButtonEvent::KEY_NUMLOCK:	return "Keyboard Button Numlock";
		case KeyboardButtonEvent::KEY_SCROLL:	return "Keyboard Button Scroll";
		case KeyboardButtonEvent::KEY_PAGEUP:	return "Keyboard Button PageUp";
		case KeyboardButtonEvent::KEY_PAGEDOWN:	return "Keyboard Button PageDown";

		case KeyboardButtonEvent::KEY_NUMPAD_SPACE:		return "Keyboard Button Numpad Space";
		case KeyboardButtonEvent::KEY_NUMPAD_TAB:		return "Keyboard Button Numpad Tab";
		case KeyboardButtonEvent::KEY_NUMPAD_ENTER:		return "Keyboard Button Numpad Enter";
		case KeyboardButtonEvent::KEY_NUMPAD_F1:		return "Keyboard Button Numpad F1";
		case KeyboardButtonEvent::KEY_NUMPAD_F2:		return "Keyboard Button Numpad F2";
		case KeyboardButtonEvent::KEY_NUMPAD_F3:		return "Keyboard Button Numpad F3";
		case KeyboardButtonEvent::KEY_NUMPAD_F4:		return "Keyboard Button Numpad F4";
		case KeyboardButtonEvent::KEY_NUMPAD_HOME:		return "Keyboard Button Numpad Home";
		case KeyboardButtonEvent::KEY_NUMPAD_LEFT:		return "Keyboard Button Numpad Left";
		case KeyboardButtonEvent::KEY_NUMPAD_UP:		return "Keyboard Button Numpad Up";
		case KeyboardButtonEvent::KEY_NUMPAD_RIGHT:		return "Keyboard Button Numpad Right";
		case KeyboardButtonEvent::KEY_NUMPAD_DOWN:		return "Keyboard Button Numpad Down";
		case KeyboardButtonEvent::KEY_NUMPAD_PRIOR:		return "Keyboard Button Numpad Prior";
		case KeyboardButtonEvent::KEY_NUMPAD_PAGEUP:	return "Keyboard Button Numpad PageUp";
		case KeyboardButtonEvent::KEY_NUMPAD_NEXT:		return "Keyboard Button Numpad Next";
		case KeyboardButtonEvent::KEY_NUMPAD_PAGEDOWN:	return "Keyboard Button Numpad PageDown";
		case KeyboardButtonEvent::KEY_NUMPAD_END:		return "Keyboard Button Numpad End";
		case KeyboardButtonEvent::KEY_NUMPAD_BEGIN:		return "Keyboard Button Numpad Begin";
		case KeyboardButtonEvent::KEY_NUMPAD_INSERT:	return "Keyboard Button Numpad Insert";
		case KeyboardButtonEvent::KEY_NUMPAD_DELETE:	return "Keyboard Button Numpad Delete";
		case KeyboardButtonEvent::KEY_NUMPAD_EQUAL:		return "Keyboard Button Numpad Equal";
		case KeyboardButtonEvent::KEY_NUMPAD_MULTIPLY:	return "Keyboard Button Numpad Multiply";
		case KeyboardButtonEvent::KEY_NUMPAD_ADD:		return "Keyboard Button Numpad Add";
		case KeyboardButtonEvent::KEY_NUMPAD_SEPARATOR:	return "Keyboard Button Numpad Separator";
		case KeyboardButtonEvent::KEY_NUMPAD_SUBTRACT:	return "Keyboard Button Numpad Substract";
		case KeyboardButtonEvent::KEY_NUMPAD_DECIMAL:	return "Keyboard Button Numpad Decimal";
		case KeyboardButtonEvent::KEY_NUMPAD_DIVIDE:	return "Keyboard Button Numpad Divide";

		case Joystick::BUTTON_1:		return "Joystick Button 1";
		case Joystick::BUTTON_2:		return "Joystick Button 2";
		case Joystick::BUTTON_3:		return "Joystick Button 3";
		case Joystick::BUTTON_4:		return "Joystick Button 4";
		case Joystick::BUTTON_5:		return "Joystick Button 5";
		case Joystick::BUTTON_6:		return "Joystick Button 6";
		case Joystick::BUTTON_7:		return "Joystick Button 7";
		case Joystick::BUTTON_8:		return "Joystick Button 8";
		case Joystick::BUTTON_9:		return "Joystick Button 9";
		case Joystick::BUTTON_10:		return "Joystick Button 10";
		case Joystick::BUTTON_11:		return "Joystick Button 11";
		case Joystick::BUTTON_12:		return "Joystick Button 12";
		case Joystick::BUTTON_13:		return "Joystick Button 13";
		case Joystick::BUTTON_14:		return "Joystick Button 14";
		case Joystick::BUTTON_15:		return "Joystick Button 15";
		case Joystick::BUTTON_16:		return "Joystick Button 16";
		case Joystick::BUTTON_17:		return "Joystick Button 17";
		case Joystick::BUTTON_18:		return "Joystick Button 18";
		case Joystick::BUTTON_19:		return "Joystick Button 19";
		case Joystick::BUTTON_20:		return "Joystick Button 20";
		case Joystick::BUTTON_21:		return "Joystick Button 21";
		case Joystick::BUTTON_22:		return "Joystick Button 22";
		case Joystick::BUTTON_23:		return "Joystick Button 23";
		case Joystick::BUTTON_24:		return "Joystick Button 24";
		case Joystick::BUTTON_25:		return "Joystick Button 25";
		case Joystick::BUTTON_26:		return "Joystick Button 26";
		case Joystick::BUTTON_27:		return "Joystick Button 27";
		case Joystick::BUTTON_28:		return "Joystick Button 28";
		case Joystick::BUTTON_29:		return "Joystick Button 29";
		case Joystick::BUTTON_30:		return "Joystick Button 30";
		case Joystick::BUTTON_31:		return "Joystick Button 31";
		case Joystick::BUTTON_32:		return "Joystick Button 32";

		default:	return "Unknown Button";
	}
}



const std::string toString( const HatEvent::State state )
{
	std::string	result;

	if( state == HatEvent::CENTERED	)	result =  "Centered";
	if( state &  HatEvent::UP		)	result += "Up ";
	if( state &  HatEvent::RIGHT	)	result += "Right";
	if( state &  HatEvent::DOWN		)	result += "Down ";
	if( state &  HatEvent::LEFT		)	result += "Left";

	return result;
}



const std::string toString( const MouseWheelEvent::Axis axis )
{
	switch( axis )
	{
		case MouseWheelEvent::HORIZONTAL:	return "Horizontal Axis";
		case MouseWheelEvent::VERTICAL:		return "Vertical Axis";
		default:							return "Unknown Axis";
	}
}



} // namespace detail

} // namespace event

} // namespace vgd
