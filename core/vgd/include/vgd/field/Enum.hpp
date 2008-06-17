// VGSDK - Copyright (C) 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ENUM_HPP
#define _VGD_FIELD_ENUM_HPP

#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{

/**
 * @brief Definition of enumeration type
 */
typedef int EnumType;

/**
 * @name Container definitions of enum type
 */
//@{

typedef TSingleField< EnumType >					SFEnum;

typedef TMultiField< EnumType >						MFEnum;

typedef TSingleAssociativeField< EnumType >			SAFEnum;

typedef TPairAssociativeField< EnumType, EnumType >	PAFEnum;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ENUM_HPP
