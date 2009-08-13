// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CAMERA_HPP
#define _VGE_HANDLER_CAMERA_HPP

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct Camera;
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
 * @brief Evaluate Camera node.
 */
struct VGE_API Camera
{
	void apply( vge::engine::Engine*, vgd::node::Camera* );
	void unapply( vge::engine::Engine*, vgd::node::Camera* );

	//
	void applyMatrix( vge::engine::Engine*, vgd::node::Camera* );
	void applyLookAt( vge::engine::Engine*, vgd::node::Camera* );

	//void unapplyMatrix( vge::engine::Engine*, vgd::node::Camera* );
	//void unapplyLookAt( vge::engine::Engine*, vgd::node::Camera* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CAMERA_HPP
