// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IMAGEUTILITIES_H
#define _VGD_BASIC_IMAGEUTILITIES_H

#include "vgd/vgd.hpp"
#include "vgd/Shp.hpp"
#include "vgd/basic/Image.hpp"



namespace vgd
{
	
namespace basic
{

/**
 * @brief Defines name of different plans in a 3D image.
 */
typedef enum {
	AXIAL_PLAN = 0,
	FRONTAL_PLAN,
	SAGITTAL_PLAN
} PlanNameType;


/**
 * @brief Collection of methods to apply on images.
 */
struct VGD_API ImageUtilities
{
	/**
	 * @brief Extract a plan (2d image) from a 3d image.
	 * 
	 * @pre pImage->type() == IImage::UINT8
	 * 
	 * @pre pImage->width() > 0
	 * @pre pImage->height() > 0
	 * @pre pImage->depth() > 0
	 * @pre if plan == AXIAL_PLAN then 0 <= position < pImage->depth()
	 * @pre if plan == FRONTAL_PLAN then 0 <= position < pImage->height()
	 * @pre if plan == SAGITTAL_PLAN then 0 <= position < pImage->width()
	 *
	 * @param pImage		3d image where plan is extract
	 * @param plan			name of plan to must be extract
	 * @param position	position of the plan
	 * @return	a reference on the desired extracted image or a reference on an empty image if extraction is not possible
	 * 
	 * @todo Remove precondition on pImage->type()
	 */
	static vgd::Shp< Image > extractImage2D(	vgd::Shp< IImage > pImage, 
															const PlanNameType plan,
															const uint32 position );

	/**
	 * @name Useful scanning image methods.
	 */
	//@{
	
	/**
	 * @brief Scan the whole image and set alpha value of each pixel to \c alpha.
	 * 
	 * @pre pImage->format() == RGBA or pImage->format() == BGRA or pImage->format() == LUMINANCE_ALPHA
	 * @pre pImage->type() == UINT8
	 * @pre 0 <= alpha <= 1
	 * 
	 * @param pImage		image to scan.
	 * @param alpha		alpha value to assign.
	 */
	static void	setAlpha( vgd::Shp< IImage > pImage, const float alpha = 1.f );

	/**
	 * @brief Scan the whole image and modify alpha value of each pixel.
	 * 
	 * Sets alpha value of each pixel to \c alpha only if pixel color is != (0,0,0), otherwise sets alpha value to zero.
	 * 
	 * @pre pImage->format() == RGBA or pImage->format() == BGRA or pImage->format() == LUMINANCE_ALPHA
	 * @pre pImage->type() == UINT8
	 * @pre 0 <= alpha <= 1
	 * 
	 * @param pImage		image to scan.
	 * @param alpha		alpha value to assign.
	 */
	static void	setAlphaIfNotBlack( vgd::Shp< IImage > pImage, const float alpha = 1.f );
	//@}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_IMAGEUTILITIES_H
