// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_DISPLAYLIST_H
#define _VGEGL_RC_DISPLAYLIST_H

#include <glo/DisplayList.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Encapsulation of one or more OpenGL display list.
 * 
 */
struct VGEGL_API DisplayList : public vge::rc::IResource, public glo::DisplayList
{
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_DISPLAYLIST_H
