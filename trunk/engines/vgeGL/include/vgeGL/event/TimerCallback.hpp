// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_TIMERCALLBACK_HPP
#define _VGEGL_EVENT_TIMERCALLBACK_HPP

#include <vgd/event/TimerCallback.hpp>
#include "vgeGL/vgeGL.hpp"

namespace vgeGL { namespace engine { struct SceneManager; } }



namespace vgeGL
{

namespace event
{


/**
 * @brief Specialized version of TimerCallback
 */
struct VGEGL_API TimerCallback : public vgd::event::TimerCallback
{
	/**
	 * @name Constructors
	 */
	//@{

	/**
	 * @copydoc vgd::event::TimerCallback::TimerCallback()
	 *
	 * @post getSceneManager() == 0
	 */
	TimerCallback();

	/**
	 * @brief Constructor storing a scene manager reference for future usage in apply method.
	 *
	 * @copydetails vgd::event::TimerCallback::TimerCallback()
	 *
	 * @param sceneManager		a reference on a scene manager
	 * @post getSceneManager() == sceneManager
	 */
	TimerCallback( vgeGL::engine::SceneManager * sceneManager );

	/**
	 * @brief Constructor storing a node reference and a scene manager reference for future usage in apply method.
	 *
	 * @copydetails vgd::event::TimerCallback::TimerCallback()
	 *
	 * @param node			a shared pointer on the node to store
	 * @param sceneManager		a reference on a scene manager
	 * @post getSceneManager() == sceneManager
	 */
	TimerCallback( vgd::Shp< vgd::node::Node > node, vgeGL::engine::SceneManager * sceneManager );

	//@}


	/**
	 * @brief Retrieves the scene manager reference stored by this callback
	 *
	 * @return the scene manager reference stored by this callback
	 */
	vgeGL::engine::SceneManager * getSceneManager();


protected:
	vgeGL::engine::SceneManager	*m_sceneManager;	///< the scene manager reference stored by this callback.	
};


} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_TIMERCALLBACK_HPP
