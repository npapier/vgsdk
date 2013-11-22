// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_UINT_HPP
#define _VGD_FIELD_UINT_HPP

#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Typedefs for fields containing elements of integer type.
 */
//@{
typedef TSingleField< uint  >						SFUInt;

typedef TOptionalField< uint  >						OFUInt;

typedef TMultiField< uint  >						MFUInt;

typedef TSingleAssociativeField< uint  >			SAFUInt;

// typedef TPairAssociativeField< int  >		PAFInt;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_UINT_HPP
