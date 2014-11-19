// VGSDK - Copyright (C) 2004, 2007, 2010, 2014, Nicolas Papier, Philippe Sengchanpheng.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#ifndef _VGD_BASIC_IMAGE_HPP
#define _VGD_BASIC_IMAGE_HPP

#ifdef __STBIMAGE__

#include <utility>
#include "vgd/basic/IImage.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Store an Image
 *
 * @sa https://github.com/nothings/stb
 *
 * @todo Adds observation on pixel editor accesses (editPixels()/editPixelsDone()...)
 * @todo use OpenImageIO::geterror(). Uses exception for error handling ?
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
	 * @brief Default constructor
	 * 
	 * @post components()	== 0
	 * @post isEmpty()		== true
	 * @post format()		== NO_FORMAT
	 * @post type()			== NO_TYPE
	 * @post pixels()		== 0
	 * @post editPixels()	== 0
	 * 
	 * @post paletteSize()			== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()			== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 * 
	 * @post voxelSize()		== vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	Image();

	/**
	 * @brief Image constructor from a file
	 * 
	 * @param strFilename		filename of Image to load
	 * 
	 * @post voxelSize()	== vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	Image( const std::string strFilename );

	/**
	 * @brief Image contructor from memory
	 * 
	 * If \c pixels parameter is not 0, then the Image data is copied from memory.
	 * Otherwise the Image is not initialized.
	 * 
	 * @param width		width of the Image
	 * @param height	height of the Image
	 * @param depth		depth of the Image
	 * @param format	format of the pixel data
	 * @param type		type of the pixel data
	 * @param pixels	pointer to the Image data in memory
	 *
	 * @pre	depth = 1
	 *
	 * @post paletteSize()			== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()			== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 */
/*	Image(		const uint32	width, const uint32 height, const uint32 depth,
				const Format	format,
				const Type		type,
				const void*		pixels = 0 );
*/

	/**
	 * @brief Image contructor from an IImage
	 * 
	 * The Image data is copied.
	 * 
	 * @param iimage			source Image to duplicated
	 */
	Image( const IImage& iimage );

	/**
	 * @brief Copy constructor
	 * 
	 * @param src		Image to be copied
	 */
	Image( const Image& src );

	/**
	 * @brief Assignment operator
	 * 
	 * @param src		Image to be copied
	 * @return			copied Image
	 */
	Image&	operator = ( const Image& src );

	/**
	 * @brief Destructor
	 */
	~Image();

	//@}


	/**
	 * @name Creation/destruction Image methods
	 */
	//@{

	/**
	 * @brief Create an Image from a file
	 * 
	 * @param strFilename		filename of Image to load
	 * 
	 * @remarks The type of file is based on the file extension for input operation on file.
	 */
	const bool load( const std::string strFilename );

	// @todo to support crypto
	/**
	 * brief Create an Image from a file in memory.
	 * 
	 * param strFilename		filename of Image to load.
	 *
	 * param buffer			pointer to Image in memory
	 *
	 * param size				size of the buffer
	 * 
	 * remarks All supported format of OpenIL. Main supported format are : bmp, dds, ico, gif, jpg, png, psd, psp, raw, tga, tif.
	 */
	//bool	load( std::string strFilename, const void* buffer, int size );


	/**
	 * @brief Save the current Image to a file
	 *
	 * @param strFilename		filename of Image to load
	 */
	const bool save(const std::string filename) const;


	/**
	 * @brief Create an Image from memory
	 * 
	 * If \c pixels parameter is not 0, then the Image data is copied from memory.
	 * Otherwise the Image is not initialized.
	 * 
	 * @param width		width of the Image
	 * @param height	height of the Image
	 * @param depth		depth of the Image
	 * @param format	format of the pixel data
	 * @param type		type of the pixel data
	 * @param pixels	pointer to the Image data in memory
	 * 
	 * @pre	depth = 1
	 *
	 * @post paletteSize()			== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()			== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 */
