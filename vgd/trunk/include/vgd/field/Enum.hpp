// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ENUM_HPP
#define _VGD_FIELD_ENUM_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
//#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{

/**
 * @brief Typedef on enumeration type.
 */
typedef int32 EnumType;

/**
 * @name Typedefs for fields containing elements of enumeration type.
 */
//@{


typedef TSingleField< EnumType >				SFEnum;

typedef TMultiField< EnumType >					MFEnum;

typedef TSingleAssociativeField< EnumType >		SAFEnum;

// typedef TPairAssociativeField< int32 >		PAFEnum;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ENUM_HPP
