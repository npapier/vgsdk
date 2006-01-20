// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ROTATION_H
#define _VGD_FIELD_ROTATION_H

#include "vgd/vgd.hpp"

#include <vgm/Rotation.hpp>

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgm::Rotation type.
 */
//@{
typedef TSingleField< vgm::Rotation >					SFRotation;

typedef TMultiField< vgm::Rotation  >					MFRotation;

typedef TSingleAssociativeField< vgm::Rotation >	SAFRotation;

// typedef TPairAssociativeField< vgm::Rotation >		PAFRotation;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ROTATION_H
