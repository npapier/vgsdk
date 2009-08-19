// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_SLIDEWINDOW_HPP
#define _VGEGL_EVENT_SLIDEWINDOW_HPP

#include "vgeGL/event/TimerCallback.hpp"
#include "vgeGL/technique/MultiMain.hpp"



namespace vgeGL
{

namespace event
{


/**
 * @brief Moves a window from one position to another one.
 *
 * @todo path, multi-path =>TransfertFunc ?
 */
struct SlideWindow : public vgeGL::event::TimerCallback
{
	/**
	 * @brief Default constructor
	 */
	VGEGL_API SlideWindow( vgeGL::engine::SceneManager * sceneManager );

	/**
	 * @brief Resets window movements.
	 */
	VGEGL_API void reset();

	/**
	 * @brief Adds a new window movement
	 *
	 * @param window		the window to move
	 * @param destination	position and size of the window at the end of the animation
	 * @param visible		visibility of the window at the end of the animation
	 *
	 * @pre window != 0
	 */
	VGEGL_API void add(	vgd::Shp< vgeGL::technique::MultiMain::Window > window,
				const vgm::Rectangle2f	destination, const bool visible );

	/**
	 * @name Overridden method
	 */
	//@{
	VGEGL_API void apply( const vgd::Shp< vgd::event::TimerEvent > event );

	VGEGL_API void endExecution();
	//@}

protected:
	struct WindowInfo
	{
		vgd::Shp< vgeGL::technique::MultiMain::Window > window;
		vgm::Vec4f										destination;
		bool											visible;

		vgm::Vec4f										source;
	};
private:
	std::vector< WindowInfo > m_window;
};



} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_SLIDEWINDOW_HPP