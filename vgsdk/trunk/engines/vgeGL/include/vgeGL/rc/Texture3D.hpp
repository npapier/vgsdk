// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TEXTURE3D_H
#define _VGEGL_RC_TEXTURE3D_H

#include <glo/Texture3D.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Encapsulation of a texture 3D object.
 */
struct VGEGL_API Texture3D : public vge::rc::IResource, public glo::Texture3D
{
};


	
} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_TEXTURE3D_H
