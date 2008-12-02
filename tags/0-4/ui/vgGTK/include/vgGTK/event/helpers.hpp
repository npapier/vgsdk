// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_EVENT_HELPERS_HPP_
#define _VGGTK_EVENT_HELPERS_HPP_

#include <gdk/gdk.h>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>



namespace vgGTK
{

namespace event
{



/**
 * @brief	Helper that retrieves the vgSDK mouse button identifier from the given gdk button event
 *
 * @param	event	a pointer to a gdk button event
 *
 * @return	the vgSDK button identifier
 */
const uint32 getButtonId( const GdkEventButton * event );



/**
 * @brief	Helper that retrieves the vgSDK button state from the given gdk button event
 *
 * @param	event	a pointer to a gdk button event
 *
 * @return	the vgSDK button state
 */
const ::vgd::event::ButtonEvent::State getButtonState( const GdkEventButton * event );



/**
 * @brief	Helper that retrieves the vgSDK button state from the given gdk key event
 *
 * @param	event	a pointer to a gdk key event
 *
 * @return	the vgSDK button state
 */
const ::vgd::event::ButtonEvent::State getButtonState( const GdkEventKey * event );



/**
 * @brief	Helper that retrieves the location of the mouse for the given GdkEventType instance.
 *
 * This function can take any GdkEventType structure that have a @c window field, an @c x field and a @c y field,
 * like @c GdkEventButton and @c GdkEventMotion have.
 *
 * @remark	The location's coordinate system is translated so the origin is located in the buttom left
 * 			corner of the window.
 *
 * @param	event	a pointer to a gdk event
 *
 * @return	the vgSDK location
 */
template< typename GdkEventType >
const ::vgd::event::Location2::Location getLocation( const GdkEventType * event )
{
	// Retrieves some properties of the window.
	gint	x;
	gint	y;
	gint	width;
	gint	height;
	gint	depth;

	gdk_window_get_geometry( event->window, &x, &y, &width, &height, &depth );


	// Retrieves the location from the event.
	float	locationX = static_cast< float >( event->x );
	float	locationY = static_cast< float >( height ) - static_cast< float >( event->y );


	// Job's done.
	return ::vgd::event::Location2::Location( locationX, locationY );
}




/**
 * @brief	Helper that retrieves the size of the surface (or window) for the given GdkEventType instance.
 *
 * This function can take any GdkEventType structure that have a @c window field
 * like @c GdkEventButton and @c GdkEventMotion have.
 *
 * @param	event	a pointer to a gdk event
 *
 * @return	the vgSDK size
 */
template< typename GdkEventType >
const ::vgd::event::Location2::Size getSize( const GdkEventType * event )
{
	// Retrieves some properties of the window.
	gint	x;
	gint	y;
	gint	width;
	gint	height;
	gint	depth;

	gdk_window_get_geometry( event->window, &x, &y, &width, &height, &depth );


	// Job's done.
	return ::vgd::event::Location2::Size( static_cast< float >(width), static_cast< float >(height) );
}



/**
 * @brief	Retrieves the vgSDK keyboard button identifier from the given GdkEventKey structure.
 *
 * @param	event a pointer to a GdkEventKey structure
 *
 * @return	a vgSDK keyboard button
 *
 * @see		vgd::event::KeyboardButtonEvent
 */
const int getKeyboardButton( const GdkEventKey * event );



/**
 * @brief	Helps to update the global button state for a given @c GdkEventButton notification.
 *
 * @param	event	a pointer to an event
 */
void updateGlobalButtonStates( const GdkEventButton * event );



/**
 * @brief	Helps to update the global button state for a given @c GdkEventKey notification.
 *
 * @param	event	a pointer to an event
 */
void updateGlobalButtonStates( const GdkEventKey * event );



/**
 * @brief	Helps to update the global button state for a given @c GdkEventMotion notification.
 *
 * @param	event	a pointer to an event
 */
void updateGlobalButtonStates( const GdkEventMotion * event );



/**
 * @brief	Helps to update the global button state for a given @c GdkEventScroll notification.
 *
 * @param	event	a pointer to an event
 */
void updateGlobalButtonStates( const GdkEventScroll * event );



} // namespace event

} // namespace vgGTK



#endif /*_VGGTK_EVENT_HELPERS_HPP_*/
