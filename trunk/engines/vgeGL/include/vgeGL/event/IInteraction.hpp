// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGEGL_EVENT_IINTERACTION_HPP
#define _VGEGL_EVENT_IINTERACTION_HPP

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
	 * Following methods do nothing, but sub-classes can override them at will to perform actions.
	 */
	//@{
	void apply( const vgd::event::AxisEvent				* /*pAxisEvent*/			) {}
	void apply( const vgd::event::HatEvent				* /*pHatEvent*/				) {}
	void apply( const vgd::event::JoystickButtonEvent	* /*pJoystickButtonEvent*/	) {}
	void apply( const vgd::event::KeyboardButtonEvent	* /*pKeyboardButtonEvent*/	) {}
	void apply( const vgd::event::Location2Event		* /*pLocation2Event*/ 		) {}
	void apply( const vgd::event::MouseButtonEvent		* /*pMouseButtonEvent*/		) {}
	void apply( const vgd::event::Motion3Event			* /*pMotion3Event*/			) {}
	void apply( const vgd::event::MouseWheelEvent		* /*pMouseWheelEvent*/		) {}
	void apply( const vgd::event::SizeEvent				* /*pSizeEvent*/			) {}
	void apply( const vgd::event::TimerEvent			* /*pTimerEvent*/			) {}
	//@}

private:	
	const bool onEvent( vgd::Shp<vgd::event::Event> event ); ///< Overrides (from IEventProcessor)
};



} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_IINTERACTION_HPP
