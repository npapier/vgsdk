// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_BOX_HPP
#define _VGD_FIELD_BOX_HPP

#include "vgd/vgd.hpp"

#include <vgm/Box.hpp>

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgm::*Box* types.
 */
//@{
typedef TSingleField< vgm::Box3f		>							SFBox3f;
typedef TSingleField< vgm::XfBox3f	>							SFXfBox3f;

typedef TMultiField< vgm::Box3f		>							MFBox3f;
typedef TMultiField< vgm::XfBox3f	>							MFXfBox3f;

typedef TSingleAssociativeField< vgm::Box3f		>			SAFBox3f;
typedef TSingleAssociativeField< vgm::XfBox3f	>			SAFXfBox3f;

// typedef TPairAssociativeField< vgm::Box3f		>				PAFBox3f;
// typedef TPairAssociativeField< vgm::XfBox3f	>				PAFXfBox3f;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_BOX_HPP
