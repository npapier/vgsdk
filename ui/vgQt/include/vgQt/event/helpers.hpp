// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_HELPERS_HPP_
#define _VGQT_EVENT_HELPERS_HPP_

#include <vgd/event/device/Keyboard.hpp>
#include <vgd/event/ButtonEvent.hpp>
#include <vgd/event/Location2.hpp>
#include <QKeyEvent>
#include <QMouseEvent>

namespace vgQt
{

namespace event
{
// mouse
/**
 * @brief	Helper that retrieves the vgSDK mouse button identifier from the given Qt mouse event.
 *
 * @param	event	a pointer to a Qt mouse event.
 *
 * @return	the vgSDK button identifier.
 */
const uint32 getButtonId( const QMouseEvent * event );

/**
 * @brief	Helper that retrieves the vgSDK button state from the given Qt mouse event.
 *
 * @param	event	a pointer to a Qt mouse event.
 *
 * @return	the vgSDK button state.
 */
const ::vgd::event::ButtonEvent::State getButtonState( const QMouseEvent * event );

/**
 * @brief	Helper that retrieves the location of the mouse for the given Qt mouse event.
 *
 * @remark	The location's coordinate system is translated so the origin is located in the buttom left
 * 			corner of the window.
 *
 * @param   widget  a pointer to a Qt widgets.
 *
 * @param	event	a pointer to a gdk event.
 *
 * @return	the vgSDK location.
 */
const ::vgd::event::Location2::Location getLocation( const QWidget * widget, const QMouseEvent * event );


// keyboard
/**
 * @brief	Retrieves the vgSDK keyboard button identifier from the given Qt Key event.
 *
 * @param	event a pointer to a Qt Key event.
 *
 * @return	a vgSDK keyboard button.
 *
 * @see		vgd::event::KeyboardButtonEvent.
 */
const int getKeyboardButton( const QKeyEvent * event );

/**
 * @brief	Helper that retrieves the vgSDK button state from the given Qt Key event.
 *
 * @param	event	a pointer to a Qt Key event.
 *
 * @return	the vgSDK button state.
 */
const ::vgd::event::ButtonEvent::State getButtonState( const QKeyEvent * event );

/**
 * @brief	Helper that retrieves the size of the surface (or window) for the given QWidget.
 *
 * @param	event	a pointer to a Qwidget.
 *
 * @return	the vgSDK size.
 */
const ::vgd::event::Location2::Size getSize( const QWidget * widget );

/**
 * @brief	Helps to update the global button state for a given QKeyEvent notification.
 *
 * @param	event	a pointer to an event.
 */
void updateGlobalButtonStates( const QKeyEvent * event );

/**
 * @brief	Helps to update the global button state for a given QKeyEvent notification.
 *
 * @param	event	a pointer to an event.
 */
void updateGlobalButtonStates( const QMouseEvent * event );


} // namespace event
} // namespace vgQt

#endif // _VGQT_EVENT_HELPERS_HPP_
