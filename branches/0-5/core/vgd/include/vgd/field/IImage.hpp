// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_IIMAGE_HPP
#define _VGD_FIELD_IIMAGE_HPP

#include "vgd/basic/IImage.hpp"
#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::basic::IImage type.
 */
//@{
typedef TSingleField< vgd::basic::IImage >					SFIImage;
typedef TOptionalField< vgd::basic::IImage >				OFIImage;
typedef TMultiField< vgd::basic::IImage >					MFIImage;
typedef TSingleAssociativeField< vgd::basic::IImage >		SAFIImage;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_IIMAGE_HPP
