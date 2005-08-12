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
 * @brief Event processor with a reference on a scene manager.
 */
struct VGEGL_API EventProcessor : public IEventProcessor
{
	/**
	 * @brief Constructor.
	 * 
	 * @param sceneManager	the linked scene manager.
	 */
	EventProcessor( ::vgeGL::engine::SceneManager *sceneManager );
	
protected:
	/**
	 * @brief A reference on a scene manager.
	 */
	::vgeGL::engine::SceneManager *m_sceneManager;
};

} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_EVENTPROCESSOR_H
