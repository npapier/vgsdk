// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_COMPUTEBOUNDINGBOX_HPP
#define _VGE_HANDLER_CBB_COMPUTEBOUNDINGBOX_HPP

#include "vge/vge.hpp"

#include "vge/handler/Handler.hpp"



namespace vge
{
	
namespace handler
{

namespace cbb
{



/**
 * @brief Abstract base class for compute bounding box handlers.
 */
struct VGE_API ComputeBoundingBox : public vge::handler::Handler
{
	const vge::service::List	getServices() const;
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_COMPUTEBOUNDINGBOX_HPP
