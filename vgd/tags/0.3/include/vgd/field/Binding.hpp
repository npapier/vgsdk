// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_BINDING_H
#define _VGD_FIELD_BINDING_H

#include "vgd/vgd.hpp"

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/Binding.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::node::Binding type.
 */
//@{
typedef TSingleField< vgd::node::Binding >					SFBinding;

typedef TMultiField< vgd::node::Binding >						MFBinding;

typedef TSingleAssociativeField< vgd::node::Binding >		SAFBinding;

// typedef TPairAssociativeField< vgd::node::Binding >		PAFBinding;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_BINDING_H
