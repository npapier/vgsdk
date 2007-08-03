// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_TRANSFORM_H
#define _VGE_HANDLER_TRANSFORM_H

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct Transform;
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
 * @brief Evaluate Transform node.
 */
struct VGE_API Transform
{
	void	apply				( vge::engine::Engine*, vgd::node::Transform* );
	void	unapply			( vge::engine::Engine*, vgd::node::Transform* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_TRANSFORM_H
