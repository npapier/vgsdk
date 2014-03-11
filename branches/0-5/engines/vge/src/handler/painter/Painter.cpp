// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/painter/Painter.hpp"

#include "vge/service/Painter.hpp"



namespace vge
{

namespace handler
{

namespace painter
{



const vge::service::List Painter::getServices() const
{
	vge::service::List list;
	list.push_back( vge::service::Painter::create() );

	return ( list );
}



} // namespace painter

} // namespace handler

} // namespace vge
