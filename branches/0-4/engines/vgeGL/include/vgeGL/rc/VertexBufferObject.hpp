// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_VERTEXBUFFEROBJECT_HPP
#define _VGEGL_RC_VERTEXBUFFEROBJECT_HPP

#include <glo/VertexBufferObject.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Encapsulation of OpenGL Vertex Buffer Object (extension GL_ARB_vertex_buffer_object).
 */
struct VGEGL_API VertexBufferObject : public vge::rc::IResource, public glo::VertexBufferObject
{
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_VERTEXBUFFEROBJECT_HPP
