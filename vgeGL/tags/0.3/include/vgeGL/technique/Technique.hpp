// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_TECHNIQUE_H
#define _VGEGL_TECHNIQUE_TECHNIQUE_H

#include <vge/technique/Technique.hpp>

#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace technique
{



/**
 * @brief Base class for all technique using OpenGL.
 */
struct VGEGL_API Technique : public vge::technique::Technique
{
	//virtual void beginPass();
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_TECHNIQUE_H
