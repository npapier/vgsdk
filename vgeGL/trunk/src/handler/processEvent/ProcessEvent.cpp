// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/processEvent/ProcessEvent.hpp"

#include <vge/service/ProcessEvent.hpp>



namespace vgeGL
{

namespace handler
{

namespace processEvent
{



const vge::service::List ProcessEvent::getServices() const
{
	vge::service::List list;
	list.push_back( vge::service::ProcessEvent::create() );

	return ( list );
}



} // namespace processEvent

} // namespace handler

} // namespace vgeGL
