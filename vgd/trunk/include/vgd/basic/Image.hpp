// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IMAGE_HPP
#define _VGD_BASIC_IMAGE_HPP

#include <string>
#include <IL/il.h>

#include "vgd/Shp.hpp"
#include "vgd/vgd.hpp"
#include "vgd/basic/IImage.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Store an image.
 *
 * @remarks This class use the DevIL image library inside.
 * @sa http://openil.sourceforge.net/
 *
 * @todo Remove m_* that could be given by OpenIL.
 * 
 * @todo use exception for error handling ?
 *
 * @ingroup g_images
 */
struct VGD_API Image : public IImage
{
	/**
	 * @name Constructors and destructor
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 * 
	 * @post components()			== 0
	 * @post isEmpty()				== true
	 * @post format()				== NO_FORMAT
	 * @post type()					== NO_TYPE
	 * @post pixels()				== 0
	 * @post editPixels()			== 0
	 * 
	 * @post paletteSize()			== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()			== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 * 
	 * @post voxelSize()			== vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	Image();

	/**
	 * @brief Image constructor from a file.
	 * 
	 * @param strFilename		filename of image to load.
	 * 
	 * @post voxelSize()	== vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	Image( std::string strFilename );

	/**
	 * @brief Image contructor from memory.
	 * 
	 * The image data is copied.
	 * 
	 * @param components	number of color components.
	 * @param width			width of the image.
	 * @param height		height of the image.
	 * @param depth			depth of the image.
	 * @param format		format of the pixel data.
	 * @param type			type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @pre format != COLOR_INDEX
	 */
	Image(		const uint32		components,
				const uint32		width, const uint32 height, const uint32 depth,
				const Format		format,
				const Type			type,
				const void*			pixels );

	/**
	 * @brief Image contructor : Create a new image.
	 * 
	 * @param components	number of color components.
	 * @param width			width of the image.
	 * @param height		height of the image.
	 * @param depth			depth of the image.
	 * @param format		format of the pixel data.
	 * @param type			type of the pixel data.
	 * 
	 * @pre format != COLOR_INDEX
	 * 
	 * @todo add param color
	 */
	Image(		const uint32		components,
				const uint32		width, const uint32 height, const uint32 depth,
				const Format		format,
				const Type			type	);

	/**
	 * @brief Image contructor from an IImage.
	 * 
	 * The image data is copied.
	 * 
	 * @param iimage			IImage
	 * 
	 * @pre iimage.format() != COLOR_INDEX
	 */
	Image( const IImage& iimage );

	/**
	 * @brief Copy constructor.
	 * 
	 * @param src		image to be copied.
	 */
	Image( const Image& src );

	/**
	 * @brief Assignment operator.
	 * 
	 * @param src		image to be copied.
	 * @return			copied image.
	 */
	Image&	operator = ( const Image& src );

	/**
	 * @brief Destructor.
	 */
	~Image();
	//@}


	/**
	 * @name Creation/destruction image methods
	 */
	//@{

	/**
	 * @brief Create an image from a file.
	 * 
	 * @param strFilename		filename of image to load.
	 * 
	 * @remarks The type of file is based on the file extension for all input/output operation on file.
	 * 
	 * @remarks All supported format of ImageLib(DevIL). 
	 * Enumeration of supported format : mainly bmp, dds, jpg, psd, psp, raw, tga, tiff.
	 */
	bool	load( std::string strFilename );

	/**
	 * @brief Create an image from memory.
	 * 
	 * Create a copy of the specified image.
	 * 
	 * @param components	number of color components.
	 * @param width			width of the image.
	 * @param height		height of the image.
	 * @param depth			depth of the image.
	 * @param format		format of the pixel data.
	 * @param type			type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @pre format != COLOR_INDEX
	 */
	bool	create(	const uint32		components, 
					const uint32		width, const uint32 height, const uint32 depth,
					const Format		format,
					const Type			type,
					const void*			pixels );

	/**
	 * @brief Create a new image.
	 * 
	 * @param components	number of color components.
	 * @param width			width of the image.
	 * @param height		height of the image.
	 * @param depth			depth of the image.
	 * @param format		format of the pixel data.
	 * @param type			type of the pixel data.
	 * 
	 * @pre format != COLOR_INDEX
	 */
	bool	create(	const uint32		components, 
					const uint32		width, const uint32 height, const uint32 depth,
					const Format		format,
					const Type			type	);

