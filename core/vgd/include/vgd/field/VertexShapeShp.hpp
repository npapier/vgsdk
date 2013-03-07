// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_VERTEXSHAPESHP_HPP
#define _VGD_FIELD_VERTEXSHAPESHP_HPP

#include "vgd/field/containers.hpp"
#include "vgd/Shp.hpp"

namespace vgd
{
namespace node 
{
struct VertexShape; 
typedef vgd::Shp< vgd::node::VertexShape > VertexShapeShp; ///< type definition for shared pointer on a VertexShape
}
}



namespace vgd
{

namespace field
{

/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::VertexShape > type.
 */
//@{

typedef TSingleField< vgd::Shp<vgd::node::VertexShape> >					SFVertexShapeShp;
typedef TOptionalField< vgd::Shp<vgd::node::VertexShape> >					OFVertexShapeShp;
typedef TMultiField< vgd::Shp<vgd::node::VertexShape>  >					MFVertexShapeShp;
typedef TSingleAssociativeField< vgd::Shp<vgd::node::VertexShape> >			SAFVertexShapeShp;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_VERTEXSHAPESHP_HPP
