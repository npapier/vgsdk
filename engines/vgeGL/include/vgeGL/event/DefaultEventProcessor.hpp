// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_DEFAULTEVENTPROCESSOR_HPP
#define _VGEGL_EVENT_DEFAULTEVENTPROCESSOR_HPP

#include "vgeGL/event/EventProcessor.hpp"



namespace vgeGL
{

namespace event
{


/**
 * @brief Process an incoming event by using service ProcessEvent on the scene graph.
 * 
 * This is the default event processor in vgsdk used to process event for draggers classes.
 */
struct DefaultEventProcessor : public EventProcessor
{
	/**
	 * @brief Constructor
	 * 
	 * @param sceneManager	the linked scene manager.
	 * 
	 * @pre sceneManager != 0
	 */
	VGEGL_API DefaultEventProcessor( ::vgeGL::engine::SceneManager *sceneManager );
	
	VGEGL_API const bool onEvent( vgd::Shp<vgd::event::Event> event ); ///< Overrides
};


} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_DEFAULTEVENTPROCESSOR_HPP
