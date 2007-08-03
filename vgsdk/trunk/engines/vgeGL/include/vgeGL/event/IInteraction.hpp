// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_IINTERACTION_H
#define _VGEGL_EVENT_IINTERACTION_H

#include <vgd/event/EventVisitor.hpp>
#include "vgeGL/event/EventProcessor.hpp"
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace event
{


/**
 * @brief Base class for all interation event processor.
 */
struct VGEGL_API IInteraction : public EventProcessor, public vgd::event::EventVisitor
{
	/**
	 * @brief Default constructor
	 * 
	 * @param sceneManager	the linked scene manager.
	 * 
	 * @pre sceneManager != 0
	 */
	IInteraction( ::vgeGL::engine::SceneManager *sceneManager );

	/**
	 * @name Interface of EventVisitor
	 * 
	 * The five following methods done nothing, but must be overriden by class to perform action.
	 */
	//@{
	void apply( const vgd::event::KeyboardButtonEvent	* /*pKeyboardButtonEvent*/	) {}
	void apply( const vgd::event::Location2Event		* /*pLocation2Event*/ 		) {}
	void apply( const vgd::event::MouseButtonEvent		* /*pMouseButtonEvent*/		) {}
	void apply( const vgd::event::Motion3Event			* /*pMotion3Event*/			) {}
	void apply( const vgd::event::MouseWheelEvent		* /*pMouseWheelEvent*/		) {}
	//@}

private:	
	const bool onEvent( vgd::Shp<vgd::event::Event> event ); ///< Overrides (from IEventProcessor)
};



} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_IINTERACTION_H
