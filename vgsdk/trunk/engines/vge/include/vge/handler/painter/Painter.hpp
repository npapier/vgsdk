// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_PAINTER_PAINTER_H
#define _VGE_HANDLER_PAINTER_PAINTER_H

#include "vge/vge.hpp"
#include <vgDebug/Global.hpp>

#include "vge/handler/Handler.hpp"



namespace vge
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Abstract base class for painters.
 */
struct VGE_API Painter : public Handler
{
	const vge::service::List	getServices() const;
};



} // namespace painter

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_PAINTER_PAINTER_H
