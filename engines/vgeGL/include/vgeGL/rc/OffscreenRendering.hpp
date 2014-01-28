// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_OFFSCREENRENDERING_HPP
#define _VGEGL_RC_OFFSCREENRENDERING_HPP

#include <glo/IResource.hpp>
#include <vector>
#include <vgd/Shp.hpp>
#include <vge/rc/IResource.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd { namespace node { struct FrameBuffer; struct Texture2D; } }



namespace vgeGL
{

namespace rc
{

struct FrameBufferObject;

/**
 * @brief OffscreenRendering rc
 */
struct VGEGL_API OffscreenRendering : public vge::rc::IResource, public glo::IResource
{
	typedef std::vector< vgd::Shp< vgd::node::Texture2D > > Texture2DVector;

	OffscreenRendering()
	:	textures( new Texture2DVector )
	{}

	vgd::Shp< vgd::node::FrameBuffer >			frameBuffer;
	vgd::Shp< vgeGL::rc::FrameBufferObject >	fbo;
	vgd::Shp< Texture2DVector >					textures;
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_OFFSCREENRENDERING_HPP
