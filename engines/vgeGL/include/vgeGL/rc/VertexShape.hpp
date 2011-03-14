// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_VERTEXSHAPE_HPP
#define _VGEGL_RC_VERTEXSHAPE_HPP

#include <glo/ArrayBuffer.hpp>
#include <glo/ElementArrayBuffer.hpp>
#include <vector>

#include "vge/rc/IResource.hpp"
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace rc
{



/**
 * @brief OpenGL objects associated to VertexShape submitting
 */
struct VGEGL_API VertexShape : public vge::rc::IResource, public glo::IResource
{
	glo::ArrayBuffer					vertex;
	glo::ArrayBuffer					normal;
	std::vector< glo::ArrayBuffer >		texCoord;
	glo::ElementArrayBuffer				vertexIndex;
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_VERTEXSHAPE_HPP
