// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGD_BASIC_IMAGEINFO_HPP
#define _VGD_BASIC_IMAGEINFO_HPP

#include <string>

#include "vgd/basic/IImage.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Store informations about an image.
 * 
 * The image data isn't stored in this class.
 * 
 * @ingroup g_images
 */
struct VGD_API ImageInfo : public IImage
{
	/**
	 * @name Constructors and destructor.
	 */
	//@{

	/**
	 * @brief Constructor setting all informations about an image.
	 * 
	 * @param width			width of the image.
	 * @param height		height of the image.
	 * @param depth			depth of the image.
	 * @param format		format of the pixel data.
	 * @param type			type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @post paletteSize()			== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()			== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 * 
	 * @post voxelSize() == vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	ImageInfo(	const uint32	width		= 0,
				const uint32	height		= 0,
				const uint32	depth		= 0,
				const Format	format		= NO_FORMAT,
				const Type		type		= NO_TYPE,
				const void*		pixels		= 0 );

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param iimage		image where informations where retrives.
	 */
	ImageInfo( const IImage& iimage );

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
	uint32&			width()					{ return ( m_width ); }
	
	/**
	 * @brief Returns the width of the image.
	 * 
	 * @return 		width of image.
	 */	
	const uint32	width() const			{ return ( m_width ); }

	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */
	uint32&			height()				{ return ( m_height ); }
	
	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */	
	const uint32	height() const			{ return ( m_height ); }

	/**
	 * @brief Returns the depth of the image.
	 * 
	 * @return		depth of image.
	 */
	uint32&			depth()					{ return ( m_depth ); }
	
	/**
	 * @brief Returns the depth of the image.
	 * 
	 * @return		depth of image.
	 */	
	const uint32	depth() const			{ return ( m_depth ); }

	/**
	 * @brief Returns the format of the pixel data.
	 * 
	 * @return		format of the pixel data.
	 */
	Format&			format()				{ return ( m_format ); }
	
	/**
	 * @brief Returns the format of the pixel data.
	 * 
	 * @return		format of the pixel data.
	 */
	const Format	format() const			{ return ( m_format ); }

	/**
	 * @brief Returns the type of the pixel data.
	 * 
	 * @return		type of the pixel data.
	 */
	Type&				type()				{ return ( m_type ); }
	
	/**
	 * @brief Returns the type of the pixel data.
	 * 
	 * @return		type of the pixel data.
	 */
	const Type		type() const			{ return ( m_type ); }

	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return a pointer to the image data in memory.
	 */
	const void*		pixels() const			{ return ( m_pixels ); }

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
	
	/**
	 * @brief Returns the pixel data pointer.
	 * 
	 * @return A reference on the pixel data pointer.
	 */
	void*&			pixelData()				{ return ( m_pixels ); }

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param width			width of the image.
	 * @param height		height of the image.
	 * @param depth			depth of the image.
	 * @param format		format of the pixel data.
	 * @param type			type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 */
	void			set(	const uint32		width		= 0,
							const uint32		height		= 0,
							const uint32		depth		= 0,
							const Format		format		= NO_FORMAT,
							const Type			type		= NO_TYPE,
							const void*			pixels		= 0 );

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param iimage		image where informations where retrives.
	 */
	void 			set( const IImage& iimage );

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
	uint32&	paletteSize() { return ( m_paletteSize ); }
	
	/**
	 * @brief Returns the size of palette.
	 * 
	 * @return 		size of palette.
	 * 
	 * @remarks		If palette is not defined, must return 0.
	 */
	const uint32	paletteSize() const { return ( m_paletteSize ); }

	/**
	 * @brief Returns the format of the palette.
	 * 
	 * @return		format of the palette.
	 * 
	 * @remarks		If palette is not defined, must return NONE.
	 */
	Format&	paletteFormat() { return ( m_paletteFormat ); }
		
	/**
	 * @brief Returns the format of the palette.
	 * 
	 * @return		format of the palette.
	 * 
	 * @remarks		If palette is not defined, must return NONE.
	 */
	const Format	paletteFormat() const { return ( m_paletteFormat ); }

	/**
	 * @brief Returns the type of the palette.
	 * 
	 * @return		type of the palette.
	 * 
	 * @remarks		If image is not defined, must return NO_TYPE.
	 */
	Type&		paletteType() { return ( m_paletteType ); }
	
	/**
	 * @brief Returns the type of the palette.
	 * 
	 * @return		type of the palette.
	 * 
	 * @remarks		If image is not defined, must return NO_TYPE.
	 */
	const Type	paletteType() const	{ return ( m_paletteType ); }
	
	/**
	 * @brief Returns a pointer to the palette data in memory.
	 * 
	 * @return		a pointer to the palette data in memory.
	 * 
	 * @remarks		If palette is not defined, must return 0.
	 */
	const void*	palettePixels() const { return ( m_palettePixels ); }

	/**
	 * @brief Returns a pointer to the palette in memory.
	 * 
	 * @return		a pointer to the palette in memory.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	void*		paletteEditPixels();
	
	/**
	 * @brief Commit all pixels modifications in palette after calling paletteEditPixels().
	 */
	void		paletteEditPixelsDone();	
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
	vgm::Vec3f&				voxelSize();

	/**
	 * @brief Returns the size of a voxel.
	 * 
	 * @return		a 3d vector with the voxel size for each dimension.
	 */
	const vgm::Vec3f		voxelSize() const;
	
	/**
	 * @brief Returns if voxelSize is supported.
	 * 
	 * @return		true if supported, false otherwise.
	 */
	const bool				isVoxelSizeSupported() const;

	//@}


protected:
	/**
	 * @name Image informations
	 */
	//@{

	uint32		m_width;
	uint32		m_height;
	uint32		m_depth;

	Format		m_format;
	Type		m_type;
	
	void*		m_pixels;

	bool		m_edit;
	//@}
	
	/**
	 * @name Palette informations
	 */
	//@{
	uint32		m_paletteSize;

	Format		m_paletteFormat;
	Type		m_paletteType;
	
	void*		m_palettePixels;
	
	bool		m_paletteEdit;
	//@}
	
	/**
	 * @brief Voxel size informations.
	 */
	vgm::Vec3f	m_voxelSize;	
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IMAGEINFO_HPP
