// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_IMAGE_H
#define _VGD_FIELD_IMAGE_H

#include "vgd/vgd.hpp"

#include "vgd/Shp.hpp"
#include "vgd/basic/IImage.hpp"
#include "vgd/basic/Image.hpp"
#include "vgd/basic/ImageInfo.hpp"

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::basic::*Image* type.
 */
//@{
typedef TSingleField< vgd::Shp< vgd::basic::IImage > >				SFIImage;

typedef TMultiField< vgd::Shp< vgd::basic::IImage > >					MFIImage;

typedef TSingleAssociativeField< vgd::Shp< vgd::basic::IImage > >	SAFIImage;



typedef TSingleField< vgd::basic::ImageInfo >				SFImageInfo;

typedef TMultiField< vgd::basic::ImageInfo >					MFImageInfo;

typedef TSingleAssociativeField< vgd::basic::ImageInfo >	SAFImageInfo;



typedef TSingleField< vgd::basic::Image >					SFImage;

typedef TMultiField< vgd::basic::Image >					MFImage;

typedef TSingleAssociativeField< vgd::basic::Image >	SAFImage;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_IMAGE_H
