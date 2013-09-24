// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGD_EVENT_KEYBOARDBUTTONEVENT_HPP
#define _VGD_EVENT_KEYBOARDBUTTONEVENT_HPP

#include "vgd/event/ButtonEvent.hpp"


namespace vgd
{
	
namespace event
{
	
/**
 * @brief	Implements a keyboard button event class.
 */
struct VGD_API KeyboardButtonEvent : public ButtonEvent
{
	/**
	 * @brief	Defines key values.
	 */
	enum {
	 KEY_BACK    =    8,
	 KEY_TAB     =    9,
	 KEY_RETURN  =    13,
	 KEY_ESCAPE  =    27,
	 KEY_SPACE   =    32,
	 KEY_DELETE  =    127,
	
	 KEY_START   = 300,
	 KEY_LBUTTON,
	 KEY_RBUTTON,
	 KEY_CANCEL,
	 KEY_MBUTTON,
	 KEY_CLEAR,
	 KEY_SHIFT,
	 KEY_ALT,
	 KEY_CONTROL,
	 KEY_MENU,
	 KEY_PAUSE,
	 KEY_CAPITAL,
	 KEY_PRIOR,  /*!< Page up */
	 KEY_NEXT,   /*!< Page down */
	 KEY_END,
	 KEY_HOME,
	 KEY_LEFT,
	 KEY_UP,
	 KEY_RIGHT,
	 KEY_DOWN,
	 KEY_SELECT,
	 KEY_PRINT,
	 KEY_EXEC,
	 KEY_SNAPSHOT,
	 KEY_INSERT,
	 KEY_HELP,
	 KEY_NUMPAD0,
	 KEY_NUMPAD1,
	 KEY_NUMPAD2,
	 KEY_NUMPAD3,
	 KEY_NUMPAD4,
	 KEY_NUMPAD5,
	 KEY_NUMPAD6,
	 KEY_NUMPAD7,
	 KEY_NUMPAD8,
	 KEY_NUMPAD9,
	 KEY_MULTIPLY,
	 KEY_ASTERISK,
	 KEY_ADD,
	 KEY_SEPARATOR,
	 KEY_SUBTRACT,
	 KEY_PERIOD,
	 KEY_SLASH,
	 KEY_ENTER,
	 KEY_DECIMAL,
	 KEY_DIVIDE,

	 KEY_F1,
	 KEY_F2,
	 KEY_F3,
	 KEY_F4,
	 KEY_F5,
	 KEY_F6,
	 KEY_F7,
	 KEY_F8,
	 KEY_F9,
	 KEY_F10,
	 KEY_F11,
	 KEY_F12,
	 KEY_F13,
	 KEY_F14,
	 KEY_F15,
	 KEY_F16,
	 KEY_F17,
	 KEY_F18,
	 KEY_F19,
	 KEY_F20,
	 KEY_F21,
	 KEY_F22,
	 KEY_F23,
	 KEY_F24,
	 KEY_NUMLOCK,
	 KEY_SCROLL,
	 KEY_PAGEUP,
	 KEY_PAGEDOWN,
	
	 KEY_NUMPAD_SPACE,
	 KEY_NUMPAD_TAB,
	 KEY_NUMPAD_ENTER,
	 KEY_NUMPAD_F1,
	 KEY_NUMPAD_F2,
	 KEY_NUMPAD_F3,
	 KEY_NUMPAD_F4,
	 KEY_NUMPAD_HOME,
	 KEY_NUMPAD_LEFT,
	 KEY_NUMPAD_UP,
	 KEY_NUMPAD_RIGHT,
	 KEY_NUMPAD_DOWN,
	 KEY_NUMPAD_PRIOR,
	 KEY_NUMPAD_PAGEUP,
	 KEY_NUMPAD_NEXT,
	 KEY_NUMPAD_PAGEDOWN,
	 KEY_NUMPAD_END,
	 KEY_NUMPAD_BEGIN,
	 KEY_NUMPAD_INSERT,
	 KEY_NUMPAD_DELETE,
	 KEY_NUMPAD_EQUAL,
	 KEY_NUMPAD_MULTIPLY,
	 KEY_NUMPAD_ADD,
	 KEY_NUMPAD_SEPARATOR,
	 KEY_NUMPAD_SUBTRACT,
	 KEY_NUMPAD_DECIMAL,
	 KEY_NUMPAD_DIVIDE
	};
	 
	/**
	 * @brief	Constructor
	 * 
	 * @param	source			a pointer to the source fo the event
	 * @param	buttonStates	a reference to the button state set
	 * @param	buttonID			a key whose state changed
	 * @param	state				a button state
	 */
	KeyboardButtonEvent( Source *source, const ButtonStateSet& buttonStates, const int32 buttonID, const State state );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~KeyboardButtonEvent();
	
	// overridden method
	void accept( vgd::event::EventVisitor& eventVisitor );
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_KEYBOARDBUTTONEVENT_HPP
