// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_BOOL_HPP
#define _VGD_FIELD_BOOL_HPP

#include "vgd/field/Enum.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Container definitions of boolean type
 */
//@{
typedef TSingleField< bool >					SFBool;

typedef TMultiField< bool  >					MFBool;

typedef TSingleAssociativeField< bool >			SAFBool;

typedef TPairAssociativeField< EnumType, bool >	PAFBool;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_BOOL_HPP
