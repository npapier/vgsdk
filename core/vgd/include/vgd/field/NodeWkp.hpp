// VGSDK - Copyright (C) 2004, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_NODEWKP_HPP
#define _VGD_FIELD_NODEWKP_HPP

#include "vgd/field/containers.hpp"
#include "vgd/node/Node.hpp"
#include "vgd/Wkp.hpp"



namespace vgd
{

namespace field
{

/**
 * @name Typedefs for fields containing elements of vgd::Wkp< vgd::node::Node > type.
 */
//@{

typedef TSingleField< vgd::Wkp<vgd::node::Node> >					SFNodeWkp;
typedef TOptionalField< vgd::Wkp<vgd::node::Node> >					OFNodeWkp;
typedef TMultiField< vgd::Wkp<vgd::node::Node>  >					MFNodeWkp;
typedef TSingleAssociativeField< vgd::Wkp<vgd::node::Node> >		SAFNodeWkp;

//@}

/**
 * @name Typedefs for fields containing elements of vgd::Wkp< vgd::node::Group > type.
 */
//@{

typedef TSingleField< vgd::Wkp<vgd::node::Group> >					SFGroupWkp;
typedef TOptionalField< vgd::Wkp<vgd::node::Group> >				OFGroupWkp;
typedef TMultiField< vgd::Wkp<vgd::node::Group>  >					MFGroupWkp;
typedef TSingleAssociativeField< vgd::Wkp<vgd::node::Group> >		SAFGroupWkp;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_NODEWKP_HPP
