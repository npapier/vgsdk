// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_BOOL_H
#define _VGD_FIELD_BOOL_H

#include "vgd/vgd.hpp"

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of boolean type.
 */
//@{
typedef TSingleField< bool >					SFBool;

typedef TMultiField< bool  >					MFBool;

typedef TSingleAssociativeField< bool >	SAFBool;

// typedef TPairAssociativeField< bool >		PAFBool;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_BOOL_H
