//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PROCESSEVENT_NULLDRAGGER_HPP
//#define _VGEGLBASE_HANDLER_PROCESSEVENT_NULLDRAGGER_HPP
//
//#include "vgeGLBase/handler/processEvent/Dragger.hpp"
//#include "vgeGLBase/handler/processEvent/ProcessEvent.hpp"
//
//
//
//namespace vgeGLBase
//{
//	
//namespace handler
//{
//
//namespace processEvent
//{
//
///**
// * @brief Process event for a vgd::node::NullDragger
// */
//struct VGEGLBASE_API NullDragger :	public vgeGLBase::handler::processEvent::ProcessEvent,
//								public vgeGLBase::handler::processEvent::Dragger
//{
//	META_HANDLER_HPP( NullDragger );
//
//	const TargetVector getTargets()	const;
//	
//	void	apply( vge::engine::Engine *, vgd::node::Node * );
//	void	unapply( vge::engine::Engine *, vgd::node::Node * );
//
//	void	setToDefaults();
//};
//
//
//
//} // namespace processEvent
//
//} // namespace handler
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PROCESSEVENT_NULLDRAGGER_HPP
//