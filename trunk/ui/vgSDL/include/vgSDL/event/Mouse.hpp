#ifndef _VGSDL_EVENT_MOUSE_HPP_
#define _VGSDL_EVENT_MOUSE_HPP_

#include<vgSDL/vgSDL.hpp>
#include <vgd/WeakPtr.hpp>
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
	 * @brief Destructor.
	 */

	~Mouse();

	/**
	 * @name	SDL Event Handling
	 */
	//@{
	static void handleEvent( const SDL_Event & event );
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
	 * @brief Creator.
	 */

	Mouse();

	/**
	 * @brief Holds the previous mouse location.
	 */

	::vgd::event::Location2::Location	m_previousLocation;

	typedef std::vector< vgd::WeakPtr< Mouse >  >	MiceCollection;

	/**
	 * @brief The collection of joystick already in use.
	 */
	static MiceCollection	m_mouseCache;


};


} // namespace event
} // namespace vgSDL

#endif // _VGSDL_EVENT_MOUSE_HPP_
