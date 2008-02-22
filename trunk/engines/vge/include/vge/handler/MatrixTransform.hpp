// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_MATRIXTRANSFORM_HPP
#define _VGE_HANDLER_MATRIXTRANSFORM_HPP

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct MatrixTransform;
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
 * @brief Evaluate MatrixTransform node.
 */
struct VGE_API MatrixTransform
{
	void	apply				( vge::engine::Engine*, vgd::node::MatrixTransform* );
	void	unapply			( vge::engine::Engine*, vgd::node::MatrixTransform* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_MATRIXTRANSFORM_HPP
