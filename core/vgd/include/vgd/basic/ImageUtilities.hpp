// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGD_BASIC_IMAGEUTILITIES_HPP
#define _VGD_BASIC_IMAGEUTILITIES_HPP

#include <vgm/operations.hpp>
#include "vgd/Shp.hpp"
#include "vgd/basic/Image.hpp"
#include "vgd/basic/MinMax.hpp"



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
 */
struct VGD_API ImageUtilities
{
	/**
	 * @brief Compute the minimum and maximum intensity values for the given image.
	 * 
	 * @pre pImage->format() == LUMINANCE_ALPHA or LUMINANCE or COLOR_INDEX
	 * 
	 * @param pImage	3d image
	 * 
	 * @remark	Be careful, for image in COLOR_INDEX the minimum and maximum are computed for the indices
	 *			and not the colors.
	 * 
	 * @remark	Alpha is not taken into account.
	 */
	static const MinMax computeMinMax( const IImage* pImage );

	/**
	 * @brief Helpers
	 * 
	 * @see computeMinMax(const IImage*)
	 */
	static const MinMax computeMinMax( const vgd::Shp< IImage > image );
	
	/**
	 * @brief Creates an image by converting the specified image into the given type.
	 * 
	 * @param	srcImage	the image to use as source
	 * @param	dstType		the type of the newly created image
	 * @param	minMax		a valid (min,max) of the image used during the convertion phase.
	 * 						Or an invalid (min,max) if it must be computed by this method.
	 * 
	 * @return	a shared pointer to the created image or an empty image if convertion is not possible.
	 * 
	 * @pre	image->format() == IImage::LUMINANCE
	 * @pre image->components() == 1
	 * @pre image->type() == IImage::UINT8, or IImage::INT16
	 * @pre dstType == IImage::UINT8
	 * 
	 * @todo remove preconditions (a template version ?)
	 */
	static vgd::Shp< Image > createImage( const vgd::Shp< IImage> srcImage, const IImage::Type dstType, MinMax& minMax );

	/**
	 * @brief Extract a slice (2d image) from a 3d image.
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
	 */
	static vgd::Shp< Image > extractSlice( const IImage* pImage, const SliceType	slice, const uint32	position );

	/**
	 * @name Useful scanning image methods.
	 */
	//@{

	/**
	 * @brief Scan the whole image and set alpha value of each pixel to the luminance value multiplied by a scale factor
	 * 
	 * @pre pImage->format() == LUMINANCE_ALPHA
	 * @pre pImage->type() == UINT8
	 * 
	 * @param pImage	image to scan
	 * @param scale		the luminance value is multiplied by a scale factor
	 */
	static void	setAlphaFromLuminance( IImage *pImage, const float scale = 1.f );
	
	/**
	 * @brief Scan the whole image and set alpha value of each pixel to \c alpha.
	 * 
	 * @pre pImage->format() == RGBA or pImage->format() == BGRA or pImage->format() == LUMINANCE_ALPHA
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
		BLACK,		
		BLACK_TO_WHITE,
		WHITE_TO_BLACK,
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



	/**
	 * @brief	Converts the given alpha value into the given component type.
	 * 
	 * @param	alpha	an alpha value to convert
	 * 
	 * @return	the alpha representation in a given component type
	 */
	template< typename ComponentType >
	static const ComponentType convertAlpha( const float alpha );



private:

	/**
	 * @brief	Invoked by computeMinMax, performs the effective mix and max pixel value computation.
	 * 
	 * @see		computeMixMax
	 */
	template< typename ComponentType >
	static const MinMax doComputeMinMax( const IImage* pImage );

	/**
	 * @brief	Invoked by extractSlice, performs the effective slice image extraction.
	 * 
	 * @see		extractSlice
	 */
	template< typename ComponentType >
	static vgd::Shp< Image > doExtractSlice( const IImage*	pImage, const SliceType	slice, const uint32	position );
	
	/**
	 * @brief	Invoked by setAlpha, performs the effective alpha layer value update.
	 * 
	 * @see		setAlpha
	 */
	template< typename ComponentType >
	static void	doSetAlpha( IImage *pImage, const float alpha );	
	
	/**
	 * @brief	Invoked by setAlphaIfNotBlack, performs the effective alpha layer value update.
	 * 
	 * @see		setAlphaIfNotBlack
	 */
	template< typename ComponentType >
	static void	doSetAlphaIfNotBlack( IImage *pImage, const float alpha );	
	 
};



} // namespace basic

} // namespace vgd



#include "vgd/basic/ImageUtilities.hxx"



#endif //#ifndef _VGD_BASIC_IMAGEUTILITIES_HPP
