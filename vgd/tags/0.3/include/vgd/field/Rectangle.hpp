// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_RECTANGLE_H
#define _VGD_FIELD_RECTANGLE_H

#include "vgd/vgd.hpp"

#include <vgm/Rectangle.hpp>

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgm::Rectangle type.
 */
//@{
typedef TSingleField< vgm::Rectangle2i >					SFRectangle2i;

typedef TMultiField< vgm::Rectangle2i  >					MFRectangle2i;

typedef TSingleAssociativeField< vgm::Rectangle2i >	SAFRectangle2i;

// typedef TPairAssociativeField< vgm::Rectangle2i >		PAFRectangle2i;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_RECTANGLE_H
