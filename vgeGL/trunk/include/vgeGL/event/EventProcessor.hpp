// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_EVENTPROCESSOR_H
#define _VGEGL_EVENT_EVENTPROCESSOR_H

#include "vgeGL/event/IEventProcessor.hpp"
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace engine
{
	struct SceneManager;
}	

namespace event
{

/**
 * @brief Event processor with a reference on the scene manager.
 */
struct VGEGL_API EventProcessor : public IEventProcessor
{
	/**
	 * @name Constructor
	 */
	//@{
	
	/**
	 * @brief Constructor.
	 * 
	 * @param sceneManager	the linked scene manager.
	 * 
	 * @pre sceneManager != 0
	 */
	EventProcessor( ::vgeGL::engine::SceneManager *sceneManager );
	
	//@}


protected:

	/**
	 * @brief Returns the reference on the linked scene manager.
	 * 
	 * @return the reference on the linked scene manager.
	 */
	::vgeGL::engine::SceneManager *getSceneManager() const { return m_sceneManager; }

private:
	/**
	 * @brief The reference on the scene manager.
	 */
	::vgeGL::engine::SceneManager *m_sceneManager;
};


} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_EVENTPROCESSOR_H
