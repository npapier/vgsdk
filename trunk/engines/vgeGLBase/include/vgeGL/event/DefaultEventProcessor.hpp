//// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_EVENT_DEFAULTEVENTPROCESSOR_HPP
//#define _VGEGLBASE_EVENT_DEFAULTEVENTPROCESSOR_HPP
//
//#include "vgeGL/event/EventProcessor.hpp"
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
// * @brief Process an incoming event by using service ProcessEvent on the scene graph.
// * 
// * This is the default event processor in vgsdk used to process event for draggers classes.
// */
//struct DefaultEventProcessor : public EventProcessor
//{
//	/**
//	 * @brief Constructor
//	 * 
//	 * @param sceneManager	the linked scene manager.
//	 * 
//	 * @pre sceneManager != 0
//	 */
//	VGEGLBASE_API DefaultEventProcessor( ::vgeGL::engine::SceneManager *sceneManager );
//
//	/**
//	 * @brief Returns the name of the field in Engine containing a Hit computed by this event processor
//	 */
//	VGEGLBASE_API static const std::string getFHit() { return std::string("DefaultEventProcessor.hit"); }
//	typedef vgd::Shp< vgeGL::basic::Hit > HitValueType;
//	typedef vgd::field::TSingleField< HitValueType > FHitType;
//
//protected:
//	// Do a picking if the incoming event is a mouse [or keyboard ] button event. The result of picking is stored in an engine field, named getFHit().
//	// Picking is used by Dragger computation
//	VGEGLBASE_API const bool onEvent( vgd::Shp<vgd::event::Event> event ); ///< Overrides
//};
//
//
//} // namespace event
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_EVENT_DEFAULTEVENTPROCESSOR_HPP
//