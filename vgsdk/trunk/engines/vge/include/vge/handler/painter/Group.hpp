// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_PAINTER_GROUP_H
#define _VGE_HANDLER_PAINTER_GROUP_H

#include "vge/vge.hpp"

#include "vge/handler/painter/Painter.hpp"



namespace vge
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Abstract base class for handlers painting group.
 */
struct VGE_API Group : public Painter
{
};



} // namespace painter

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_PAINTER_GROUP_H
