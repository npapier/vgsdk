// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_PRIMITIVE_HPP
#define _VGD_FIELD_PRIMITIVE_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/Primitive.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::node::Primitive type.
 */
//@{
typedef TSingleField< vgd::node::Primitive >					SFPrimitive;

typedef TMultiField< vgd::node::Primitive  >					MFPrimitive;

typedef TSingleAssociativeField< vgd::node::Primitive >	SAFPrimitive;

// typedef TPairAssociativeField< vgd::node::Primitive >		PAFPrimitive;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_PRIMITIVE_HPP
