// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IIMAGE_H
#define _VGD_BASIC_IIMAGE_H

#include <vgm/Vector.hpp>
#include "vgd/vgd.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Abstract interface for image (1, 2 or 3 dimensions).
 * 
 * @todo Format: COLOR_INDEX image.
 * 
 * @todo LUMINANCE8_ALPHA8 and others ?
 * 
 * @ingroup g_images
 */
struct VGD_API IImage
{
	/**
	 * @brief Format of image.
	 */
	typedef enum {
		NO_FORMAT	= 0,
		RGB,
		RGBA,
		BGR,
		BGRA,
		LUMINANCE,
		LUMINANCE_ALPHA
	} Format;
	
	/**
	 * @brief Type of image.
	 */
	typedef enum {
		NO_TYPE = 0,
		//BOOL	= 1,
		UINT8,
		INT8,
		UINT16,
		INT16,
		UINT32,
		INT32,
		FLOAT,
		DOUBLE
	} Type;

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~IImage();



	/**
	 * @name Accessor to image.
	 */
	//@{

	/**
	 * @brief Returns the number of color components.
	 * 
	 * Typical values are 1, 2, 3, 4.
	 * 
	 * @return		number of color components.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual const uint32	components() const=0;

	/**
	 * @brief Returns the width of the image.
	 * 
	 * @return 		width of image.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual const uint32	width() const=0;

	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual const uint32	height() const=0;

	/**
	 * @brief Returns the depth of the image.
	 * 
	 * @return		depth of image.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual const uint32	depth() const=0;

	/**
	 * @brief Returns the format of the pixel data.
	 * 
	 * @return		format of the pixel data.
	 * 
	 * @remarks		If image is not defined, must return NONE.
	 */
	virtual const Format	format() const=0;

	/**
	 * @brief Returns the type of the pixel data.
	 * 
	 * @return		type of the pixel data.
	 * 
	 * @remarks		If image is not defined, must return NO_TYPE.
	 */
	virtual const Type	type() const=0;
	
	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return		a pointer to the image data in memory.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual const void*	pixels() const=0;

	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return		a pointer to the image data in memory.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual void*			editPixels()=0;
	
	/**
	 * @brief Commit all pixels modifications after calling editPixels().
	 */
	virtual void			editPixelsDone()=0;
	
	/**
	 * @brief Returns the size of a voxel.
	 * 
	 * @return		a 3d vector with the voxel size for each dimension.
	 */
	virtual const vgm::Vec3f	voxelSize() const=0;

	/**
	 * @brief Test if this class store an image.
	 * 
	 * @return		true if there is no image in this class (i.e. width()==height()==depth()==0), false otherwise.
	 */
	virtual const bool	isEmpty() const;
	//@}
	
	/**
	 * @brief Compute the number of component for image with the specified format.
	 */
	const uint32			computeNumComponents( const Format format ) const;
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IIMAGE_H
