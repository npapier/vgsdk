// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_FLOAT_H
#define _VGD_FIELD_FLOAT_H

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
 * @name Typedefs for fields containing elements of floating type.
 */
//@{
typedef TSingleField< float  >						SFFloat;
typedef TSingleField< double >						SFDouble;

typedef TMultiField< float  >							MFFloat;
typedef TMultiField< double >							MFDouble;

typedef TSingleAssociativeField< float  >			SAFFloat;
typedef TSingleAssociativeField< double >			SAFDouble;

// typedef TPairAssociativeField< float  >			PAFFloat;
// typedef TPairAssociativeField< double >			PAFDouble;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_FLOAT_H
