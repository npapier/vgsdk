// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TEXTURE1D_HPP
#define _VGEGL_RC_TEXTURE1D_HPP

#include <glo/Texture1D.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Encapsulation of a texture 1D object.
 */
struct VGEGL_API Texture1D : public vge::rc::IResource, public glo::Texture1D
{
};


	
} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_TEXTURE1D_HPP
