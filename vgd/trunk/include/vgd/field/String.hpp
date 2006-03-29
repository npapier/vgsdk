// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_STRING_HPP
#define _VGD_FIELD_STRING_HPP

#include "vgd/vgd.hpp"

#include <string>

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of std::string type.
 */
//@{
typedef TSingleField< std::string >					SFString;

typedef TMultiField< std::string  >					MFString;

typedef TSingleAssociativeField< std::string >	SAFString;

// typedef TPairAssociativeField< std::string >		PAFString;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_STRING_HPP
