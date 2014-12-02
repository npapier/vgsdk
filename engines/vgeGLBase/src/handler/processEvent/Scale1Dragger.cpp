//// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/processEvent/Scale1Dragger.hpp"
//
//#include <vgd/event/KeyboardButtonEvent.hpp>
//#include <vgd/event/Location2Event.hpp>
//#include <vgd/event/MouseButtonEvent.hpp>
//#include <vgd/event/MouseWheelEvent.hpp>
//#include <vgd/node/Scale1Dragger.hpp>
//#include <vge/rc/ButtonStateSet.hpp>
//#include <vgm/Utilities.hpp>
//
//#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/technique/ProcessEvent.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace handler
//{
//
//namespace processEvent
//{
//
//
//
//META_HANDLER_CPP( Scale1Dragger );
//
//
//
//const vge::handler::Handler::TargetVector Scale1Dragger::getTargets() const
//{
//	TargetVector targets;
//	
//	targets.push_back( vgd::node::Scale1Dragger::getClassIndexStatic() );
//	
//	return ( targets );
//}
//
//
//
//void Scale1Dragger::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
//{
//	using vgd::node::Scale1Dragger;
//		
//	assert( dynamic_cast< Scale1Dragger* >(pNode) != 0 );
//	Scale1Dragger *pDragger = static_cast< Scale1Dragger* >(pNode);
//	
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	//
//	Dragger::preApply( pGLEngine, pDragger );
//	Dragger::apply();
//	Dragger::postApply();
//}
//
//
//
//void Scale1Dragger::unapply( vge::engine::Engine *, vgd::node::Node * )
//{
//}
//
//
//
//void Scale1Dragger::setToDefaults()
//{
//}
//
//
//
//void Scale1Dragger::apply( vgd::event::Location2Event *pLocation2Event )
//{
//	using vgd::node::Scale1Dragger;
//		
//	assert( dynamic_cast< Scale1Dragger* >(m_pDragger) != 0 );
//	Scale1Dragger *pDragger = static_cast< Scale1Dragger* >(m_pDragger);
//		
//	if ( pDragger->getCurrentState() == Scale1Dragger::SCALE_X_ACTIVE )
//	{
//		// FIXME: Dragger ComputeScaleX();
//		vgd::event::Location2Event::LocationDelta	delta = pLocation2Event->getDelta();
//		vgd::event::Location2Event::Size				size	= pLocation2Event->getSize();				
//			
//		pDragger->setScale( pDragger->getScale() + (delta[0]/size[0]) );
//
//		// Schedules a refresh
//		pLocation2Event->scheduleRefreshForced();
//	}
//}
//
//
//
//void Scale1Dragger::apply( vgd::event::MouseWheelEvent *pMouseWheelEvent )
//{
//	using vgd::event::MouseWheelEvent;
//	using vgd::node::Scale1Dragger;
//		
//	assert( dynamic_cast< Scale1Dragger* >(m_pDragger) != 0 );
//	Scale1Dragger *pDragger = static_cast< Scale1Dragger* >(m_pDragger);
//	
//	//	
//	if ( pMouseWheelEvent->getAxis() == MouseWheelEvent::VERTICAL )
//	{
//		if ( pMouseWheelEvent->getDelta() != 0.f )
//		{
//			// WHEEL
//			// FIXME: Dragger ComputeScaleXWithWheel();
//			if ( pMouseWheelEvent->getDelta() > 0 )
//			{
//				pDragger->setScale( pDragger->getScale() + 0.5f );
//			}
//			else
//			{
//				pDragger->setScale( pDragger->getScale() - 0.5f );
//			}
//
//			// Schedules a refresh
//			pMouseWheelEvent->scheduleRefreshForced();
//		}
//	}
//}
//
//
//
//} // namespace processEvent
//	
//} // namespace handler
//
//} // namespace vge
//