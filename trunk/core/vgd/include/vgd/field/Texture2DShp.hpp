// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TEXTURE2DSHP_HPP
#define _VGD_FIELD_TEXTURE2DSHP_HPP

#include "vgd/field/containers.hpp"
#include "vgd/Shp.hpp"

namespace vgd
{
namespace node 
{
struct Texture2D; 
typedef vgd::Shp< vgd::node::Texture2D > Texture2DShp; ///< type definition for shared pointer on a Texture2D
}
}



namespace vgd
{

namespace field
{

/**
 * @name Typedefs for fields containing elements of vgd::Shp< vgd::node::Texture2D > type.
 */
//@{

typedef TSingleField< vgd::Shp<vgd::node::Texture2D> >					SFTexture2DShp;
typedef TOptionalField< vgd::Shp<vgd::node::Texture2D> >				OFTexture2DShp;
typedef TMultiField< vgd::Shp<vgd::node::Texture2D>  >					MFTexture2DShp;
typedef TSingleAssociativeField< vgd::Shp<vgd::node::Texture2D> >		SAFTexture2DShp;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TEXTURE2DSHP_HPP
