// VGSDK - Copyright (C) 2004, 2006, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_GLSLPROGRAM_HPP
#define _VGEGL_RC_GLSLPROGRAM_HPP

#include <glo/GLSLProgram.hpp>
#include <vge/rc/IResource.hpp>

#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace rc
{

/**
 * @brief Encapsulation of OpenGL Shading Language shaders
 */
struct VGEGL_API GLSLProgram : public vge::rc::IResource, public glo::GLSLProgram
{
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_GLSLPROGRAM_HPP
