// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_FLOAT_HPP
#define _VGD_FIELD_FLOAT_HPP

#include "vgd/field/containers.hpp"



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

typedef TOptionalField< float  >					OFFloat;
typedef TOptionalField< double >					OFDouble;

typedef TMultiField< float  >						MFFloat;
typedef TMultiField< double >						MFDouble;

typedef TSingleAssociativeField< float  >			SAFFloat;
typedef TSingleAssociativeField< double >			SAFDouble;

// typedef TPairAssociativeField< float  >			PAFFloat;
// typedef TPairAssociativeField< double >			PAFDouble;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_FLOAT_HPP
