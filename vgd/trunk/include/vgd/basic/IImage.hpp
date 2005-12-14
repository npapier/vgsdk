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
 * @todo type.BOOL and LUMINANCE8_ALPHA8...
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
		LUMINANCE_ALPHA,
		COLOR_INDEX
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
	 * @name Image accessors
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
	virtual void*		editPixels()=0;
	
	/**
	 * @brief Commit all pixels modifications after calling editPixels().
	 */
	virtual void		editPixelsDone()=0;
	
	/**
	 * @brief Test if this class store an image.
	 * 
	 * @return		true if there is no image in this class (i.e. width()==height()==depth()==0), false otherwise.
	 */
	virtual const bool	isEmpty() const;
	
	/**
	 * @brief Compute the number of component for image with the specified format.
	 */
	static const uint32	computeNumComponents( const Format format );
	//@}
	


	/**
	 * @name Palette accessors
	 */
	//@{

	/**
	 * @brief Returns the size of palette.
	 * 
	 * @return 		size of palette.
	 * 
	 * @remarks		If palette is not defined, must return 0.
	 */
	virtual const uint32	paletteSize() const=0;

	/**
	 * @brief Returns the format of the palette.
	 * 
	 * @return		format of the palette.
	 * 
	 * @remarks		If palette is not defined, must return NONE.
	 */
	virtual const Format	paletteFormat() const=0;

	/**
	 * @brief Returns the type of the palette.
	 * 
	 * @return		type of the palette.
	 * 
	 * @remarks		If image is not defined, must return NO_TYPE.
	 */
	virtual const Type	paletteType() const=0;
	
	/**
	 * @brief Returns a pointer to the palette data in memory.
	 * 
	 * @return		a pointer to the palette data in memory.
	 * 
	 * @remarks		If palette is not defined, must return 0.
	 */
	virtual const void*	palettePixels() const=0;

	/**
	 * @brief Returns a pointer to the palette in memory.
	 * 
	 * @return		a pointer to the palette in memory.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	virtual void*		paletteEditPixels()=0;
	
	/**
	 * @brief Commit all pixels modifications in palette after calling paletteEditPixels().
	 */
	virtual void		paletteEditPixelsDone()=0;	
	//@}
	
	
	/**
	 * @name Voxel size accessors
	 */
	//@{

	/**
	 * @brief Returns the size of a voxel.
	 * 
	 * @return		a 3d vector with the voxel size for each dimension.
	 */
	virtual const vgm::Vec3f	voxelSize() const=0;
	
	/**
	 * @brief Returns if voxelSize is supported.
	 * 
	 * @return		true if supported, false otherwise.
	 */
	virtual const bool			isVoxelSizeSupported() const=0;
	//@}
	
	
	
	/**
	 * @name Offset helpers
	 */
	//@{
	
	/**
	 * @brief Computes offset from coordinates.
	 * 
	 * @param x		x-coordinate
	 * @param y		y-coordinate
	 * @param z		z-coordinate
	 * 
	 * @return the computed offset
	 */
	const uint32 computeOffset( const uint32 x, const uint32 y, const uint32 z );
	
	/**
	 * @brief Computes offset from coordinates.
	 * 
	 * @param position	coordinates
	 * 
	 * @return the computed offset
	 */	
	const uint32 computeOffset( const vgm::Vec3i position );
	
	/**
	 * @brief Computes maximum offset in the image.
	 * 
	 * @return the maximum offset
	 */
	const uint32 computeMaximumOffset() const;
	
	/**
	 * @brief Computes coordinates from offset.
	 * 
	 * @param offset		the offset
	 * 
	 * @return the computed coordinates
	 */
	const vgm::Vec3i computeCoordinates( const uint32 offset ) const;
	
	//@}
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IIMAGE_H
