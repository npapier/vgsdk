// VGSDK - Copyright (C) 2007, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGD_BASIC_SLICETYPE_HPP
#define _VGD_BASIC_SLICETYPE_HPP


namespace vgd
{

namespace basic
{

/**
 * @brief Defines name of different slices in a 3D image.
 * 
 * @ingroup g_images
 */
typedef enum {
	AXIAL_SLICE = 0,
	FRONTAL_SLICE,
	SAGITTAL_SLICE
} SliceType;


} // namespace basic

} // namespace vgd



#endif //#ifndef _VGD_BASIC_SLICETYPE_HPP
