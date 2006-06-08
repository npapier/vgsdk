// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
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
	 * @brief Retrives the position of the last pixel in the image.
	 * 
	 * @return the position of the last pixel in the image
	 * 
	 * @remarks computeMaximumPosition() == getSize()
	 */
	const vgm::Vec3i computeMaximumPosition() const;
	
	/**
	 * @brief Retrives the size of the image.
	 * 
	 * @return the size of the image.
	 * 
	 * @remarks computeMaximumPosition() == getSize()
	 */
	const vgm::Vec3i getSize() const;

	/**
	 * @brief Computes the whole number of pixels in the image.
	 * 
	 * @return the whole number of pixels in the image
	 * 
	 * @remarks computeMaximumIndex() == computeNumberOfPixels()
	 */
	const uint32 computeNumberOfPixels() const;

	/**
	 * @brief Computes the maximum index in the image.
	 * 
	 * @return the maximum index in the image.
	 * 
	 * @remarks computeMaximumIndex() == computeNumberOfPixels()
	 */
	const uint32 computeMaximumIndex() const;
	
	/**
	 * @brief Computes maximum offset in the image.
	 * 
	 * @return the maximum offset
	 */
	const uint32 computeMaximumOffset() const;

	//@}
	

	
	/**
	 * @name Pixel accessors
	 * 
	 * @remarks These methods are relatively slow and should not be used in situations where high-performance access
	 * is required. Use a PixelEditorRO/RW classes for efficient pixel accesses.
	 * 
	 * @todo PixelEditorRO/RW classes
	 */
	//@{

	/**
	 * @brief Gets the color of a pixel.
	 * 
	 * @param position		coordinates of the pixel
	 * 
	 * @return color of a pixel
	 * 
	 * @pre components() == 1
	 * @pre isValid( position )
	 */
	const float getPixel1( const vgm::Vec3i position ) const;

	/**
	 * @brief Gets the color of a pixel.
	 * 
	 * @param index		index of the pixel
	 * 
	 * @return color of a pixel
	 * 
	 * @pre components() == 1
	 * @pre isValid( index )
	 */
	const float getPixel1( const uint32 index ) const;

	/**
	 * @brief Sets the color of a pixel.
	 * 
	 * @param position	coordinates of the pixel
	 * @param color		color of the pixel
	 * 
	 * @pre components() == 1
	 * @pre isValid( position )
	 * 
	 * @remarks The color is static casted to the type of the image (@sa type() ).
	 */
	void setPixel1( const vgm::Vec3i position, const float color );

	/**
	 * @brief Sets the color of a pixel.
	 * 
	 * @param index		index of the pixel
	 * @param color		color of the pixel
	 * 
	 * @pre components() == 1
	 * @pre isValid( index )
	 * 
	 * @remarks The color is static casted to the type of the image (@sa type() ).
	 */
	void setPixel1( const uint32 index, const float color );

	/**
	 * @brief Checks if the given position is valid
	 * 
	 * @param position 	the coordinates
	 * 
	 * @return true if the given position is valid, false otherwise.
	 * 
	 * Note that the given position is valid, if and only if :
	 * - 0 <= position[0] < width() and
	 * - 0 <= position[1] < height() and
	 * - 0 <= position[2] < depth()
	 */
	const bool isValid( const vgm::Vec3i position ) const;

	//@}



	/**
	 * @name Palette accessors
	 * 
	 * @todo Palette Pixel accessors
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
	 * @name Index helpers
	 */
	//@{
	
	/**
	 * @brief Computes index from coordinates.
	 * 
	 * @param x		x-coordinate
	 * @param y		y-coordinate
	 * @param z		z-coordinate
	 * 
	 * @pre x < width()
	 * @pre y < height()
	 * @pre z < depth()
	 * 
	 * @return the computed index
	 */
	const uint32 computeIndex( const uint32 x, const uint32 y, const uint32 z ) const;

	/**
	 * @brief Computes index from coordinates.
	 * 
	 * @param position	(x,y,z) coordinates
	 * 
	 * @pre isValid(position)
	 * 
	 * @return the computed index
	 */
	const uint32 computeIndex( const vgm::Vec3i position ) const;
	
	/**
	 * @brief Computes the coordinates from an index.
	 * 
	 * @param index		the index
	 * 
	 * @return the computed coordinates
	 * 
	 * @post if return value = coord, then	isValid(coord) is true
	 */
	const vgm::Vec3i computePosition( const uint32 index ) const;

	/**
	 * @brief Checks if the given index is valid
	 * 
	 * @param index		the index
	 * 
	 * @return true if the given index is valid, false otherwise.
	 * Note that the given index is valid, if and only if offset < computeMaximumIndex()
	 */
	const bool isValid( const uint32 index ) const;
	
	//@}
	
	
	
	/**
	 * @name Offset helpers
	 */
	//@{

	/**
	 * @brief Computes the size of one pixel.
	 * 
	 * @remarks The size of one pixel depends of format() and type() of the image.
	 * 
	 * @return The size of one pixel in bytes
	 */
	const uint32 sizeOfPixel() const;
	
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
	 * @pre isValid(position)
	 * 
	 * @return the computed offset
	 */
	const uint32 computeOffset( const vgm::Vec3i position ) const;

	/**
	 * @brief Computes offset from index.
	 * 
	 * @param index		the index
	 * 
	 * @pre isValid(index)
	 * 
	 * @return the offset
	 */
	const uint32 computeOffset( const uint32 index ) const;

	/**
	 * @brief Computes the pixel position from an offset.
	 * 
	 * @param offset		the offset
	 * 
	 * @return the computed pixel position
	 *
	 * @pre isOffsetValid( offset )
	 *  
	 * @post if return value = position, then isValid(position) must be true.
	 */
	const vgm::Vec3i computePositionFromOffset( const uint32 offset ) const;
	
	/**
	 * @brief Computes index from offset.
	 * 
	 * @param offset	the offset
	 * 
	 * @pre isOffsetValid(offset)
	 * @pre sizeOfPixel() > 0
	 * 
	 * @return the index
	 */
	const uint32 computeIndexFromOffset( const uint32 offset ) const;	

	/**
	 * @brief Checks if the given offset is valid
	 * 
	 * @param offset		the offset
	 * 
	 * @return true if the given offset is valid, false otherwise.
	 * Note that the given offset is valid, if and only if 0 <= offset < computeMaximumOffset()
	 */
	const bool isOffsetValid( const uint32 offset ) const;

	//@}
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IIMAGE_HPP
