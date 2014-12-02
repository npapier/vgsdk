//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_EVENT_REFRESHERCALLBACK_HPP
//#define _VGEGLBASE_EVENT_REFRESHERCALLBACK_HPP
//
//#include <vgeGL/event/TimerCallback.hpp>
//
//
//
//namespace vgeGL
//{
//
//namespace event
//{
//
//
///**
// * @brief Force regularly the refresh of the canvas owning this callback
// *
// * @ingroup g_time
// */
//struct VGEGLBASE_API RefresherCallback : public vgeGL::event::TimerCallback
//{
//	/**
//	 * @name Constructors
//	 */
//	//@{
//
//	/**
//	 * @brief Default constructor
//	 */
//	RefresherCallback();
//
//	/**
//	 * @brief Constructor
//	 */
//	RefresherCallback( vgeGL::engine::SceneManager * sceneManager );
//
//	/**
//	 * @brief Constructor
//	 */
//	RefresherCallback( vgd::Shp< vgd::node::Node > node, vgeGL::engine::SceneManager * sceneManager );
//
//	//@}
//
//
//	void apply( const vgd::Shp< vgd::event::TimerEvent > event );
//};
//
//
//} // namespace event
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_EVENT_REFRESHERCALLBACK_HPP
//