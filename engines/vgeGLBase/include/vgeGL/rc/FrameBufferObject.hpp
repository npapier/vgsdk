// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_FRAMEBUFFEROBJECT_HPP
#define _VGEGL_RC_FRAMEBUFFEROBJECT_HPP

#include <glo/FrameBufferObject.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Encapsulation of a frame buffer object
 */
struct VGEGL_API FrameBufferObject : public vge::rc::IResource, public glo::FrameBufferObject
{
};


	
} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_FRAMEBUFFEROBJECT_HPP
