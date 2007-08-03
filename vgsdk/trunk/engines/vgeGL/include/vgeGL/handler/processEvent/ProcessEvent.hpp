// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PROCESSEVENT_PROCESSEVENT_H
#define _VGEGL_HANDLER_PROCESSEVENT_PROCESSEVENT_H

#include <vge/handler/Handler.hpp>
#include <vgDebug/Global.hpp>

#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace handler
{

namespace processEvent
{



/**
 * @brief Abstract base class for process event handlers.
 */
struct VGEGL_API ProcessEvent : public vge::handler::Handler
{
	const vge::service::List	getServices() const;
};



} // namespace processEvent

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PROCESSEVENT_PROCESSEVENT_H
