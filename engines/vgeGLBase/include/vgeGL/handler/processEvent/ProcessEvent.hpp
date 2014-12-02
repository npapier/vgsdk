// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGLBASE_HANDLER_PROCESSEVENT_PROCESSEVENT_HPP
#define _VGEGLBASE_HANDLER_PROCESSEVENT_PROCESSEVENT_HPP

#include <vge/handler/Handler.hpp>


#include "vgeGLBase/vgeGLBase.hpp"



namespace vgeGLBase
{
	
namespace handler
{

namespace processEvent
{



/**
* @brief Abstract base class for process event handlers.
*/
struct VGEGLBASE_API ProcessEvent : public vge::handler::Handler
{
	const vge::service::List	getServices() const;
};



} // namespace processEvent

} // namespace handler

} // namespace vgeGLBase

#endif //#ifndef _VGEGLBASE_HANDLER_PROCESSEVENT_PROCESSEVENT_HPP
