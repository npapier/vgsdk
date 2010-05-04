// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/Basic.hpp"

#include "vge/service/Basic.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



const vge::service::List Basic::getServices() const
{
	vge::service::List list;

	list.push_back( vge::service::Basic::create() );

	return list;
}



} // namespace basic

} // namespace handler

} // namespace vge
