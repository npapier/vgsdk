// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_TEXTUREMATRIXTRANSFORM_H
#define _VGE_HANDLER_TEXTUREMATRIXTRANSFORM_H

#include "vge/vge.hpp"

namespace vgd
{
	namespace node
	{
		struct TextureMatrixTransform;
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
 * @brief Evaluate TextureMatrixTransform node.
 */
struct VGE_API TextureMatrixTransform
{
	void	apply		( vge::engine::Engine*, vgd::node::TextureMatrixTransform* );
	void	unapply	( vge::engine::Engine*, vgd::node::TextureMatrixTransform* );
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_TEXTUREMATRIXTRANSFORM_H
