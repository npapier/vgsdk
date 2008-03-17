// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGSDL_EVENT_EVENT_HPP_
#define _VGSDL_EVENT_EVENT_HPP_

#include <vgSDL/vgSDL.hpp>



namespace vgSDL
{

namespace event
{


/**
 * @name	SDL Event Handling
 */
//@{
/**
 * @brief	Process one SDL event, translate it into the appropriate vgSDK event
 * 			and then return execution control.
 *
 * @return	the number of processed event (0 or 1).
 *
 * @remark	In order to receive SDL events, you must have called @c SDL_Init with
 * 			@c SDL_INIT_VIDEO and @c SDL_INIT_JOYSTICK flags. You also must have enabled
 * 			joystick events by calling @c SDL_JoystickEventState(SDL_ENABLE)
 *
 * @remark	The processed SDL event is removed from the event queue.
 */
VGSDL_API const int processEvent();

/**
 * @brief	Process SDL events waiting in the queue, translate them into appropriate vgSDL events
 * 			and then returns execution control.
 *
 * Is the event queue is empty, the execution control is returned immediatly.
 *
 * @param	number	the maximum number of events to process (10 by defaults)
 *
 * @return	the number of processed events (from 0 to @c number)
 *
 * @remark	In order to receive SDL events, you must have called @c SDL_Init with
 * 			@c SDL_INIT_VIDEO and @c SDL_INIT_JOYSTICK flags. You also must have enabled
 * 			joystick events by calling @c SDL_JoystickEventState(SDL_ENABLE)
 *
 * @remark	The processed SDL events are removed from the event queue.
 */
VGSDL_API const int processEvents( const int number = 10 );
//@}



}

}

#endif /*_VGSDL_EVENT_EVENT_HPP_*/
