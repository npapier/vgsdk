// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_NODESHP_HPP
#define _VGD_FIELD_NODESHP_HPP

#include "vgd/field/containers.hpp"
#include "vgd/node/Group.hpp"



namespace vgd
{
	
namespace field
{

/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::Node > type.
 */
//@{

typedef TSingleField< vgd::Shp<vgd::node::Node> >					SFNodeShp;
typedef TOptionalField< vgd::Shp<vgd::node::Node> >					OFNodeShp;
typedef TMultiField< vgd::Shp<vgd::node::Node>  >					MFNodeShp;
typedef TSingleAssociativeField< vgd::Shp<vgd::node::Node> >		SAFNodeShp;

//@}

/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::Group > type.
 */
//@{

typedef TSingleField< vgd::Shp<vgd::node::Group> >					SFGroupShp;
typedef TOptionalField< vgd::Shp<vgd::node::Group> >				OFGroupShp;
typedef TMultiField< vgd::Shp<vgd::node::Group>  >					MFGroupShp;
typedef TSingleAssociativeField< vgd::Shp<vgd::node::Group> >		SAFGroupShp;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_NODESHP_HPP
