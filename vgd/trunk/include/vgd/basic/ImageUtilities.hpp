// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IMAGEUTILITIES_H
#define _VGD_BASIC_IMAGEUTILITIES_H

#include <utility>

#include "vgd/vgd.hpp"
#include "vgd/Shp.hpp"
#include "vgd/basic/Image.hpp"



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


/**
 * @brief Collection of methods to apply on images.
 * 
 * @ingroup g_images
 * 
 * @todo setAlpha() and setAlphaIfNotBlack() don't traverse the whole image (depth is not used !!!)
 */
struct VGD_API ImageUtilities
{
	/**
	 * @brief Compute the minimum and maximum intensity values for the given image.
	 * 
	 * @pre pImage->format() == LUMINANCE
	 * @pre pImage->type() == IImage::UINT8
	 * 
	 * @param pImage	3d image where slice is extract
	 * 
	 * @todo remove precondition on type() 
	 */
	static std::pair< float, float > computeMinMax( const IImage* pImage );
	
	/**
	 * @brief Extract a slice (2d image) from a 3d image.
	 * 
	 * @pre pImage->type() == IImage::UINT8
	 * 
	 * @pre pImage->width() > 0
	 * @pre pImage->height() > 0
	 * @pre pImage->depth() > 0
	 * @pre if slice == AXIAL_SLICE then 0 <= position < pImage->depth()
	 * @pre if slice == FRONTAL_SLICE then 0 <= position < pImage->height()
	 * @pre if slice == SAGITTAL_SLICE then 0 <= position < pImage->width()
	 *
	 * @param pImage	3d image where slice is extract
	 * @param slice		name of slice to must be extract
	 * @param position	position of the slice
	 * @return	a reference on the desired extracted image or a reference on an empty image if extraction is not possible
	 * 
	 * @remarks if pImage->format() == COLOR_INDEX, then the extracted image format is LUMINANCE and does'nt contain 
	 * the palette.
	 * 
	 * @todo Remove precondition on pImage->type()
	 */
	static vgd::Shp< Image > extractSlice(	const IImage*	pImage,
											const SliceType	slice,
											const uint32	position );

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
	 * @param pImage	image to scan.
	 * @param alpha		alpha value to assign.
	 */
	static void	setAlpha( IImage *pImage, const float alpha = 1.f );

	/**
	 * @brief Scan the whole image and modify alpha value of each pixel.
	 * 
	 * Sets alpha value of each pixel to \c alpha only if pixel color is != (0,0,0), otherwise sets alpha value to zero.
	 * 
	 * @pre pImage->format() == RGBA or pImage->format() == BGRA or pImage->format() == LUMINANCE_ALPHA
	 * @pre pImage->type() == UINT8
	 * @pre 0 <= alpha <= 1
	 * 
	 * @param pImage	image to scan.
	 * @param alpha		alpha value to assign.
	 */
	static void	setAlphaIfNotBlack( IImage *pImage, const float alpha = 1.f );

	/**
	 * @brief The different functions used to initialize palette.
	 */
	enum PaletteFunctionType {
		BLACK_TO_WHITE,
		WHITE_TO_BLACK,
		BLACK,
		WHITE
	};

	/**
	 * @brief Initialize palette.
	 * 
	 * @todo template version
	 * @todo Comments
	 */
	static void setupPalette(	const int32 minValue, const int32 maxValue,
								const int32 interval1, const int32 interval2,
								const PaletteFunctionType fun1, const float alpha1,
								const PaletteFunctionType fun2, const float alpha2,
								const PaletteFunctionType fun3, const float alpha3,
								uint8 *pPalette );

	/**
	 * @pre beginInterval >= minValue && beginInterval <= maxValue
	 * @pre endInterval >= minValue && endInterval <= maxValue
	 * @pre 0 <= alpha <= 1
	 * @pre pPalette is a valid reference on a palette (!= 0).
	 */
	static void setupPalette(	const int32 minValue, const int32 maxValue,
								const int32 beginInterval, const int32 endInterval,
								const PaletteFunctionType function,
								const float fAlpha,
								uint8 *pPalette );
	//@}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_IMAGEUTILITIES_H
