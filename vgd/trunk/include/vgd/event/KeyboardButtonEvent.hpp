// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_KEYBOARDBUTTONEVENT_H
#define _VGD_EVENT_KEYBOARDBUTTONEVENT_H


#include "vgd/vgd.hpp"
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
	enum Key {
		ANY = 0, UNDEFINED = 1, LEFT_SHIFT = 0xffe1, RIGHT_SHIFT,
		LEFT_CONTROL, RIGHT_CONTROL, LEFT_ALT = 0xffe9, RIGHT_ALT,
		NUMBER_0 = 0x0030, NUMBER_1, NUMBER_2, NUMBER_3,
		NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7,
		NUMBER_8, NUMBER_9, A = 0x0061, B,
		C, D, E, F,
		G, H, I, J,
		K, L, M, N,
		O, P, Q, R,
		S, T, U, V,
		W, X, Y, Z,
		HOME = 0xff50, LEFT_ARROW, UP_ARROW, RIGHT_ARROW,
		DOWN_ARROW, PAGE_UP, PAGE_DOWN, END,
		PRIOR = 0xff55, NEXT, PAD_ENTER = 0xff8d, PAD_F1 = 0xff91,
		PAD_F2, PAD_F3, PAD_F4, PAD_0 = 0xff9e,
		PAD_1 = 0xff9c, PAD_2 = 0xff99, PAD_3 = 0xff9b, PAD_4 = 0xff96,
		PAD_5 = 0xff9d, PAD_6 = 0xff98, PAD_7 = 0xff95, PAD_8 = 0xff97,
		PAD_9 = 0xff9a, PAD_ADD = 0xffab, PAD_SUBTRACT = 0xffad, PAD_MULTIPLY = 0xffaa,
		PAD_DIVIDE = 0xffaf, PAD_SPACE = 0xff8d, PAD_TAB = 0xff89, PAD_INSERT = 0xff9e,
		PAD_DELETE = 0xff9f, PAD_PERIOD = 0xff9f, F1 = 0xffbe, F2,
		F3, F4, F5, F6,
		F7, F8, F9, F10,
		F11, F12, BACKSPACE = 0xff08, TAB = 0xff09,
		RETURN = 0xff0d, ENTER = 0xff0d, PAUSE = 0xff13, SCROLL_LOCK = 0xff14,
		ESCAPE = 0xff1b, DELETE = 0xffff, KEY_DELETE = DELETE, PRINT = 0xff61,
		INSERT = 0xff63, NUM_LOCK = 0xff7f, CAPS_LOCK = 0xffe5, SHIFT_LOCK = 0xffe6,
		SPACE = 0x0020, APOSTROPHE = 0x0027, COMMA = 0x002c, MINUS = 0x002d,
		PERIOD = 0x002e, SLASH = 0x002f, SEMICOLON = 0x003b, EQUAL = 0x003d,
		BRACKETLEFT = 0x005b, BACKSLASH = 0x005c, BRACKETRIGHT = 0x005d, GRAVE = 0x0060 
    };
	
	/**
	 * @brief	Constructor
	 * 
	 * @param	source	a pointer to the source fo the event
	 * @param	state	a button state
	 * @param	key		a key whose state changed
	 */
	KeyboardButtonEvent( Source *source, State state, Key key );
	
	/**
	 * @brief	Destructor
	 */
	virtual ~KeyboardButtonEvent();
	
	/**
	 * @brief	Retrieves the key whose state changed.
	 * 
	 * @return	a key
	 */
	Key getKey() const;
	
private:

	/**
	 * @brief	The kay whose state changed.
	 */
	Key key;
};


} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_KEYBOARDBUTTONEVENT_H
