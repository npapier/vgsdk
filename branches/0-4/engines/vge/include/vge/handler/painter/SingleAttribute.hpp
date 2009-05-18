// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_PAINTER_SINGLEATTRIBUTE_HPP
#define _VGE_HANDLER_PAINTER_SINGLEATTRIBUTE_HPP

#include "vge/vge.hpp"

#include "vge/handler/painter/Attribute.hpp"



namespace vge
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Abstract base class for handlers painting single attribute.
 */
struct VGE_API SingleAttribute : public Attribute
{
};



} // namespace painter

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_PAINTER_SINGLEATTRIBUTE_HPP
