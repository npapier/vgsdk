// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXTURECUBEMAP_H
#define _VGEGL_HANDLER_PAINTER_TEXTURECUBEMAP_H

#include "vgeGL/vgeGL.hpp"

#include "vgeGL/handler/painter/Texture.hpp"

namespace vgd
{
	namespace node
	{
		struct TextureCubeMap;
	}
}

namespace vgeGL
{
	namespace rc
	{
		struct TextureCubeMap;
	}
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the TextureCubeMap node
 * 
 * @todo If there is modification in vgd::node::Texture, the entire texture resource is update (image, param, filter, 
 * env...). That must be optimized.
 */
struct VGEGL_API TextureCubeMap : public vgeGL::handler::painter::Texture
{
	META_HANDLER_HPP( TextureCubeMap );

	//const vge::service::List			getServices	() const;
	const TargetVector					getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	/**
	 * @brief Create the textureCubeMap and initialize it.
	 */
	void	create		( vgeGL::engine::Engine*, vgd::node::TextureCubeMap*, vgeGL::rc::TextureCubeMap* );
	
	void	create		( GLenum target, vgeGL::engine::Engine*, vgd::Shp< vgd::basic::IImage >, vgeGL::rc::TextureCubeMap* );	
	
	/**
	 * @brief Use a texture initialize by create().
	 */
	void	use			( vgeGL::engine::Engine*, vgd::node::TextureCubeMap*, vgeGL::rc::TextureCubeMap* );	



protected:

	static GLenum	m_cubeMapTarget[];
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXTURECUBEMAP_H
