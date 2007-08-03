// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_SURROUNDSCALE_H
#define _VGE_HANDLER_SURROUNDSCALE_H

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct SurroundScale;
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
 * @brief Evaluate SurroundScale node.
 */
struct VGE_API SurroundScale
{
	void	apply				( vge::engine::Engine*, vgd::node::SurroundScale* );
	void	unapply			( vge::engine::Engine*, vgd::node::SurroundScale* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_SURROUNDSCALE_H
