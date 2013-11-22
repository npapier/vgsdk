// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_VERTEXSHAPEPTR_HPP
#define _VGD_FIELD_VERTEXSHAPEPTR_HPP

#include "vgd/field/containers.hpp"

namespace vgd
{
namespace node 
{
struct VertexShape; 
typedef vgd::node::VertexShape *VertexShapePtr; ///< type definition for pointer on a VertexShape
}
}



namespace vgd
{

namespace field
{

/**
 * @name Typedefs for fields containing elements of vgd::node::VertexShapePtr type.
 */
//@{

typedef TSingleField< vgd::node::VertexShape * >					SFVertexShapePtr;
typedef TOptionalField< vgd::node::VertexShape * >					OFVertexShapePtr;
typedef TMultiField< vgd::node::VertexShape *  >					MFVertexShapePtr;
typedef TSingleAssociativeField< vgd::node::VertexShape * >			SAFVertexShapePtr;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_VERTEXSHAPEPTR_HPP
