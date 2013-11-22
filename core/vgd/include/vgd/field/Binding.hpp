// VGSDK - Copyright (C) 2004, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_BINDING_HPP
#define _VGD_FIELD_BINDING_HPP

#include "vgd/field/containers.hpp"
#include "vgd/node/Enum.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::node::Binding type
 */
//@{
typedef TSingleField< vgd::node::Binding >					SFBinding;
typedef TOptionalField< vgd::node::Binding >				OFBinding;
typedef TMultiField< vgd::node::Binding >					MFBinding;
typedef TSingleAssociativeField< vgd::node::Binding >		SAFBinding;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_BINDING_HPP