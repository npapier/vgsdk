//// VGSDK - Copyright (C) 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_EVENT_TIMERCALLBACK_HPP
//#define _VGEGLBASE_EVENT_TIMERCALLBACK_HPP
//
//#include <vgd/event/TimerCallback.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//
//namespace vgeGLBase { namespace engine { struct SceneManager; } }
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
// * @brief Specialized version of TimerCallback
// *
// * @ingroup g_time
// */
//struct VGEGLBASE_API TimerCallback : public vgd::event::TimerCallback
//{
//	/**
//	 * @name Constructors
//	 */
//	//@{
//
//	/**
//	 * @copydoc vgd::event::TimerCallback::TimerCallback()
//	 *
//	 * @post getSceneManager() == 0
//	 */
//	TimerCallback();
//
//	/**
//	 * @brief Constructor storing a scene manager reference for future usage in apply method.
//	 *
//	 * @copydetails vgd::event::TimerCallback::TimerCallback()
//	 *
//	 * @param sceneManager		a reference on a scene manager
//	 * @post getSceneManager() == sceneManager
//	 */
//	TimerCallback( vgeGLBase::engine::SceneManager * sceneManager );
//
//	/**
//	 * @brief Constructor storing a node reference and a scene manager reference for future usage in apply method.
//	 *
//	 * @copydetails vgd::event::TimerCallback::TimerCallback()
//	 *
//	 * @param node			a shared pointer on the node to store
//	 * @param sceneManager		a reference on a scene manager
//	 * @post getSceneManager() == sceneManager
//	 */
//	TimerCallback( vgd::Shp< vgd::node::Node > node, vgeGLBase::engine::SceneManager * sceneManager );
//
//	//@}
//
//
//	/**
//	 * @brief Retrieves the scene manager reference stored by this callback
//	 *
//	 * @return the scene manager reference stored by this callback
//	 */
//	vgeGLBase::engine::SceneManager * getSceneManager();
//
//
//protected:
//	vgeGLBase::engine::SceneManager	*m_sceneManager;	///< the scene manager reference stored by this callback.	
//};
//
//
//} // namespace event
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_EVENT_TIMERCALLBACK_HPP
//