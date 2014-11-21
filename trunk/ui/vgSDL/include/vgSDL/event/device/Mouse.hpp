// VGSDK - Copyright (C) 2009, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest

#ifndef _VGSDL_EVENT_DEVICE_MOUSE_HPP_
#define _VGSDL_EVENT_DEVICE_MOUSE_HPP_

#include <vgd/Wkp.hpp>
#include <vgd/event/device/Mouse.hpp>
#include <vgd/event/Location2.hpp>

#include "vgSDL/vgSDL.hpp"

#include <SDL_events.h>
#include <SDL_mouse.h>



namespace vgSDL
{

namespace event
{

namespace device
{

/**
 * @brief Implement a SDL based mouse.
 */
struct VGSDL_API Mouse : public ::vgd::event::device::Mouse
{

	/**
	 * @brief Destructor.
	 */
	~Mouse();

	/**
	 * @name	SDL Event Handling
	 */
	//@{
	static void handleEvent(const SDL_MouseMotionEvent & event);
	static void handleEvent(const SDL_MouseButtonEvent & event);
	//@}

	/**
	 * @brief	Searches for a mouse at the given index.
	 *
	 * @param	index	an index for a mouse
	 *
	 * @return	a shared pointer to a mouse, empty if none
	 */
	static vgd::Shp< Mouse > find( const int index );

	/**
	 * @brief	Retrieves the mouse with the given index, or create
	 * 			one if none exists.
	 *
	 *
	 * @param	index	an index for a mouse
	 *
	 * @return	a shared pointer to a mouse, empty on error
	 *
	 * @see		getNames, find
	 */
	static vgd::Shp< Mouse > get( const int index );


private:

	/**
	 * @brief Constructor
	 *
	 * @param identifier	the device identifier
	 */
	Mouse( const uint identifier = 0 );

	/**
	 * @brief Holds the previous mouse location.
	 */
	::vgd::event::Location2::Location	m_previousLocation;

	typedef std::vector< vgd::Wkp< Mouse >  >	MiceCollection;

	/**
	 * @brief The collection of joystick already in use.
	 */
	static MiceCollection	m_mouseCache;


};



} // namespace device

} // namespace event

} // namespace vgSDL

#endif // _VGSDL_EVENT_DEVICE_MOUSE_HPP_
