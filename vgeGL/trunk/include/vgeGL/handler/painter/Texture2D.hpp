// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE2D_H
#define _VGEGL_HANDLER_PAINTER_TEXTURE2D_H

#include "vgeGL/vgeGL.hpp"

#include "vgeGL/handler/painter/Texture.hpp"

namespace vgd
{
	namespace node
	{
		struct Texture2D;
	}
}

namespace vgeGL
{
	namespace rc
	{
		struct Texture2D;
	}
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the Texture2D node
 * 
 * @todo If there is modification in vgd::node::Texture, the entire texture resource is update (image, param, filter, 
 * env...). That must be optimized.
 */
struct VGEGL_API Texture2D : public vgeGL::handler::painter::Texture
{
	META_HANDLER_HPP( Texture2D );

	const TargetVector	getTargets()	const;

	void						apply		( vge::engine::Engine*, vgd::node::Node* );
	void						unapply	( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	/**
	 * @brief Create the texture2D and initialize it.
	 */
	void	synchronize	( vgeGL::engine::Engine*, vgd::node::Texture2D*, vgeGL::rc::Texture2D* );
	
	/**
	 * @brief Use a texture initialize by create().
	 */
	void	bind			( vgeGL::engine::Engine*, vgd::node::Texture2D*, vgeGL::rc::Texture2D* );	
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE2D_H
