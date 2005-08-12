// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_DEFAULTEVENTPROCESSOR_H
#define _VGEGL_EVENT_DEFAULTEVENTPROCESSOR_H

#include "vgeGL/event/EventProcessor.hpp"
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
 * @brief Process an incoming event by using service ProcessEvent on the scene graph.
 * 
 * This is the default event processor in vgsdk used to process event for draggers classes.
 */
struct VGEGL_API DefaultEventProcessor : public EventProcessor
{
	/**
	 * @brief Constructor.
	 * 
	 * @param sceneManager	the linked scene manager.
	 */
	DefaultEventProcessor( ::vgeGL::engine::SceneManager *sceneManager );
	
	// Overrides
	const bool onEvent( vgd::Shp<vgd::event::Event> event );
};

} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_DEFAULTEVENTPROCESSOR_H