/*	const bool	create(	const uint32	width, const uint32 height, const uint32 depth,
						const Format	format, const Type	type,
						const void*		pixels = 0 );
*/	

	/**
	 * @brief Create an Image from an IImage
	 * 
	 * The Image data is copied
	 * 
	 * @param iimage	source Image to duplicated
	 */
	//const bool create( const IImage& iimage );

	/**
	 * @brief Destroy Image
	 */
	void destroy();
	//@}



	/**
	 * @name Actions on Image
	 *
	 * @todo copy_pixels() to changeType()
	 * @todo Generic channel shuffling using ImageBufAlgo::channels() to changeFormat()
	 *
	 * @todo capture_image(webcam) (OpenCV in OpenImageIO)
	 */
	//@{

	/**
	 * brief Convert Image to another type/format of Image.
	 * 
	 * param format		desired format of the converted Image
	 * param type		desired type of the converted Image
	 * 
	 * todo Documentation of what is done exactly by convert (see DevIL).
	 */
	//const bool convertTo( const Format format, const Type type );

	/**
	 * @brief Definition of filter available to resize an Image
	 */
	/*enum Filter
	{
		FILTER_SCALE_NEAREST,	//< lower-quality scaling filters
		FILTER_SCALE_BILINEAR,	//< lower-quality scaling filters

		FILTER_SCALE_BOX,			//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_TRIANGLE,		//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_LANCZOS3,		//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_BSPLINE		//< higher-quality scaling filters and take longer to perform
	};*/

	/**
	 * @brief Scales the Image to the new dimensions specified, shrinking or enlarging the Image, depending on the Image's original dimensions.
	 *
	 * @param size		the new dimension (width, height and depth) of the Image
	 *
	 * return true if rescale has been successful, false if not
	 */
	const bool scale(const vgm::Vec3i size);

	/**
	 * @brief Definition of different flip operations
	 */
/*	enum Flip
	{
		FLIP_X_AXIS,		//< scan-lines exchanged vertically
		FLIP_Y_AXIS			//< columns exchanged horizontally
	};
*/

	/**
	 * @brief Inverts an Image over the specified axis.
	 *
	 * @param flipType		defines the flip axis
	 * @param nbThreads	use nbThreads execution threads to speed up Image operations
	 *
	 * @return true if flip has been successful, false if not
	 */
	//const bool flip( const Flip flipType = FLIP_X_AXIS, const int nbThreads = 1);

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
	 * @return		number of color components
	 */
	const uint32	components() const;

	/**
	 * @brief Returns the width of the Image.
	 * 
	 * @return 		width of Image
	 */
	const uint32	width() const;

	/**
	 * @brief Returns the height of the Image.
	 * 
	 * @return		height of Image
	 */
	const uint32	height() const;

	/**
	 * @brief Returns the depth of the Image.
	 * 
	 * @return		depth of Image
	 */
	const uint32	depth() const;

	/**
	 * @brief Returns the format of the pixel data.
	 * 
	 * @return		format of the pixel data
	 */
	const Format	format() const;

	/**
	 * @brief Returns the type of the pixel data.
	 * 
	 * @return		type of the pixel data
	 */
	const Type		type() const;

	/**
	 * @brief Returns a pointer to the Image data in memory.
	 * 
	 * @return a pointer to the Image data in memory
	 */
	const void*		pixels() const;

	/**
	 * @brief Returns a pointer to the Image data in memory.
	 * 
	 * @return a pointer to the Image data in memory
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
	 *
	 * Not supported
	 */
	//@{

	const uint32	paletteSize() const;

	const Format	paletteFormat() const;

	const Type		paletteType() const;

	const void*		palettePixels() const;
	void*			paletteEditPixels();
	void			paletteEditPixelsDone();
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



	/**
	 * @name Direct access to Image pixel data
	 */
	//@{

	/**
	 * @brief Returns the Image pixel data
	 *
	 */
	//unsigned char * getImageBuf();
	//const unsigned char * getImageBuf() const;

	//@}



private:

	/**
	 * @name OpenImageIO encapsulation methods
	 */
	//@{

	/**
	 * @brief Code of copy constructor
	 */
	void copy( const Image& src );
 
	void resetInformations();
	//@}


	/**
	 * @name Image data and informations
	 */
	//@{
	unsigned char * m_image;		/// @< In-memory representation of a 2D Image

	bool		m_edit;
	//@}

	/**
	 * @brief Voxel size informations.
	 */
	vgm::Vec3f	m_voxelSize;

	int m_width;	///< outputs image width in pixels
	int m_height;	///< outputs image height in pixels
	int m_comp;		///< outputs # of image components in image file
};


} // namespace basic

} // namespace vgd

#else // #ifdef __STBIMAGE__




#include <IL/il.h>
#include <IL/ilu.h>
#include <string>

#include "vgd/basic/IImage.hpp"

namespace vgd { template<class T> struct Shp; }



