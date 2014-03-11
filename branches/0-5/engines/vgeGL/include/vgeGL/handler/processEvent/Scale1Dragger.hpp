// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PROCESSEVENT_SCALE1DRAGGER_HPP
#define _VGEGL_HANDLER_PROCESSEVENT_SCALE1DRAGGER_HPP

#include "vgeGL/handler/processEvent/Dragger.hpp"
#include "vgeGL/handler/processEvent/ProcessEvent.hpp"



namespace vgeGL
{
	
namespace handler
{

namespace processEvent
{

/**
 * @brief Process event for a vgd::node::Scale1Dragger
 */
struct VGEGL_API Scale1Dragger :	public vgeGL::handler::processEvent::ProcessEvent,
									public vgeGL::handler::processEvent::Dragger
{
	META_HANDLER_HPP( Scale1Dragger );

	const TargetVector getTargets()	const;
	
	void	apply( vge::engine::Engine *, vgd::node::Node * );
	void	unapply( vge::engine::Engine *, vgd::node::Node * );

	void	setToDefaults();
	
	void	apply( vgd::event::Location2Event *  );
	void	apply( vgd::event::MouseWheelEvent * );
};



} // namespace processEvent

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PROCESSEVENT_SCALE1DRAGGER_HPP
