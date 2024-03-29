// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_PAINTER_GROUP_HPP
#define _VGE_HANDLER_PAINTER_GROUP_HPP

#include "vge/handler/painter/Painter.hpp"



namespace vge
{

namespace handler
{

namespace painter
{



/**
 * @brief Base class for handlers painting group.
 */
struct VGE_API Group : public Painter
{
	void apply( vge::engine::Engine*, vgd::node::Node* );
};



} // namespace painter

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_PAINTER_GROUP_HPP
