// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_INTEGER_H
#define _VGD_FIELD_INTEGER_H

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
 * @name Typedefs for fields containing elements of integer type.
 */
//@{
typedef TSingleField< int8  >			SFInt8;
typedef TSingleField< uint8 >			SFUInt8;
typedef TSingleField< int16 >			SFInt16;
typedef TSingleField< uint16>			SFUInt16;
typedef TSingleField< int32 >			SFInt32;
typedef TSingleField< uint32>			SFUInt32;

typedef TMultiField< int8  >			MFInt8;
typedef TMultiField< uint8 >			MFUInt8;
typedef TMultiField< int16 >			MFInt16;
typedef TMultiField< uint16>			MFUInt16;
typedef TMultiField< int32 >			MFInt32;
typedef TMultiField< uint32>			MFUInt32;

typedef TSingleAssociativeField< int8  >			SAFInt8;
typedef TSingleAssociativeField< uint8 >			SAFUInt8;
typedef TSingleAssociativeField< int16 >			SAFInt16;
typedef TSingleAssociativeField< uint16>			SAFUInt16;
typedef TSingleAssociativeField< int32 >			SAFInt32;
typedef TSingleAssociativeField< uint32>			SAFUInt32;

// typedef TPairAssociativeField< int8  >			PAFInt8;
// typedef TPairAssociativeField< uint8 >			PAFUInt8;
// typedef TPairAssociativeField< int16 >			PAFInt16;
// typedef TPairAssociativeField< uint16>			PAFUInt16;
// typedef TPairAssociativeField< int32 >			PAFInt32;
// typedef TPairAssociativeField< uint32>			PAFUInt32;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_INTEGER_H