	/**
	 * @brief Create an image from an IImage.
	 * 
	 * The image data is copied.
	 * 
	 * @param iimage			IImage
	 * 
	 * @pre format != COLOR_INDEX
	 */
	bool create( const IImage& iimage );

	/**
	 * @brief Save the current image to a file.
	 *
	 * Enumeration of supported format : mainly bmp, dds, jpg, pcx, png, pnm, raw, tga, tiff.
	 */
	bool	save( const std::string filename ) const;
	
	/**
	 * @brief Destroy image.
	 */
	void	destroy();
	//@}



	/**
	 * @name Actions on image
	 */
	//@{

	/**
	 * @brief Convert image to another type/format of image.
	 * 
	 * @param format		desired format of the converted image
	 * @param type			desired type of the converted image
	 * 
	 * @todo Documentation of what is done exactly by convert (see DevIL).
	 */
	bool	convertTo( const Format format, const Type type );
	//@}



	/**
	 * @name Image accessor methods
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
	 * 
	 * @remarks Call editPixelsDone() when you have finished editing pixels.
	 */
	void*			editPixels();
	
	/**
	 * @brief Commit all pixels modifications after calling editPixels().
	 */
	void 			editPixelsDone();
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
	const uint32	paletteSize() const;

	/**
	 * @brief Returns the format of the palette.
	 * 
	 * @return		format of the palette.
	 * 
	 * @remarks		If palette is not defined, must return NONE.
	 */
	const Format	paletteFormat() const;

	/**
	 * @brief Returns the type of the palette.
	 * 
	 * @return		type of the palette.
	 * 
	 * @remarks		If image is not defined, must return NO_TYPE.
	 */
	const Type		paletteType() const;
	
	/**
	 * @brief Returns a pointer to the palette data in memory.
	 * 
	 * @return		a pointer to the palette data in memory.
	 * 
	 * @remarks		If palette is not defined, must return 0.
	 */
	const void*		palettePixels() const;

	/**
	 * @brief Returns a pointer to the palette in memory.
	 * 
	 * @return		a pointer to the palette in memory.
	 * 
	 * @remarks		If image is not defined, must return 0.
	 */
	void*			paletteEditPixels();
	
	/**
	 * @brief Commit all pixels modifications in palette after calling paletteEditPixels().
	 */
	void			paletteEditPixelsDone();
	
	/**
	 * @brief Sets the palette.
	 * 
	 * @param palette		palette to copy to internal palette.
	 * @param size			size of palette in bytes.
	 * @param format		format of the palette.
	 * 
	 * @pre format==RGB or format==RGBA or format==BGR or format==BGRA
	 */
	void			setPalette( const void *palette, uint32 size, const Format format );

	/**
	 * @brief Create an image with the palette.
	 * 
	 * @return an image that contains a copy of the palette data.
	 */
	vgd::Shp< Image >	getPaletteImage() const;
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
	const bool	isVoxelSizeSupported() const;	

	//@}



private:

	/**
	 * @name DevIL encapsulation methods.
	 */
	//@{

	/**
	 * @brief Code of copy constructor.
	 */
	void		copy( const Image& src );
 
	/**
	 * @brief Must be called before using DevIL methods on an image.
	 */
	bool	bind() const;

	bool	reportILError() const;

	Format	convertILFormat2My( ILenum format	) const;
	Format	convertILPalFormat2My( ILenum format	) const;

	ILenum	convertMyFormat2IL( Format format	) const;
	ILenum	convertMyFormat2ILPal( Format format	) const;
	
	Type	convertILType2My( ILenum type	) const;
	ILenum	convertMyType2IL( Type myType ) const;
	
	void	resetInformations	();
	void	updateInformations();
	//@}


	/**
	 * @name Image data and informations.
	 */
	//@{

	/**
	 * @brief id for image library, 0 otherwise(no image specified or not yet loaded).
	 */
	ILuint		m_iluintImgID;
	
	uint32		m_components;
	uint32		m_width;
	uint32		m_height;
	uint32		m_depth;	
	Format		m_format;
	Type		m_type;

	bool		m_edit;
	//@}

	/**
	 * @brief Voxel size informations.
	 */
	vgm::Vec3f	m_voxelSize;
		
	/**
	 * @brief Used to know if this instance is the first one or not (for doiing some initializations).
	 */
	static bool	m_firstInstance;	
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IMAGE_HPP
