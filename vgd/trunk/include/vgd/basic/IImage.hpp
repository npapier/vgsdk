// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IIMAGE_HPP
#define _VGD_BASIC_IIMAGE_HPP

#include <utility>
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
	 * @brief Commits all pixels modifications after calling editPixels().
	 */
	virtual void		editPixelsDone()=0;
	
	/**
	 * @brief Tests if this class store an image.
	 * 
	 * @return		true if there is no image in this class (i.e. width()==height()==depth()==0), false otherwise.
	 */
	virtual const bool	isEmpty() const;

	/**
	 * @brief Computes the size of one pixel
	 * 
	 * @remarks The size of one pixel depends of format() and type() of the image.
	 * 
	 * @return The size of one pixel in bytes
	 */
	const uint32 sizeOfPixel() const;
	
	/**
	 * @brief Computes the whole number of pixels in the image.
	 * 
	 * @return the whole number of pixels in the image
	 */
	const uint32 computeNumberOfPixels() const;

	//@}
	
	
	/**
	 * @name Pixel accessors
	 * 
	 * @remarks These methods are not very fast. Use a PixelEditorRO/RW classes for faster accesses.
	 * 
	 * @todo PixelEditorRO/RW classes
	 */
	//@{

	/**
	 * @brief Gets a pixel color.
	 * 
	 * @param position	coordinates of pixel
	 * 
	 * @return color of pixel
	 * 
	 * @pre components() == 1
	 * @pre computeOffset(position) <= computeMaximumOffset()
	 */
	const float getPixel1( const vgm::Vec3i position ) const;

	/**
	 * @brief Gets a pixel color.
	 * 
	 * @param offset	the offset
	 * 
	 * @return color of pixel
	 * 
	 * @pre components() == 1
	 */
	const float getPixel1( const uint32 offset ) const;

	/**
	 * @brief Sets a pixel color.
	 * 
	 * @param position	coordinates of pixel
	 * @param color		color of pixel
	 * 
	 * @remarks The color is static casted (@sa type() ).
	 */
	void setPixel1( const vgm::Vec3i position, const float color );

	/**
	 * @brief Sets a pixel color.
	 * 
	 * @param offset		the offset
	 * @param color		color of pixel
	 * 
	 * @remarks The color is static casted (@sa type() ).
	 */
	void setPixel1( const uint32 offset, const float color );
	
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
	 * @name Helpers
	 */
	//@{

	/**
	 * @brief Computes the number of components for image with the specified format.
	 * 
	 * @return the number of component
	 * 
	 * @todo Should be optimized by replacing switch with a lookup table.
	 */
	static const uint32	computeNumComponents( const Format format );

	/**
	 * @brief Computes the size of one element of \c type
	 * 
	 * @return the size of one element of \c type
	 * 
	 * @todo Should be optimized by replacing the switch with a lookup table.
	 */
	static const uint32 computeSizeOfType( const Type type );

	/**
	 * @brief Computes the minimum and maximum values allowed by the given type.
	 * 
	 * @return a pair with the minimum and the maximum values
	 */
	static const std::pair< double, double > getRange( const Type type );

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
	 * @pre x < width()
	 * @pre y < height()
	 * @pre z < depth()
	 * 
	 * @return the computed offset
	 */
	const uint32 computeOffset( const uint32 x, const uint32 y, const uint32 z ) const;
	
	/**
	 * @brief Computes offset from coordinates.
	 * 
	 * @param position	coordinates
	 * 
	 * @pre position[0] < width()
	 * @pre position[1] < height()
	 * @pre position[2] < depth()
	 * 
	 * @return the computed offset
	 */	
	const uint32 computeOffset( const vgm::Vec3i position ) const;

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
	 * 
	 * @post if return value = coord, then	0 <= coord[0] < width() and
	 * 										0 <= coord[1] < height() and
	 * 										0 <= coord[2] < depth()
	 */
	const vgm::Vec3i computeCoordinates( const uint32 offset ) const;
	
	//@}
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IIMAGE_HPP