namespace vgd
{

namespace basic
{



/**
 * @brief Store an image.
 *
 * @remarks This class use the OpenIL (i.e. DevIL image) library inside.
 * @sa http://openil.sourceforge.net/
 *
 * @todo Removes duplicates parameters on constructor and create() methods (see parameters \c format and \c components).
 * @todo Removes in version 0.5 deprecated methods.
 *  
 * @todo Adds observation on pixel editor accesses (editPixels()/editPixelsDone()...)
 * 
 * @todo Uses exception for error handling ?
 * @todo Remove m_* that could be given by OpenIL (not very interesting because of mutex to access OpenIL states)
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
	 * @brief Default constructor
	 * 
	 * @post components()		== 0
	 * @post isEmpty()		== true
	 * @post format()			== NO_FORMAT
	 * @post type()			== NO_TYPE
	 * @post pixels()			== 0
	 * @post editPixels()		== 0
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 * 
	 * @post voxelSize()		== vgm::Vec3f(1.f, 1.f, 1.f)
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
	 * @brief Image constructor from a file in memory.
	 * 
	 * @param strFilename		filename of image to load.
	 * 
	 * @param buffer			pointer to the image in memory.
	 *
	 * @param size				size of the buffer
	 * 
	 * @post voxelSize()	== vgm::Vec3f(1.f, 1.f, 1.f)
	 */
	Image( std::string strFilename, const void*	buffer, int size );

	/**
	 * @brief Image contructor from memory.
	 * 
	 * If \c pixels parameter is not 0, then the image data is copied from memory.
	 * Otherwise the image is not initialized.
	 * 
	 * @param width		width of the image.
	 * @param height		height of the image.
	 * @param depth		depth of the image.
	 * @param format		format of the pixel data.
	 * @param type		type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 */
	Image(		const uint32	width, const uint32 height, const uint32 depth,
				const Format	format,
				const Type		type,
				const void*		pixels = 0 );

	/**
	 * @brief Image contructor from memory.
	 * 
	 * @param components	number of color components.
	 * @param width		width of the image.
	 * @param height		height of the image.
	 * @param depth		depth of the image.
	 * @param format		format of the pixel data.
	 * @param type		type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @pre components == computeNumComponents( format )
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 *
	 * @deprecated Use constructor without components parameters instead
	 */
	Image(		const uint32		components,
				const uint32		width, const uint32 height, const uint32 depth,
				const Format		format,
				const Type			type,
				const void*			pixels );

	/**
	 * @brief Image contructor
	 * 
	 * @param components	number of color components.
	 * @param width		width of the image.
	 * @param height		height of the image.
	 * @param depth		depth of the image.
	 * @param format		format of the pixel data.
	 * @param type		type of the pixel data.
	 * 
	 * @pre components == computeNumComponents( format ) 
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 *
	 * @deprecated Use constructor without components parameters instead 
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
	 * @remarks All supported format of OpenIL. Main supported format are : bmp, dds, ico, gif, jpg, png, psd, psp, raw, tga, tif.
	 */
	bool	load( std::string strFilename );

	/**
	 * @brief Create an image from a file in memory.
	 * 
	 * @param strFilename		filename of image to load.
	 *
	 * @param buffer			pointer to image in memory
	 *
	 * @param size				size of the buffer
	 * 
	 * @remarks All supported format of OpenIL. Main supported format are : bmp, dds, ico, gif, jpg, png, psd, psp, raw, tga, tif.
	 */
	bool	load( std::string strFilename, const void* buffer, int size );

	/**
	 * @brief Create an image from memory.
	 * 
	 * If \c pixels parameter is not 0, then the image data is copied from memory.
	 * Otherwise the image is not initialized.
	 * 
	 * @param width		width of the image.
	 * @param height		height of the image.
	 * @param depth		depth of the image.
	 * @param format		format of the pixel data.
	 * @param type		type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 */
	bool	create(	const uint32	width, const uint32 height, const uint32 depth,
					const Format	format, const Type	type,
					const void*		pixels = 0 );

	/**
	 * @brief Create an image from memory.
	 * 
	 * Create a copy of the specified image.
	 * 
	 * @param components	number of color components.
	 * @param width		width of the image.
	 * @param height		height of the image.
	 * @param depth		depth of the image.
	 * @param format		format of the pixel data.
	 * @param type		type of the pixel data.
	 * @param pixels		pointer to the image data in memory.
	 * 
	 * @pre components == computeNumComponents( format )
	 *
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 *
	 * @deprecated Use create() without components parameters instead  
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
	 * @param width		width of the image.
	 * @param height		height of the image.
	 * @param depth		depth of the image.
	 * @param format		format of the pixel data.
	 * @param type		type of the pixel data.
	 * 
	 * @pre components == computeNumComponents( format )
	 * 
	 * @post paletteSize()		== 0
	 * @post paletteFormat()		== NO_FORMAT
	 * @post paletteType()		== NO_TYPE
	 * @post palettePixels()		== 0
	 * @post paletteEditPixels()	== 0
	 *
	 * @deprecated Use create() without components parameters instead  
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
	 */
	bool create( const IImage& iimage );

	/**
	 * @brief Save the current image to a file.
	 *
	 * @remarks All supported format of OpenIL. Main supported format are : bmp, dds, jpg, png, raw, tga, tif.
	 */
	bool save( const std::string filename ) const;

