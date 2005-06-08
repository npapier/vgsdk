// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_NODE_H
#define _VGD_FIELD_NODE_H

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/Group.hpp"
//#include "vgd/node/Node.hpp"
#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace field
{

/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::Node > type.
 */
//@{
typedef TSingleField< vgd::Shp<vgd::node::Node> >						SFNode;

typedef TMultiField< vgd::Shp<vgd::node::Node>  >						MFNode;

typedef TSingleAssociativeField< vgd::Shp<vgd::node::Node> >		SAFNode;

// typedef TPairAssociativeField< vgd::Shp<vgd::node::Node> >		PAFNode;
//@}

/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::Group > type.
 */
//@{
typedef TSingleField< vgd::Shp<vgd::node::Group> >						SFGroup;

typedef TMultiField< vgd::Shp<vgd::node::Group>  >						MFGroup;

typedef TSingleAssociativeField< vgd::Shp<vgd::node::Group> >		SAFGroup;

// typedef TPairAssociativeField< vgd::Shp<vgd::node::Group> >		PAFGroup;
//@}

} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_NODE_H
