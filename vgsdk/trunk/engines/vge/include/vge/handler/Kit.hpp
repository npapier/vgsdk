// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_KIT_H
#define _VGE_HANDLER_KIT_H

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct Kit;
	}
}

namespace vge
{
	namespace engine
	{
		struct Engine;
	}
}



namespace vge
{
	
namespace handler
{

/**
 * @brief Evaluate Kit node.
 */
struct VGE_API Kit
{
	void	apply				( vge::engine::Engine*, vgd::node::Kit* );
	void	unapply			( vge::engine::Engine*, vgd::node::Kit* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_KIT_H
