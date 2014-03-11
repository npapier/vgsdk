// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_IIMAGESHP_HPP
#define _VGD_FIELD_IIMAGESHP_HPP

#include "vgd/basic/IImage.hpp"
#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{



/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::basic::IImage > type.
 */
//@{

typedef TSingleField< vgd::Shp< vgd::basic::IImage > >					SFIImageShp;
typedef TOptionalField< vgd::Shp< vgd::basic::IImage > >				OFIImageShp;
typedef TMultiField< vgd::Shp< vgd::basic::IImage > >					MFIImageShp;
typedef TSingleAssociativeField< vgd::Shp< vgd::basic::IImage > >		SAFIImageShp;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_IIMAGESHP_HPP
