// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE1D_H
#define _VGEGL_HANDLER_PAINTER_TEXTURE1D_H

#include "vgeGL/vgeGL.hpp"

#include "vgeGL/handler/painter/Texture.hpp"

namespace vgd
{
	namespace node
	{
		struct Texture1D;
	}
}

namespace vgeGL
{
	namespace rc
	{
		struct Texture1D;
	}
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the Texture1D node
 */
struct VGEGL_API Texture1D : public vgeGL::handler::painter::Texture
{
	META_HANDLER_HPP( Texture1D );

	const TargetVector	getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults();

	void	synchronize	( vgeGL::engine::Engine*, vgd::node::Texture1D*, vgeGL::rc::Texture1D* );

private:	
	/**
	 * @todo Must be generalized for n-dimensional texture ?
	 * @todo ARB NPOT extension
	 */
	void texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
						vgeGL::rc::Texture1D *pResource );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE1D_H
