// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TEXTURECUBEMAP_HPP
#define _VGEGL_RC_TEXTURECUBEMAP_HPP

#include <glo/TextureCubeMap.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{



/**
 * @brief Encapsulation of a cube map texture object.
 */
struct VGEGL_API TextureCubeMap : public vge::rc::IResource, public glo::TextureCubeMap
{
};


	
} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_TEXTURECUBEMAP_HPP
