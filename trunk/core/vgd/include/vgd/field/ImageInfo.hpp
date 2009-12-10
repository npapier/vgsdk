// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_IMAGEINFO_HPP
#define _VGD_FIELD_IMAGEINFO_HPP

#include "vgd/basic/Image.hpp"
#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::basic::Image type.
 */
//@{

typedef TSingleField< vgd::basic::Image >				SFImage;
typedef TOptionalField< vgd::basic::Image >				OFImage;
typedef TMultiField< vgd::basic::Image >				MFImage;
typedef TSingleAssociativeField< vgd::basic::Image >	SAFImage;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_IMAGEINFO_HPP