	/**
	 * @brief Saves the current image into a buffer that will be allocated during the call.
	 *
	 * @param	type		a string containing the target file type like "jpg", "png", ...
	 * @param	buffer		will receive the saved data or left empty on error
	 *
	 * @return	true on success, false otherwise
	 */
	bool save( const std::string & type, std::vector< char > & buffer ) const;
	
	/**
	 * @brief Destroy image.
	 */
	void destroy();
	//@}



	/**
	 * @name Actions on image
	 */
	//@{

	/**
	 * @brief Convert image to another type/format of image.
	 * 
	 * @param format		desired format of the converted image
	 * @param type		desired type of the converted image
	 * 
	 * @todo Documentation of what is done exactly by convert (see DevIL).
	 */
	const bool convertTo( const Format format, const Type type );

	/**
	 * @brief Definition of filter available to scale image.
	 */
	enum Filter
	{
		FILTER_SCALE_NEAREST	= ILU_NEAREST,	//< lower-quality scaling filters
		FILTER_SCALE_LINEAR		= ILU_LINEAR,	//< lower-quality scaling filters
		FILTER_SCALE_BILINEAR	= ILU_BILINEAR,	//< lower-quality scaling filters

		FILTER_SCALE_BOX		= ILU_SCALE_BOX,		//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_MITCHELL	= ILU_SCALE_MITCHELL,	//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_BELL		= ILU_SCALE_BELL,		//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_BSPLINE	= ILU_SCALE_BSPLINE,	//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_LANCZOS3	= ILU_SCALE_LANCZOS3,	//< higher-quality scaling filters and take longer to perform
		FILTER_SCALE_TRIANGLE	= ILU_SCALE_TRIANGLE,	//< higher-quality scaling filters and take longer to perform
	};

	/**
	 * @brief Scales the image to the new dimensions specified, shrinking or enlarging the image, depending on the image's original dimensions.
	 *
	 * @param size		the new dimension (width, height and depth)  of the image
	 * @param filter		the filter to use during scaling
	 *
	 * @return true if rescale has been successful, false if not
	 */
	const bool scale( const vgm::Vec3i size, const Filter filter = FILTER_SCALE_BOX );

	/**
	 * @brief Inverts an image over the x axis.
	 *
	 * @return true if flip has been successful, false if not
	 */
	const bool flip();

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
	 * @remarks	If palette is not defined, must return 0.
	 */
	const uint32	paletteSize() const;

	/**
	 * @brief Returns the format of the palette.
	 * 
	 * @return		format of the palette.
	 * 
	 * @remarks	If palette is not defined, must return NO_FORMAT.
	 */
	const Format	paletteFormat() const;

	/**
	 * @brief Returns the type of the palette.
	 * 
	 * @return		type of the palette.
	 * 
	 * @remarks	If image is not defined, must return NO_TYPE.
	 */
	const Type		paletteType() const;
	
	/**
	 * @brief Returns a pointer to the palette data in memory.
	 * 
	 * @return		a pointer to the palette data in memory.
	 * 
	 * @remarks	If palette is not defined, must return 0.
	 */
	const void*		palettePixels() const;

	/**
	 * @brief Returns a pointer to the palette in memory.
	 * 
	 * @return		a pointer to the palette in memory.
	 * 
	 * @remarks	If image is not defined, must return 0.
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
	 * @param size		size of palette in bytes.
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



	/**
	 * @name OpenIL accessors
	 *
	 * @remarks OpenIL is not multi-thread safe. Be careful...
	 */
	//@{
	
	/**
	 * @brief Returns the OpenIL name of image
	 *
	 * @return the name of the image
	 */
	ILuint getName();
	
	//@}



private:

	/**
	 * @name DevIL encapsulation methods
	 */
	//@{

	/**
	 * @brief Code of copy constructor.
	 */
	void	copy( const Image& src );
 
	/**
	 * @brief Must be called before using DevIL methods on an image.
	 */
	bool	bind() const;

	bool	reportILError() const;

	Format	convertILFormat2My( ILenum format		) const;
	Format	convertILPalFormat2My( ILenum format	) const;

	ILenum	convertMyFormat2IL( Format format		) const;
	ILenum	convertMyFormat2ILPal( Format format	) const;
	
	Type	convertILType2My( ILenum type	) const;
	ILenum	convertMyType2IL( Type myType	) const;
	
	void	resetInformations();
	void	updateInformations();
	//@}


	/**
	 * @name Image data and informations
	 */
	//@{

	/**
	 * @brief id for image library, 0 otherwise (no image specified or not yet loaded).
	 */
	ILuint		m_iluintImgID;

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
};

} // namespace basic

} // namespace vgd

#endif // #ifdef __STBIMAGE__

#endif // #ifndef _VGD_BASIC_IMAGE_HPP
