//// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//// Author Guillaume Brocker
//
//#ifndef _VGEGLBASE_EVENT_IINTERACTION_HPP
//#define _VGEGLBASE_EVENT_IINTERACTION_HPP
//
//#include <vgd/event/EventVisitor.hpp>
//#include "vgeGLBase/event/EventProcessor.hpp"
//#include "vgeGLBase/vgeGLBase.hpp"
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
// * @brief Base class for all interation event processor.
// */
//struct VGEGLBASE_API IInteraction : public EventProcessor, public vgd::event::EventVisitor
//{
//	/**
//	 * @brief Default constructor
//	 * 
//	 * @param sceneManager	the linked scene manager.
//	 * 
//	 * @pre sceneManager != 0
//	 */
//	IInteraction( ::vgeGLBase::engine::SceneManager *sceneManager );
//
//	/**
//	 * @name Interface of EventVisitor
//	 * 
//	 * Following methods do nothing, but sub-classes can override them at will to perform actions.
//	 */
//	//@{
//	void apply( vgd::event::AxisEvent				* /*pAxisEvent*/			) {}
//	void apply( vgd::event::HatEvent				* /*pHatEvent*/				) {}
//	void apply( vgd::event::JoystickButtonEvent		* /*pJoystickButtonEvent*/	) {}
//	void apply( vgd::event::KeyboardButtonEvent		* /*pKeyboardButtonEvent*/	) {}
//	void apply( vgd::event::Location2Event			* /*pLocation2Event*/ 		) {}
//	void apply( vgd::event::MouseButtonEvent		* /*pMouseButtonEvent*/		) {}
//	void apply( vgd::event::Motion3Event			* /*pMotion3Event*/			) {}
//	void apply( vgd::event::MouseWheelEvent			* /*pMouseWheelEvent*/		) {}
//	void apply( vgd::event::SizeEvent				* /*pSizeEvent*/			) {}
//	void apply( vgd::event::TimerEvent				* /*pTimerEvent*/			) {}
//	//@}
//
//private:	
//	const bool onEvent( vgd::Shp<vgd::event::Event> event ); ///< Overrides (from IEventProcessor)
//};
//
//
//
//} // namespace event
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_EVENT_IINTERACTION_HPP
//