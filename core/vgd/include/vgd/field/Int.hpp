// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_INT_HPP
#define _VGD_FIELD_INT_HPP

#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Typedefs for fields containing elements of integer type.
 */
//@{
typedef TSingleField< int  >					SFInt;

typedef TOptionalField< int  >					OFInt;

typedef TMultiField< int  >						MFInt;

typedef TSingleAssociativeField< int  >			SAFInt;

// typedef TPairAssociativeField< int  >		PAFInt;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_INT_HPP
