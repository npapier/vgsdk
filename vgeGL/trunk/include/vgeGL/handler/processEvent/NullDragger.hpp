// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PROCESSEVENT_NULLDRAGGER_H
#define _VGEGL_HANDLER_PROCESSEVENT_NULLDRAGGER_H

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
 * @brief Process event for a vgd::node::NullDragger.
 */
struct VGEGL_API NullDragger :	public vgeGL::handler::processEvent::ProcessEvent,
											public vgeGL::handler::processEvent::Dragger
{
	META_HANDLER_HPP( NullDragger );

	const TargetVector getTargets()	const;
	
	void	apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode );
	void	unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode );

	void	setToDefaults();
};



} // namespace processEvent

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PROCESSEVENT_NULLDRAGGER_H
