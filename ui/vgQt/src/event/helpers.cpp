// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Nicolas Papier

#include <vgQt/event/helpers.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/device/Keyboard.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWidget>
#include <vgDebug/helpers.hpp>


namespace vgQt
{

namespace event
{

const int getKeyboardButton( const QKeyEvent * event )
{
    using vgd::event::KeyboardButtonEvent;

    switch(event->key())
    {
    case Qt::Key_Backspace: 	return KeyboardButtonEvent::KEY_BACK;
    case Qt::Key_Tab:           return KeyboardButtonEvent::KEY_TAB;
    case Qt::Key_Return:        return KeyboardButtonEvent::KEY_RETURN;
    case Qt::Key_Enter:         return KeyboardButtonEvent::KEY_ENTER;
    case Qt::Key_Escape:        return KeyboardButtonEvent::KEY_ESCAPE;
    case Qt::Key_Space:			return KeyboardButtonEvent::KEY_SPACE;
    case Qt::Key_Delete:        return KeyboardButtonEvent::KEY_DELETE;

    case Qt::Key_Cancel:    	return KeyboardButtonEvent::KEY_CANCEL;
    case Qt::Key_Clear:     	return KeyboardButtonEvent::KEY_CLEAR;

    case Qt::Key_Control:       return KeyboardButtonEvent::KEY_CONTROL;
    case Qt::Key_Shift:         return KeyboardButtonEvent::KEY_SHIFT;
    case Qt::Key_Alt:           return KeyboardButtonEvent::KEY_ALT;
    case Qt::Key_Menu:          return KeyboardButtonEvent::KEY_MENU;

    case Qt::Key_Pause:     	return KeyboardButtonEvent::KEY_PAUSE;

    case Qt::Key_PageUp:		return KeyboardButtonEvent::KEY_PRIOR;  /*!< Page up */
    case Qt::Key_PageDown:		return KeyboardButtonEvent::KEY_NEXT;   /*!< Page down */
    case Qt::Key_End:       	return KeyboardButtonEvent::KEY_END;
    case Qt::Key_Home:      	return KeyboardButtonEvent::KEY_HOME;

    case Qt::Key_Left:  		return KeyboardButtonEvent::KEY_LEFT;
    case Qt::Key_Up:        	return KeyboardButtonEvent::KEY_UP;
    case Qt::Key_Right:         return KeyboardButtonEvent::KEY_RIGHT;
    case Qt::Key_Down:      	return KeyboardButtonEvent::KEY_DOWN;

    case Qt::Key_Select:    	return KeyboardButtonEvent::KEY_SELECT;
    case Qt::Key_Print:     	return KeyboardButtonEvent::KEY_PRINT;
    case Qt::Key_Execute:   	return KeyboardButtonEvent::KEY_EXEC;

    case Qt::Key_Insert:        return KeyboardButtonEvent::KEY_INSERT;
    case Qt::Key_Help:      	return KeyboardButtonEvent::KEY_HELP;
    case Qt::Key_0:             return '0';
    case Qt::Key_1:         	return '1';
    case Qt::Key_2:     		return '2';
    case Qt::Key_3: 			return '3';
    case Qt::Key_4:         	return '4';
    case Qt::Key_5:     		return '5';
    case Qt::Key_6: 			return '6';
    case Qt::Key_7:             return '7';
    case Qt::Key_8:         	return '8';
    case Qt::Key_9:             return '9';
    case Qt::Key_multiply:		return KeyboardButtonEvent::KEY_MULTIPLY;

	case Qt::Key_Asterisk:		return KeyboardButtonEvent::KEY_ASTERISK;
    case Qt::Key_Plus:          return KeyboardButtonEvent::KEY_ADD;
    case Qt::Key_Minus:     	return KeyboardButtonEvent::KEY_SUBTRACT;
	case Qt::Key_Period:		return KeyboardButtonEvent::KEY_PERIOD;
	case Qt::Key_Slash:			return KeyboardButtonEvent::KEY_SLASH;

    case Qt::Key_Colon:			return ',';
    case Qt::Key_Semicolon:		return ';';
    case Qt::Key_Less:			return '<';
    case Qt::Key_Equal:			return '=';
    case Qt::Key_Greater:		return '>';
    case Qt::Key_Question:		return '?';
    case Qt::Key_At:			return '@';

    case Qt::Key_A:
    case Qt::Key_B:
    case Qt::Key_C:
    case Qt::Key_D:
    case Qt::Key_E:
    case Qt::Key_F:
    case Qt::Key_G:
    case Qt::Key_H:
    case Qt::Key_I:
    case Qt::Key_J:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_M:
    case Qt::Key_N:
    case Qt::Key_O:
    case Qt::Key_P:
    case Qt::Key_Q:
    case Qt::Key_R:
    case Qt::Key_S:
    case Qt::Key_T:
    case Qt::Key_U:
    case Qt::Key_V:
    case Qt::Key_W:
    case Qt::Key_X:
    case Qt::Key_Y:
    case Qt::Key_Z:
		{
			const QString	text = event->text();
			if( text.isEmpty() )
			{
				return event->key();
			}
			else
			{
				const QByteArray ascii = text.toAscii();
				Q_ASSERT( ascii.length() == 1 );
				return ascii.at( 0 );
			}
		}
		break;

    case Qt::Key_BracketLeft:	return '[';
    case Qt::Key_Backslash:		return '\\';
    case Qt::Key_BracketRight:	return ']';
    case Qt::Key_AsciiCircum:	return '^';
    case Qt::Key_Underscore:	return '_';

    case Qt::Key_F1:			return KeyboardButtonEvent::KEY_F1;
    case Qt::Key_F2:			return KeyboardButtonEvent::KEY_F2;
    case Qt::Key_F3:			return KeyboardButtonEvent::KEY_F3;
    case Qt::Key_F4:			return KeyboardButtonEvent::KEY_F4;
    case Qt::Key_F5:			return KeyboardButtonEvent::KEY_F5;
    case Qt::Key_F6:			return KeyboardButtonEvent::KEY_F6;
    case Qt::Key_F7:			return KeyboardButtonEvent::KEY_F7;
    case Qt::Key_F8:			return KeyboardButtonEvent::KEY_F8;
    case Qt::Key_F9:			return KeyboardButtonEvent::KEY_F9;
    case Qt::Key_F10:			return KeyboardButtonEvent::KEY_F10;
    case Qt::Key_F11:			return KeyboardButtonEvent::KEY_F11;
    case Qt::Key_F12:			return KeyboardButtonEvent::KEY_F12;
    case Qt::Key_F13:			return KeyboardButtonEvent::KEY_F13;
    case Qt::Key_F14:			return KeyboardButtonEvent::KEY_F14;
    case Qt::Key_F15:			return KeyboardButtonEvent::KEY_F15;
    case Qt::Key_F16:			return KeyboardButtonEvent::KEY_F16;
    case Qt::Key_F17:			return KeyboardButtonEvent::KEY_F17;
    case Qt::Key_F18:			return KeyboardButtonEvent::KEY_F18;
    case Qt::Key_F19:			return KeyboardButtonEvent::KEY_F19;
    case Qt::Key_F20:			return KeyboardButtonEvent::KEY_F20;
    case Qt::Key_F21:			return KeyboardButtonEvent::KEY_F21;
    case Qt::Key_F22:			return KeyboardButtonEvent::KEY_F22;
    case Qt::Key_F23:			return KeyboardButtonEvent::KEY_F23;
    case Qt::Key_F24:			return KeyboardButtonEvent::KEY_F24;
    case Qt::Key_NumLock:		return KeyboardButtonEvent::KEY_NUMLOCK;
    case Qt::Key_ScrollLock:	return KeyboardButtonEvent::KEY_SCROLL;

    default:
        vgLogDebug( "Unsupported keyboard key %i (%s).", event->key(), event->text().toStdString().c_str() );
        return 0;
    }
}

const ::vgd::event::ButtonEvent::State getButtonState( const QKeyEvent * event )
{
    switch(event->type())
    {
        case QEvent::KeyPress : return ::vgd::event::ButtonEvent::DOWN;
        case QEvent::KeyRelease : return ::vgd::event::ButtonEvent::UP;

    default : return ::vgd::event::ButtonEvent::UP;
    }
}

const uint32 getButtonId( const QMouseEvent * event )
{
    switch( event->button() )
    {
    case Qt::LeftButton:
        return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_1;

    case Qt::RightButton:
        return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_2;

    case Qt::MiddleButton:
        return ::vgd::event::MouseButtonEvent::MOUSE_BUTTON_3;

    default:
        assert( false && "Unsupported mouse button number.");
        return 0;
    }
}

const ::vgd::event::ButtonEvent::State getButtonState( const QMouseEvent * event )
{
    switch( event->type() )
    {
    case QEvent::MouseButtonPress:
        return ::vgd::event::ButtonEvent::DOWN;

    case QEvent::MouseButtonRelease:
        return ::vgd::event::ButtonEvent::UP;

    default:
        return ::vgd::event::ButtonEvent::UP;
    }
}

const ::vgd::event::Location2::Location getLocation( const QWidget * widget, const QMouseEvent * event )
{
    // Retrieves the location from the event.
    float	locationX = static_cast< float >( event->x() );
    float	locationY = static_cast< float >( widget->height() - event->y() );

    // Job's done.
    return ::vgd::event::Location2::Location( locationX, locationY );
}

const ::vgd::event::Location2::Size getSize( const QWidget * widget )
{
    float width = widget->width();
    float height = widget->height();

    return ::vgd::event::Location2::Location( width, height );
}

void updateGlobalButtonStates( const QMouseEvent * event )
{
    using ::vgd::event::MouseButtonEvent;
    using ::vgd::event::detail::GlobalButtonStateSet;

    // Mouse
    GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_1, event->type() == QEvent::MouseButtonPress && event->button() == Qt::LeftButton );
    GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_2, event->type() == QEvent::MouseButtonPress && event->button() == Qt::RightButton );
    GlobalButtonStateSet::update( MouseButtonEvent::MOUSE_BUTTON_3, event->type() == QEvent::MouseButtonPress && event->button() == Qt::MiddleButton );
}

void updateGlobalButtonStates( const QKeyEvent * event )
{
    using ::vgd::event::ButtonEvent;
    using ::vgd::event::detail::GlobalButtonStateSet;

    GlobalButtonStateSet::update( getKeyboardButton(event), (getButtonState(event) == ButtonEvent::DOWN) );
}


} // namespace event
} // namespace vgQt
