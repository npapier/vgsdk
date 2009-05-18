// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_PLANE_HPP
#define _VGD_FIELD_PLANE_HPP

#include <vgm/Plane.hpp>
#include "vgd/field/Enum.hpp"



namespace vgd
{

namespace field
{

/**
 * @name Container definitions of plane type
 */
//@{

typedef TSingleField< vgm::Plane >						SFPlane;

typedef TMultiField< vgm::Plane >						MFPlane;

typedef TSingleAssociativeField< vgm::Plane >			SAFPlane;

typedef TPairAssociativeField< Enum, vgm::Plane >		PAFPlane;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_PLANE_HPP
