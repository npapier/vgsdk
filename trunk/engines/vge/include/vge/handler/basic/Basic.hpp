// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_BASIC_HPP
#define _VGE_HANDLER_BASIC_BASIC_HPP

#include "vge/vge.hpp"

#include "vge/handler/Handler.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



/**
 * @brief Abstract base class for basics handlers.
 */
struct VGE_API Basic : public vge::handler::Handler
{
	const vge::service::List	getServices() const;
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_BASIC_HPP
