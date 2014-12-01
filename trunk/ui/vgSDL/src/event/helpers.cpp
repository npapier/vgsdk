// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller, Nicolas Papier, Philippe Sengchanpheng.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#include <vgSDL/event/helpers.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/device/Keyboard.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgDebug/helpers.hpp>

#include <iostream>

namespace vgSDL
{

namespace event
{

const int getKeyboardButton(const SDL_Event * event)
{
    using vgd::event::KeyboardButtonEvent;
	SDL_KeyboardEvent keyboardEvent = event->key;
	
	//if (keyboardEvent.type == SDL_TEXTINPUT)
	//{
	//	return (int)event->text.text[0];
	//}

	switch (keyboardEvent.keysym.sym)
    {
	case SDLK_BACKSPACE: 	return KeyboardButtonEvent::KEY_BACK;
    case SDLK_TAB:          return KeyboardButtonEvent::KEY_TAB;
    case SDLK_RETURN:       return KeyboardButtonEvent::KEY_RETURN;
	//case SDLK_ENTER:        return KeyboardButtonEvent::KEY_ENTER;
    case SDLK_ESCAPE:       return KeyboardButtonEvent::KEY_ESCAPE;
    case SDLK_SPACE:		return KeyboardButtonEvent::KEY_SPACE;
    case SDLK_DELETE:       return KeyboardButtonEvent::KEY_DELETE;

	//case SDLK_CANCEL:    	return KeyboardButtonEvent::KEY_CANCEL;
    case SDLK_CLEAR:     	return KeyboardButtonEvent::KEY_CLEAR;

    case SDLK_RCTRL:      return KeyboardButtonEvent::KEY_CONTROL;
	case SDLK_LCTRL:      return KeyboardButtonEvent::KEY_CONTROL;
    case SDLK_RSHIFT:        return KeyboardButtonEvent::KEY_SHIFT;
	case SDLK_LSHIFT:        return KeyboardButtonEvent::KEY_SHIFT;
    case SDLK_RALT:          return KeyboardButtonEvent::KEY_ALT;
	case SDLK_LALT:          return KeyboardButtonEvent::KEY_ALT;
    case SDLK_MENU:         return KeyboardButtonEvent::KEY_MENU;

    case SDLK_PAUSE:     	return KeyboardButtonEvent::KEY_PAUSE;

    case SDLK_PAGEUP:		return KeyboardButtonEvent::KEY_PRIOR;  /*!< Page up */
    case SDLK_PAGEDOWN:		return KeyboardButtonEvent::KEY_NEXT;   /*!< Page down */
    case SDLK_END:       	return KeyboardButtonEvent::KEY_END;
    case SDLK_HOME:      	return KeyboardButtonEvent::KEY_HOME;

    case SDLK_LEFT:  		return KeyboardButtonEvent::KEY_LEFT;
    case SDLK_UP:        	return KeyboardButtonEvent::KEY_UP;
    case SDLK_RIGHT:         return KeyboardButtonEvent::KEY_RIGHT;
    case SDLK_DOWN:      	return KeyboardButtonEvent::KEY_DOWN;

	//case SDLK_SELECT:    	return KeyboardButtonEvent::KEY_SELECT;
	case SDLK_PRINTSCREEN:  return KeyboardButtonEvent::KEY_PRINT;
	//case SDLK_EXECUTE:   	return KeyboardButtonEvent::KEY_EXEC;

    case SDLK_INSERT:       return KeyboardButtonEvent::KEY_INSERT;
    case SDLK_HELP:      	return KeyboardButtonEvent::KEY_HELP;
    case SDLK_0:            return '0';
    case SDLK_1:         	return '1';
    case SDLK_2:     		return '2';
    case SDLK_3: 			return '3';
    case SDLK_4:         	return '4';
    case SDLK_5:     		return '5';
    case SDLK_6: 			return '6';
    case SDLK_7:            return '7';
    case SDLK_8:         	return '8';
    case SDLK_9:            return '9';
	//case SDLK_MULTIPLY:		return KeyboardButtonEvent::KEY_MULTIPLY;

	case SDLK_ASTERISK:		return KeyboardButtonEvent::KEY_ASTERISK;
    case SDLK_PLUS:         return KeyboardButtonEvent::KEY_ADD;
    case SDLK_MINUS:     	return KeyboardButtonEvent::KEY_SUBTRACT;
	case SDLK_PERIOD:		return KeyboardButtonEvent::KEY_PERIOD;
	case SDLK_SLASH:		return KeyboardButtonEvent::KEY_SLASH;

	case SDLK_COLON:		return ':';
    case SDLK_SEMICOLON:	return ';';
    case SDLK_LESS:			return '<';
	case SDLK_EQUALS:		return '=';
    case SDLK_GREATER:		return '>';
    case SDLK_QUESTION:		return '?';
    case SDLK_AT:			return '@';

	case SDLK_EXCLAIM:		return '!';
	case SDLK_QUOTEDBL:		return '"';
	case SDLK_HASH:			return '#';
	case SDLK_DOLLAR:		return '$';
	case SDLK_AMPERSAND:	return '&';
	case SDLK_QUOTE:		return '\'';
	case SDLK_COMMA:		return ',';	

	case SDLK_a:
	case SDLK_b:
	case SDLK_c:
	case SDLK_d:
	case SDLK_e:
	case SDLK_f:
	case SDLK_g:
	case SDLK_h:
	case SDLK_i:
	case SDLK_j:
	case SDLK_k:
	case SDLK_l:
	case SDLK_m:
	case SDLK_n:
	case SDLK_o:
	case SDLK_p:
	case SDLK_q:
	case SDLK_r:
	case SDLK_s:
	case SDLK_t:
	case SDLK_u:
	case SDLK_v:
	case SDLK_w:
	case SDLK_x:
	case SDLK_y:
	case SDLK_z:
	{	
		return SDL_GetKeyName(event->key.keysym.sym)[0];
	}

	case SDLK_LEFTPAREN:	return '(';
	case SDLK_RIGHTPAREN:	return ')';
    case SDLK_LEFTBRACKET:	return '[';
	case SDLK_BACKSLASH:	return '\\';
    case SDLK_RIGHTBRACKET:	return ']';
    case SDLK_CARET:		return '^';
    case SDLK_UNDERSCORE:	return '_';
	case SDLK_BACKQUOTE:	return '`';

    case SDLK_F1:			return KeyboardButtonEvent::KEY_F1;
    case SDLK_F2:			return KeyboardButtonEvent::KEY_F2;
    case SDLK_F3:			return KeyboardButtonEvent::KEY_F3;
    case SDLK_F4:			return KeyboardButtonEvent::KEY_F4;
    case SDLK_F5:			return KeyboardButtonEvent::KEY_F5;
    case SDLK_F6:			return KeyboardButtonEvent::KEY_F6;
    case SDLK_F7:			return KeyboardButtonEvent::KEY_F7;
    case SDLK_F8:			return KeyboardButtonEvent::KEY_F8;
    case SDLK_F9:			return KeyboardButtonEvent::KEY_F9;
    case SDLK_F10:			return KeyboardButtonEvent::KEY_F10;
    case SDLK_F11:			return KeyboardButtonEvent::KEY_F11;
    case SDLK_F12:			return KeyboardButtonEvent::KEY_F12;
    case SDLK_F13:			return KeyboardButtonEvent::KEY_F13;
    case SDLK_F14:			return KeyboardButtonEvent::KEY_F14;
    case SDLK_F15:			return KeyboardButtonEvent::KEY_F15;
    //case SDLK_F16:			return KeyboardButtonEvent::KEY_F16;
    //case SDLK_F17:			return KeyboardButtonEvent::KEY_F17;
    //case SDLK_F18:			return KeyboardButtonEvent::KEY_F18;
    //case SDLK_F19:			return KeyboardButtonEvent::KEY_F19;
    //case SDLK_F20:			return KeyboardButtonEvent::KEY_F20;
    //case SDLK_F21:			return KeyboardButtonEvent::KEY_F21;
    //case SDLK_F22:			return KeyboardButtonEvent::KEY_F22;
    //case SDLK_F23:			return KeyboardButtonEvent::KEY_F23;
    //case SDLK_F24:			return KeyboardButtonEvent::KEY_F24;
	case SDLK_NUMLOCKCLEAR:	return KeyboardButtonEvent::KEY_NUMLOCK;
	case SDLK_SCROLLLOCK:	return KeyboardButtonEvent::KEY_SCROLL;

	case SDLK_KP_0:			return KeyboardButtonEvent::KEY_NUMPAD0;
	case SDLK_KP_1:			return KeyboardButtonEvent::KEY_NUMPAD1;
	case SDLK_KP_2:			return KeyboardButtonEvent::KEY_NUMPAD2;
	case SDLK_KP_3:			return KeyboardButtonEvent::KEY_NUMPAD3;
	case SDLK_KP_4:			return KeyboardButtonEvent::KEY_NUMPAD4;
	case SDLK_KP_5:			return KeyboardButtonEvent::KEY_NUMPAD5;
	case SDLK_KP_6:			return KeyboardButtonEvent::KEY_NUMPAD6;
	case SDLK_KP_7:			return KeyboardButtonEvent::KEY_NUMPAD7;
	case SDLK_KP_8:			return KeyboardButtonEvent::KEY_NUMPAD8;
	case SDLK_KP_9:			return KeyboardButtonEvent::KEY_NUMPAD9;
	case SDLK_KP_PERIOD:	return KeyboardButtonEvent::KEY_NUMPAD_DELETE;
	case SDLK_KP_DIVIDE:	return KeyboardButtonEvent::KEY_NUMPAD_DIVIDE;
	case SDLK_KP_MULTIPLY:	return KeyboardButtonEvent::KEY_NUMPAD_MULTIPLY;
	case SDLK_KP_MINUS:		return KeyboardButtonEvent::KEY_NUMPAD_SUBTRACT;
	case SDLK_KP_PLUS:		return KeyboardButtonEvent::KEY_NUMPAD_ADD;
	case SDLK_KP_ENTER:		return KeyboardButtonEvent::KEY_NUMPAD_ENTER;
	case SDLK_KP_EQUALS:	return KeyboardButtonEvent::KEY_NUMPAD_EQUAL;

    default:
		vgLogDebug("Unsupported keyboard key %i (%s).", SDL_GetScancodeName(keyboardEvent.keysym.scancode), SDL_GetKeyName(keyboardEvent.keysym.sym));
        return 0;
    }
}

const ::vgd::event::ButtonEvent::State getButtonState(const SDL_Event * event)
{
    switch(event->key.state)
    {
		case SDL_PRESSED : return ::vgd::event::ButtonEvent::DOWN;
		case SDL_RELEASED: return ::vgd::event::ButtonEvent::UP;

		default : return ::vgd::event::ButtonEvent::UP;
    }
}

void updateGlobalButtonStates(const SDL_Event * event)
{
    using ::vgd::event::ButtonEvent;
    using ::vgd::event::detail::GlobalButtonStateSet;

    GlobalButtonStateSet::update( getKeyboardButton(event), (getButtonState(event) == ButtonEvent::DOWN) );

}

void updateGlobalButtonStates(const SDL_MouseButtonEvent * event)
{
	using ::vgd::event::MouseButtonEvent;
	using ::vgd::event::detail::GlobalButtonStateSet;


	// Mouse
	GlobalButtonStateSet::update(MouseButtonEvent::MOUSE_BUTTON_1, event->type == SDL_MOUSEBUTTONDOWN && event->button == SDL_BUTTON_LEFT);
	GlobalButtonStateSet::update(MouseButtonEvent::MOUSE_BUTTON_2, event->type == SDL_MOUSEBUTTONDOWN && event->button == SDL_BUTTON_RIGHT);
	GlobalButtonStateSet::update(MouseButtonEvent::MOUSE_BUTTON_3, event->type == SDL_MOUSEBUTTONDOWN && event->button == SDL_BUTTON_MIDDLE);

}

const ::vgd::event::ButtonEvent::State getButtonState(const SDL_MouseButtonEvent * event)
{
	switch (event->state)
	{
	case SDL_PRESSED:
		return ::vgd::event::ButtonEvent::DOWN;

	case SDL_RELEASED:
		return ::vgd::event::ButtonEvent::UP;

	default:
		assert(false && "Unsupported mouse button state.");
		return ::vgd::event::ButtonEvent::UP;
	}
}


const uint32 getButtonId(const SDL_MouseButtonEvent * event)
{
	switch (event->button)
	{
	case SDL_BUTTON_LEFT:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_1;

	case SDL_BUTTON_RIGHT:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_2;

	case SDL_BUTTON_MIDDLE:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_3;

	case SDL_BUTTON_X1:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_4;

	case SDL_BUTTON_X2:
		return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_5;

	default:
		assert(false && "Unsupported mouse button number.");
		return 0;
	}
}

const ::vgd::event::Location2::Location getLocation(const SDL_MouseMotionEvent * event)
{
	SDL_Window* window = SDL_GetMouseFocus();
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	// Retrieves the location from the event.
	float	locationX = static_cast< float >(event->x);
	float	locationY = static_cast< float >(height - event->y);

	// Job's done.
	return ::vgd::event::Location2::Location(locationX, locationY);
}

const ::vgd::event::Location2::Location getLocation(const SDL_MouseButtonEvent * event)
{
	SDL_Window* window = SDL_GetMouseFocus();
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	// Retrieves the location from the event.
	float	locationX = static_cast< float >(event->x);
	float	locationY = static_cast< float >(height - event->y);

	// Job's done.
	return ::vgd::event::Location2::Location(locationX, locationY);
}

const ::vgd::event::Location2::Size getSize()
{
	SDL_Window* window = SDL_GetMouseFocus();
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	return ::vgd::event::Location2::Location(width, height);
}


} // namespace event
} // namespace vgQt
