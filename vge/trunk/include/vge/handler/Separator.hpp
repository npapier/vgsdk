// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_SEPARATOR_H
#define _VGE_HANDLER_SEPARATOR_H

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct Separator;
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
 * @brief Evaluate Separator node.
 */
struct VGE_API Separator
{
	void	apply		( vge::engine::Engine*, vgd::node::Separator* );
	void	unapply	( vge::engine::Engine*, vgd::node::Separator* );	
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_SEPARATOR_H
