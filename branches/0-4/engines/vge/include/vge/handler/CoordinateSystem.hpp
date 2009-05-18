// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_COORDINATESYSTEM_HPP
#define _VGE_HANDLER_COORDINATESYSTEM_HPP

#include "vge/vge.hpp"

namespace vgd { namespace node { struct CoordinateSystem; } }

namespace vge {	namespace engine { struct Engine; } }



namespace vge
{
	
namespace handler
{



/**
 * @brief Evaluates CoordinateSystem node.
 */
struct VGE_API CoordinateSystem
{
	void	apply	( vge::engine::Engine*, vgd::node::CoordinateSystem* );
	void	unapply	( vge::engine::Engine*, vgd::node::CoordinateSystem* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_COORDINATESYSTEM_HPP
