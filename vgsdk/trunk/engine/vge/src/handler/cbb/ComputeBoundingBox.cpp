// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/ComputeBoundingBox.hpp"

#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{
	
namespace cbb
{



const vge::service::List ComputeBoundingBox::getServices() const
{
	vge::service::List list;

	list.push_back( vge::service::ComputeBoundingBox::create() );

	return ( list );
}



} // namespace cbb

} // namespace handler

} // namespace vge
