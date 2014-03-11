// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCAIRO_IMAGESURFACE_HPP
#define _VGCAIRO_IMAGESURFACE_HPP

#include <cairo.h>
#include <string>
#include <vgd/basic/IImage.hpp>

#include "vgCairo/vgCairo.hpp"



namespace vgCairo
{



/**
 * @brief Implements IImage interface using cairo image backend.
 *
 * @todo cairomm
 * @todo load/save svg
 * @todo Support of other cairo backends (or other cairo surfaces)
 * 
 * @ingroup g_images
 */
struct VGCAIRO_API ImageSurface : public ::vgd::basic::IImage
{
	/**
	 * @name Constructors and destructor
	 *
	 * @todo ImageSurface( pixels, owner = true|false)
	 * @todo ImageSurface( const IImage& iimage );
	 */
	//@{

	/**
	 * @brief Creates an image surface.
	 *
	 * @param width		width of the image
	 * @param height	height of the image
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()	== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()	== 0
	 * @post paletteEditPixels()	== 0
	 * 
	 * @post voxelSize() == vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	ImageSurface( const uint32 width, const uint32 height );
	
	/**
	 * @brief Creates an image surface and initializes its contents with the given PNG file.
	 *
	 * @param filename	name of PNG to load
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()	== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()	== 0
	 * @post paletteEditPixels()	== 0
	 * 
	 * @post voxelSize() == vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	ImageSurface( const std::string filename );
	
	/**
	 * @brief Destructor
	 */
	~ImageSurface();

	//@}



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
	 */	
	const uint32	components() const;

	/**
	 * @brief Returns the width of the image.
	 * 
	 * @return 		width of image.
	 */	
	const uint32	width() const;

	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */	
	const uint32	height() const;

	/**
	 * @brief Returns the depth of the image.
	 * 
	 * @return		depth of image.
	 */	
	const uint32	depth() const;

	/**
	 * @brief Returns the format of the pixel data.
	 * 
	 * @return		format of the pixel data.
	 */
	const Format	format() const;
	
	/**
	 * @brief Returns the type of the pixel data.
	 * 
	 * @return		type of the pixel data.
	 */
	const Type		type() const;

	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return a pointer to the image data in memory.
	 */
	const void*		pixels() const;

	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return a pointer to the image data in memory.
	 */
	void*			editPixels();

	/**
	 * @brief Commit all pixels modifications after calling editPixels().
	 */	
	void			editPixelsDone();

	//@}



	/**
	 * @name Png support
	 *
	 * @see ImageSurface( const std::string filename ) to read PNG file.
	 */
	//@{
	
	/**
	 * @brief Writes to a new file as a PNG image.
	 *
	 * @param filename	the name of a file to write to
	 */
	void write( const std::string filename );

	//@}



	/**
	 * @name Cairo accessors
	 */
	//@{
	
	/**
	 * @brief Retrieves the cairo surface
	 * 
	 * @return a pointer on the cairo surface
	 */
	cairo_surface_t	* getSurface() { return m_surface; }

	/**
	 * @brief Retrieves the cairo context
	 *
	 * @return a pointer on the cairo context
	 */
	cairo_t * getContext() { return m_cairo; }
	//@}



	/**
	 * @name Palette accessors
	 *
	 * @remarks Palette is not supported.
	 */
	//@{

	/**
	 * @brief Returns the size of palette.
	 * 
	 * @return 		size of palette.
	 * 
	 * @remarks	If palette is not defined, must return 0.
	 */
	const uint32	paletteSize() const { return 0; }
		
	/**
	 * @brief Returns the format of the palette.
	 * 
	 * @return		format of the palette.
	 * 
	 * @remarks	If palette is not defined, must return NONE.
	 */
	const Format	paletteFormat() const { return NO_FORMAT; }
	
	/**
	 * @brief Returns the type of the palette.
	 * 
	 * @return		type of the palette.
	 * 
	 * @remarks	If image is not defined, must return NO_TYPE.
	 */
	const Type	paletteType() const	{ return NO_TYPE; }
	
	/**
	 * @brief Returns a pointer to the palette data in memory.
	 * 
	 * @return		a pointer to the palette data in memory.
	 * 
	 * @remarks	If palette is not defined, must return 0.
	 */
	const void*	palettePixels() const { return 0; }

	/**
	 * @brief Returns a pointer to the palette in memory.
	 * 
	 * @return		a pointer to the palette in memory.
	 * 
	 * @remarks	If image is not defined, must return 0.
	 */
	void*		paletteEditPixels() { return 0; }
	
	/**
	 * @brief Commit all pixels modifications in palette after calling paletteEditPixels().
	 */
	void		paletteEditPixelsDone() {}
	//@}


	/**
	 * @name Voxel size accessors
	 *
	 * @remarks Voxel size is not supported.
	 */
	//@{

	/**
	 * @brief Returns the size of a voxel.
	 * 
	 * @return a 3d vector with the voxel size for each dimension.
	 */
	const vgm::Vec3f		voxelSize() const { return vgm::Vec3f(1.f, 1.f, 1.f); }

	/**
	 * @brief Returns if voxelSize is supported.
	 * 
	 * @return true if supported, false otherwise.
	 */
	const bool				isVoxelSizeSupported() const { return false; }

	//@}



protected:

	/**
	 * @brief Checks whether an error has previously occurred for the surface
	 *
	 * @todo Throws an exception
	 */
	void checkCairoSurfaceStatus();



	bool m_edit;	//< see editPixel()

	/**
	 * @name cairo objects
	 */
	//@{
	uint8 *				m_pixels;	//< pointer of the pixel buffer
	cairo_surface_t	*	m_surface;	//< the cairo surface
	cairo_t *			m_cairo;	//< the cairo context
	//@}
};



} // namespace vgCairo

#endif // #ifndef _VGCAIRO_IMAGESURFACE_HPP
