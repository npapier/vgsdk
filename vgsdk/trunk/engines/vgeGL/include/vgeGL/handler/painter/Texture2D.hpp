// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE2D_HPP
#define _VGEGL_HANDLER_PAINTER_TEXTURE2D_HPP

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
 */
struct VGEGL_API Texture2D : public vgeGL::handler::painter::Texture
{
	META_HANDLER_HPP( Texture2D );

	const TargetVector	getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();

	/**
	 * @brief Creates/updates the texture2D and updates parameters.
	 */
	void	synchronize	( vgeGL::engine::Engine*, vgd::node::Texture2D*, vgeGL::rc::Texture2D* );


private:
	/**
	 * @todo Must be generalized for n-dimensional texture ?
	 * @todo ARB NPOT extension
	 */
	void texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture2D *pNode,
						vgeGL::rc::Texture2D *pResource );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE2D_HPP
