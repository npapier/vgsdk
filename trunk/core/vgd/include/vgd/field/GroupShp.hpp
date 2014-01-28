// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_GROUPSHP_HPP
#define _VGD_FIELD_GROUPSHP_HPP

#include "vgd/field/containers.hpp"
#include "vgd/node/Group.hpp"

namespace vgd
{

namespace node 
{

	typedef vgd::Shp< vgd::node::Group > GroupShp; ///< type definition for shared pointer on a Group
}

}

namespace vgd
{

namespace field
{


/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::Group > type.
 */
//@{

typedef TSingleField< vgd::node::GroupShp >				SFGroupShp;
typedef TOptionalField< vgd::node::GroupShp >			OFGroupShp;
typedef TMultiField< vgd::node::GroupShp  >				MFGroupShp;
typedef TSingleAssociativeField< vgd::node::GroupShp >	SAFGroupShp;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_GROUPSHP_HPP
