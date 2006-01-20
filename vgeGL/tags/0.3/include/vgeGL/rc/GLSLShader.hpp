// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_GLSLSHADER_H
#define _VGEGL_RC_GLSLSHADER_H

#include <glo/GLSLShader.hpp>
#include <vge/rc/IResource.hpp>

#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace rc
{

/**
 * @brief Encapsulation of OpenGL Shading Language shaders
 */
struct VGEGL_API GLSLShader : public vge::rc::IResource, public glo::GLSLShader
{
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_GLSLSHADER_H
