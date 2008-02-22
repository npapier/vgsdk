// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_TRANSFORMSEPARATOR_HPP
#define _VGE_HANDLER_TRANSFORMSEPARATOR_HPP

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct TransformSeparator;
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
 * @brief Evaluate TransformSeparator node.
 */
struct VGE_API TransformSeparator
{
	void	apply		( vge::engine::Engine*, vgd::node::TransformSeparator* );
	void	unapply	( vge::engine::Engine*, vgd::node::TransformSeparator* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_TRANSFORMSEPARATOR_HPP
