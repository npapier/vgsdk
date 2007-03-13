// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TEXTURE2D_H
#define _VGEGL_RC_TEXTURE2D_H

#include <glo/Texture2D.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Encapsulation of a texture 2D object.
 */
struct VGEGL_API Texture2D : public vge::rc::IResource, public glo::Texture2D
{
};


	
} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_TEXTURE2D_H
