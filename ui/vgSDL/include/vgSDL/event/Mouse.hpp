#ifndef _VGSDL_EVENT_MOUSE_HPP_
#define _VGSDL_EVENT_MOUSE_HPP_

#include<vgSDL/vgSDL.hpp>
#include <vgd/event/Mouse.hpp>
#include <vgd/event/Location2.hpp>
//#include <SDL.h>

union SDL_Event;

namespace vgSDL
{
namespace event
{

/**
 * @brief Implement a SDL based mouse.
 */

struct VGSDL_API Mouse : public ::vgd::event::Mouse
{

	/**
	 * @brief Creator.
	 */

	Mouse();

	/**
	 * @brief Destructor.
	 */

	~Mouse();

	/**
	 * @name	SDL Event Handling
	 */
	//@{
	void handleEvent( const SDL_Event & event );
	//@}

private:
	::vgd::event::Location2::Location	m_previousLocation;	///< Holds the previous mouse location.

};


} // namespace event
} // namespace vgSDL

#endif // _VGSDL_EVENT_MOUSE_HPP_
