// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_IMAGEINFO_H
#define _VGD_BASIC_IMAGEINFO_H

#include "vgd/vgd.hpp"

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
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * @param pixels			pointer to the image data in memory.
	 */
	ImageInfo(	const int32		width			= 0,
					const int32		height		= 0,
					const Format	format		= NO_FORMAT,
					const Type		type			= NO_TYPE,
					const uint8		*pixels		= 0 );

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
	int32				components();

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
	int32&			width()					{ return ( m_width ); }
	
	/**
	 * @brief Returns the width of the image.
	 * 
	 * @return 		width of image.
	 */	
	const int32		width() const			{ return ( m_width ); }

	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */
	int32&			height()					{ return ( m_height ); }
	
	/**
	 * @brief Returns the height of the image.
	 * 
	 * @return		height of image.
	 */	
	const int32		height() const			{ return ( m_height ); }

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
	const Type	type() const				{ return ( m_type ); }
	
	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return a pointer to the image data in memory.
	 */
	const uint8*	pixels( void ) const	{ return ( m_pixels ); }

	/**
	 * @brief Returns a pointer to the image data in memory.
	 * 
	 * @return a pointer to the image data in memory.
	 */
	uint8*			editPixels()			{ assert( !m_edit );		m_edit = true;		return ( m_pixels ); }

	/**
	 * @brief Commit all pixels modifications after calling editPixels().
	 */	
	void				editPixelsDone()		{ assert( m_edit );		m_edit = false;	}
	
	/**
	 * @brief Returns the pixel data pointer.
	 * 
	 * @return A reference on the pixel data pointer.
	 */
	uint8*&			pixelData()				{ return ( m_pixels ); }

	/**
	 * @brief Set all informations about an image.
	 * 
	 * @param width			width of the image.
	 * @param height			height of the image.
	 * @param format			format of the pixel data.
	 * @param type				type of the pixel data.
	 * @param pixels			pointer to the image data in memory.
	 */
	void			set(	const int32		width			= 0,
							const int32		height		= 0,
							const Format	format		= NO_FORMAT,
							const Type		type			= NO_TYPE,
							const uint8		*pixels		= 0 );

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
	int32			m_width;
	int32			m_height;

	Format		m_format;
	Type			m_type;
	
	uint8			*m_pixels;
	
	bool			m_edit;
	//@}
};



} // namespace basic

} // namespace vgd

#endif // #ifndef _VGD_BASIC_IMAGEINFO_H
