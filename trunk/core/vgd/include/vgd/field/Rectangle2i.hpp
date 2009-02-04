// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_RECTANGLE2I_HPP
#define _VGD_FIELD_RECTANGLE2I_HPP

#include <vgm/Rectangle.hpp>

#include "vgd/field/Enum.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Container definitions of rectangle type
 */
//@{

typedef TSingleField< vgm::Rectangle2i >					SFRectangle2i;

typedef TMultiField< vgm::Rectangle2i >						MFRectangle2i;

typedef TSingleAssociativeField< vgm::Rectangle2i >			SAFRectangle2i;

typedef TPairAssociativeField< Enum, vgm::Rectangle2i >		PAFRectangle2i;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_RECTANGLE2I_HPP
