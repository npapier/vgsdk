// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IMAGE_H
#define _VGD_BASIC_IMAGE_H

#include "vgd/vgd.hpp"

#include <string>
#include <IL/il.h>

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
 * @todo Support 3d images.
 * @todo Support other image format FLOAT, USHORT, UINT...
 * 
 * @todo use exception for error handling.
 *
 * @ingroup g_images
 */
struct VGD_API Image : public IImage
{
	/**
	 * @name Constructors and destructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	Image();
	
	/**
	 * @brief Image constructor from a file.
	 * 
	 * @param strFilename		filename of image to load.
	 */
	Image( std::string strFilename );

	/**
	 * @brief Image contructor from memory.
	 * 
	 * The image data is copied.
	 * 
	 * @param components		number of color components.
	 * @param width			width of the image.
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * @param pixels			pointer to the image data in memory.
	 */
	Image(		const int32		components,
					const int32		width, const int32 height,
					const Format	format,
					const Type		type,
					const uint8*	pixels );

	/**
	 * @brief Image contructor : Create a new image.
	 * 
	 * @param components		number of color components.
	 * @param width			width of the image.
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * 
	 * @todo add param color
	 */
	Image(		const int32		components,
					const int32		width, const int32 height,
					const Format	format,
					const Type		type );
					
	/**
	 * @brief Image contructor from an IImage.
	 * 
	 * The image data is copied.
	 * 
	 * @param iimage			IImage
	 */
	Image(		const IImage& iimage );

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
	 * @name Creation/destruction image methods.
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
	 * @param components		number of color components.
	 * @param width			width of the image.
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * @param pixels			pointer to the image data in memory.
	 */
	bool	create(	const int32		components, 
						const int32		width, const int32 height,
						const Format	format,
						const Type		type,
						const uint8*	pixels );

	/**
	 * @brief Create a new image.
	 * 
	 * @param components		number of color components.
	 * @param width			width of the image.
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 */
	bool	create(	const int32		components, 
						const int32		width, const int32 height,
						const Format	format,
						const Type		type );

	/**
	 * @brief Create an image from an IImage.
	 * 
	 * The image data is copied.
	 * 
	 * @param iimage			IImage
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
	 * @name Apply action on image methods.
	 */
	//@{

	/**
	 * @brief Convert the current image to another format.
	 * 
	 * @param format		destination format of image(except LUMINANCE_ALPHA).
	 * 
	 * @todo Documentation of what is done by convert exactly(see DevIL).
	 */
	bool	convertTo( const Format format );
	//@}



	/**
	 * @name Image accessor methods.
	 */
	//@{

	/**
	 * @brief Returns the number of color components.
	 * 
	 * Typical values are 1, 2, 3, 4.
	 * 
	 * @return		number of color components.
	 */
	const int32		components() const;

	/**
	 * @brief Returns the width of the image.
	 * 
	 * @return 		width of image.
	 */
	const int32		width() const;

	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */
	const int32		height() const;

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
	const uint8*	pixels() const;

	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return a pointer to the image data in memory.
	 * 
	 * @remarks Call editPixelsDone() when you have finished editing pixels.
	 */
	uint8*			editPixels();
	
	/**
	 * @brief Commit all pixels modifications after calling editPixels().
	 */
	void 				editPixelsDone();
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
	bool		bind() const;

	bool		reportILError() const;

	Format	convertIL2My	( ILint format	) const;
	ILint		convertMy2IL	( Format format	) const;
	
	void		resetInformations	();
	void		updateInformations();
	//@}


	/**
	 * @name Image data and informations.
	 */
	//@{

	/**
	 * id for image library, 0 otherwise(no image specified or not yet loaded).
	 */
	ILuint	m_iluintImgID;
	
	int32		m_components;
	int32		m_width;
	int32		m_height;
	Format	m_format;
	Type		m_type;
	bool		m_edit;
	//@}
	
	/**
	 * @brief Used to know if this instance is the first one or not (for doiing some initializations).
	 */
	static bool	m_firstInstance;	
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IMAGE_H
