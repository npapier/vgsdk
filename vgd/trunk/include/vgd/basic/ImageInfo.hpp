// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IMAGEINFO_H
#define _VGD_BASIC_IMAGEINFO_H

#include <string>

#include "vgd/vgd.hpp"
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
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * @param pixels			pointer to the image data in memory.
	 */
	ImageInfo(	const uint32	width			= 0,
					const uint32	height		= 0,
					const Format	format		= NO_FORMAT,
					const Type		type			= NO_TYPE,
					const void*		pixels		= 0 );

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param iimage		image where informations where retrives.
	 */
	ImageInfo( const IImage& iimage );

	//@}



	/**
	 * @name Accessors methods.
	 */
	//@{

	/**
	 * @brief Returns the number of color components.
	 * 
	 * Typical values are 1, 2, 3, 4.
	 * 
	 * @return		number of color components.
	 */
	uint32			components();

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
	uint32&			height()					{ return ( m_height ); }
	
	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */	
	const uint32	height() const			{ return ( m_height ); }

	/**
	 * @brief Returns the format of the pixel data.
	 * 
	 * @return		format of the pixel data.
	 */
	Format&			format()					{ return ( m_format ); }
	
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
	Type&				type()					{ return ( m_type ); }
	
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
	void*&		pixelData()				{ return ( m_pixels ); }

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param width			width of the image.
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * @param pixels			pointer to the image data in memory.
	 */
	void			set(	const uint32	width			= 0,
							const uint32	height		= 0,
							const Format	format		= NO_FORMAT,
							const Type		type			= NO_TYPE,
							const void*		pixels		= 0 );

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param iimage		image where informations where retrives.
	 */
	void 			set( const IImage& iimage );
	//@}



protected:
	/**
	 * @name Image informations.
	 */
	//@{
	uint32		m_width;
	uint32		m_height;

	Format		m_format;
	Type			m_type;
	
	void*			m_pixels;
	
	bool			m_edit;
	//@}
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IMAGEINFO_H
