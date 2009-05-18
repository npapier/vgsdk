// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PROCESSEVENT_TRANSFORMDRAGGER_HPP
#define _VGEGL_HANDLER_PROCESSEVENT_TRANSFORMDRAGGER_HPP

#include "vgeGL/handler/processEvent/Dragger.hpp"
#include "vgeGL/handler/processEvent/ProcessEvent.hpp"
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace handler
{

namespace processEvent
{

/**
 * @brief Process event for a vgd::node::TransformDragger.
 */
struct VGEGL_API TransformDragger :	public vgeGL::handler::processEvent::ProcessEvent,
												public vgeGL::handler::processEvent::Dragger
{
	META_HANDLER_HPP( TransformDragger );

	const TargetVector				getTargets()	const;
	
	void	apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode );
	void	unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode );

	void	setToDefaults();
	
	void	apply( const vgd::event::Location2Event *pLocation2Event );
	void	apply( const vgd::event::MouseWheelEvent *pMouseWheelEvent );
};



} // namespace processEvent

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PROCESSEVENT_TRANSFORMDRAGGER_HPP
