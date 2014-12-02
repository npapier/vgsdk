//// VGSDK - Copyright (C) 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_EVENT_SLIDEWINDOW_HPP
//#define _VGEGLBASE_EVENT_SLIDEWINDOW_HPP
//
//#include "vgeGLBase/event/TimerCallback.hpp"
//#include "vgeGLBase/technique/MultiMain.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace event
//{
//
//
///**
// * @brief Moves a window from one position to another one.
// *
// * @todo path, multi-path =>TransfertFunc ?
// */
//struct SlideWindow : public vgeGLBase::event::TimerCallback
//{
//	/**
//	 * @brief Default constructor
//	 */
//	VGEGLBASE_API SlideWindow( vgeGLBase::engine::SceneManager * sceneManager );
//
//	/**
//	 * @brief Resets window movements.
//	 */
//	VGEGLBASE_API void reset();
//
//	/**
//	 * @brief Adds a new window movement
//	 *
//	 * @param window		the window to move
//	 * @param destination	position and size of the window at the end of the animation
//	 * @param visible		visibility of the window at the end of the animation
//	 *
//	 * @pre window != 0
//	 */
//	VGEGLBASE_API void add(	vgd::Shp< vgeGLBase::technique::MultiMain::Window > window,
//						const vgm::Rectangle2f	destination, const bool visible );
//
//	/**
//	 * @name Overridden method
//	 */
//	//@{
//	VGEGLBASE_API void apply( const vgd::Shp< vgd::event::TimerEvent > event );
//
//	VGEGLBASE_API void endExecution( const vgd::Shp< vgd::event::TimerEvent > event );
//	//@}
//
//protected:
//	struct WindowInfo
//	{
//		vgd::Shp< vgeGLBase::technique::MultiMain::Window > window;
//		vgm::Vec4f										destination;
//		bool											visible;
//
//		vgm::Vec4f										source;
//	};
//private:
//	std::vector< WindowInfo > m_window;
//};
//
//
//
//} // namespace event
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_EVENT_SLIDEWINDOW_HPP
//