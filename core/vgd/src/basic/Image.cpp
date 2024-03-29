// VGSDK - Copyright (C) 2004, 2007, 2009, 2010, 2011, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/Image.hpp"

#ifdef __STBIMAGE__

#include "vgd/basic/Image.hpp"
#include "vgd/basic/FilenameExtractor.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include <stb/stb_image_resize.h>
#undef STB_IMAGE_IMPLEMENTATION
#undef STB_IMAGE_RESIZE_IMPLEMENTATION
#undef STB_IMAGE_WRITE_IMPLEMENTATION
#include <sbf/operations.hpp>
#include <vgDebug/helpers.hpp>

#include <cassert>

namespace vgd
{

namespace basic
{


Image::Image() 
:	m_image	(NULL	),
	m_width	(0		),
	m_height(0		),
	m_comp	(0		)
{
	resetInformations();
}



Image::Image( const std::string strFilename )
:	m_image	(NULL	),
	m_width	(0		),
	m_height(0		),
	m_comp	(0		)
{
	resetInformations();

	load( strFilename );
}



Image::Image(	const uint32	width, const uint32 height, const uint32 depth,
				const Format	format,
				const Type		type,
				const void*		pixels )
:	m_image	(NULL	),
	m_width	(0		),
	m_height(0		),
	m_comp	(0		)
{
	resetInformations();

	create(	width, height, depth,
			format, type,
			pixels );
}


Image::Image( const IImage& Image )
{
	resetInformations();

	const bool retVal = create( Image );
	vgAssertN( retVal, "Error during Image construction/copying." );
}



Image::Image( const Image& src )
{
	copy(src);
}



Image& Image::operator = ( const Image& src )
{
	if ( this != &src )
	{
		destroy();
		copy( src );
	}

	return ( *this );
}



Image::~Image()
{
	destroy();
}



const bool Image::load( const std::string strFilename )
{
	destroy();

	// Create a new Image name.
	m_image = stbi_load(strFilename.c_str(), &m_width, &m_height, &m_comp, 0);

	if (m_image != NULL)
	{
		vgLogDebug("Image::load: %s (%i x %i) loaded.", strFilename.c_str(), width(), height() );
		return true;
	}
	else
	{
		vgLogDebug("Image::load: Unable to read Image %s.", strFilename.c_str() );
		destroy();

		return false;
	}
}


bool Image::load( std::string strFilename, const void* buffer, int size )
{

#ifdef _DEBUG
	vgLogDebug("Image::load: Start reading image %s.", strFilename.c_str() );
#endif

	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( strFilename.c_str() );
	std::string						extension = extractor.getLowerCaseExtension();


	m_image = stbi_load_from_memory((unsigned char *)buffer, size, &m_width, &m_height, &m_comp, STBI_default);

	if ( m_image == NULL )
	{
		destroy();
		return false;
	}
	else
	{
#ifdef _DEBUG
		vgLogDebug("Image::load: Finish reading image %s (%i x %i).",
			strFilename.c_str(), width(), height() );
#endif
		return true;
	}
}


const bool Image::save( const std::string strFilename ) const
{
	using vgd::basic::FilenameExtractor;
	FilenameExtractor extractor(strFilename);
	std::string extension = extractor.getLowerCaseExtension();

	bool retVal = false;

	if(extension == ".png")	retVal = stbi_write_png(strFilename.c_str(), m_width, m_height, m_comp, m_image, 0);
	if(extension == ".bmp")	retVal = stbi_write_bmp(strFilename.c_str(), m_width, m_height, m_comp, m_image);
	if(extension == ".tga")	retVal = stbi_write_tga(strFilename.c_str(), m_width, m_height, m_comp, m_image);


	if ( retVal )
	{
		vgLogDebug( "Image::save: %s", strFilename.c_str() );
		return true;
	}
	else
	{
		vgLogDebug( "Image::save: Unable to write Image %s.", strFilename.c_str() );
		return false;
	}
}


bool Image::save( const std::string & type, std::vector< char > & buffer ) const
{
	if( type == "png" )
	{
		int outputLen;
		unsigned char * output = stbi_write_png_to_mem(m_image, 0, m_width, m_height, m_comp, &outputLen);

		if( output )
		{
			buffer.resize(outputLen);
			memcpy(&buffer[0], output, outputLen);
			free( output );
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		vgLogDebug("Unable to save an image to a buffer. %s is not a supported target type.", type.c_str());
		buffer.clear();
		return false;
	}
}


const bool Image::create(	const uint32	width, const uint32 height, const uint32 depth,
							const Format	format,	const Type	type,
							const void*		pixels )
{
	vgAssert( depth == 1 );

	// Create a new Image name
	destroy();

	m_comp = computeNumComponents(format);
	m_width = width;
	m_height = height;
	m_voxelSize.setValue( 1.f, 1.f, 1.f );

	// Copy pixels
	if ( pixels )
	{
		// Assign memory for pixel data
		m_image = (unsigned char*) malloc(computeMaximumOffset());
		memcpy(m_image, pixels, computeMaximumOffset());
	}

	return true;
}



const bool Image::create( const IImage& Image )
{
	destroy();

	const bool bRetVal = create(	Image.width(), Image.height(), Image.depth(),
									Image.format(), Image.type(),
									Image.pixels() );

	if ( bRetVal && (Image.format() != COLOR_INDEX) )
	{
		voxelSize() = Image.voxelSize();
		return true;
	}
	else
	{
		vgAssertN( Image.format() != COLOR_INDEX, "COLOR_INDEX format not supported" );
		/*if (	(Image.format() == COLOR_INDEX) &&
				(Image.paletteFormat() != NO_FORMAT) )
		{
			setPalette(	Image.palettePixels(),
						Image.paletteSize(),
						Image.paletteFormat() );
		}*/
		return false;
	}
}



void Image::destroy()
{
	if(m_image != NULL)
		stbi_image_free(m_image);

	m_image = NULL;
	resetInformations();
}


const bool Image::scale( const vgm::Vec3i size, const Filter filter )
{
	vgAssertN(!isEmpty(), "No image set, can't scale.");

	unsigned char * outputData = (unsigned char*) malloc(sizeof(unsigned char) * size[0] * size[1] * m_comp);
	bool retVal = stbir_resize_uint8(	m_image, m_width, m_height,  0,
										outputData, size[0], size[1], 0, m_comp);

	if (retVal && outputData)
	{
		stbi_image_free(m_image);
		m_image = outputData;
		
		m_width = size[0];
		m_height = size[1];
	}
	else
	{
		stbi_image_free(outputData);
	}
	
	return retVal;
}


/*
const bool Image::flip( const Flip flipType, const int nbThreads )
{
	OpenImageIO::ImageBuf destination( "Image.flip.destination", m_image.spec() );

	if ( flipType == FLIP_X_AXIS )
	{
		// Flip
		const bool retVal = OpenImageIO::ImageBufAlgo::flip( destination, m_image, OpenImageIO::ROI::All(), nbThreads ); 

		// Swap images
		if (retVal)		m_image.swap( destination );

		return retVal;
	}
	else
	{
		vgAssert( flipType == FLIP_Y_AXIS );

		// Flip
		const bool retVal = OpenImageIO::ImageBufAlgo::flop( destination, m_image, OpenImageIO::ROI::All(), nbThreads ); 

		// Swap images
		if (retVal)		m_image.swap( destination );

		return retVal;
	}
}
*/


const uint32 Image::components() const
{
	return m_comp;
}



const uint32 Image::width() const
{
	return m_width;
}



const uint32 Image::height() const
{
	return m_height;
}



const uint32 Image::depth() const
{
	return 1; // ????? only depth supported
}




const Image::Format Image::format() const
{
	Format format;
	
	switch (m_comp)
	{
	case 0:
		format = NO_FORMAT;
		break;
	
	case 1:
		format = LUMINANCE;
		break;

	case 2:
		format = LUMINANCE_ALPHA;
		break;
	
	case 3:
		format = RGB;
		break;
	
	case 4:
		format = RGBA;
		break;
	
	default:
		assert(false && "Not a supported number of components.");
		format = NO_FORMAT;
	}
	
	return format;
}



const Image::Type Image::type() const
{
	return INT8; // ????? only type supported
}



const void* Image::pixels() const
{
	return static_cast<void *>(m_image);
}



void* Image::editPixels()
{
	vgAssertN( !m_edit, "Image already edited." );

	m_edit = true;

	return static_cast<void *>(m_image);
}



void Image::editPixelsDone()
{
	vgAssertN( m_edit, "Image not currently edited" );

	m_edit = false;
}



// PALETTE
const uint32 Image::paletteSize() const
{
	return 0;
}



const Image::Format Image::paletteFormat() const
{
	return NO_FORMAT;
}



const Image::Type Image::paletteType() const
{
	return NO_TYPE;
}



const void* Image::palettePixels() const
{
	return 0;
}



void* Image::paletteEditPixels()
{
	vgAssertN( !m_edit, "Image already edited." );

	m_edit = true;

	return 0;
}



void Image::paletteEditPixelsDone()
{
	vgAssertN( m_edit, "Image not currently edited" );

	m_edit = false;
}



vgm::Vec3f& Image::voxelSize()
{
	return m_voxelSize;
}



const vgm::Vec3f Image::voxelSize() const
{
	return m_voxelSize;
}



const bool Image::isVoxelSizeSupported() const
{
	return true;
}



void Image::copy( const Image& src )
{
	vgAssertN( m_image == NULL, "Pixel data pointer isn't null, memory leak" );
	unsigned char * srcChar = (unsigned char *)src.pixels();
	m_image = (unsigned char *)malloc(computeMaximumOffset());
	memcpy(m_image, srcChar, computeMaximumOffset());

	m_width = src.width();
	m_height = src.height();
	m_comp = src.components();

	m_edit			= false;
	m_voxelSize		= src.m_voxelSize;
}



void Image::resetInformations()
{
	m_edit			= false;
	m_voxelSize		= vgm::Vec3f( 1.f, 1.f, 1.f );
}



} // namespace basic

} // namespace vgd




#else // #ifdef __STBIMAGE__




#ifndef __EMSCRIPTEN__
#include <boost/thread.hpp>
#else
	#error "Try tu use Image version OpenIL with emscripten"
#endif

#include <vgd/basic/FilenameExtractor.hpp>
#include <vgDebug/helpers.hpp>

#include "vgd/Shp.hpp"



namespace vgd
{

namespace basic
{

namespace
{
	boost::recursive_mutex globalOpenILMutex; //< a mutex to protect accesses to OpenIL library (OpenIL is not reentrant).

/**
 * @brief Global startup and shutdown of OpenIL library
 */
struct OpenILStartupManagement
{
	/**
	 * @brief Default constructor that calls initializeOpenIL()
	 */
	OpenILStartupManagement()
	{
		initializeOpenIL();
	}
	
	/**
	 * @brief Default destructor that calls shutdownOpenIL()
	 */
	~OpenILStartupManagement()
	{
		shutdownOpenIL();
	}

	/**
	 * @brief This method must be called prior to any use of OpenIL.
	 */
	static void initializeOpenIL()
	{
		vgLogDebug("Image::OpenIL library startup.");

		// Do some initialization.
		boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

		ilInit();
	}

	/**
	 * brief This method must be called at exit.
	 */
	static void shutdownOpenIL()
	{
		vgLogDebug("Image::OpenIL library shutdown.");

		ilShutDown();
	}
};

	static OpenILStartupManagement openILStartupManagement; ///< Global startup and shutdown of OpenIL library 
}



Image::Image()
:	m_iluintImgID(0)
{
	resetInformations();
}



Image::Image( std::string strFilename )
:	m_iluintImgID(0)
{
	resetInformations();

	load( strFilename );
}



Image::Image( std::string strFilename, const void* buffer, int size )
:	m_iluintImgID(0)
{
	resetInformations();

	load( strFilename, buffer, size );
}



Image::Image(	const uint32	width, const uint32 height, const uint32 depth,
				const Format	format,
				const Type		type,
				const void*		pixels )
:	m_iluintImgID(0)
{
	resetInformations();

	create(	computeNumComponents( format ),
			width, height, depth,
			format, type,
			pixels );
}



Image::Image(	const uint32		components,
				const uint32		width, const uint32 height, const uint32 depth,
				const Format		format,
				const Type			type,
				const void*			pixels ) 
:	m_iluintImgID(0)
{
	vgAssert( components == computeNumComponents( format ) );

	resetInformations();

	create(	width, height, depth,
			format, type,
			pixels );
}



Image::Image(	const uint32	components,
				const uint32	width, const uint32 height, const uint32 depth,
				const Format	format,
				const Type		type 	)
:	m_iluintImgID(0)
{
	vgAssert( components == computeNumComponents( format ) );
		
	resetInformations();
		
	create(	width, height, depth,
			format, type );
}



Image::Image( const IImage& image )
:	m_iluintImgID(0)
{
	resetInformations();

	const bool retVal = create(	image );
	vgAssertN( retVal, "Error during image construction/copying." );
}



Image::Image( const Image& src )
:	m_iluintImgID(0)
{
	copy(src);
}



Image& Image::operator = ( const Image& src )
{
	if ( this != &src )
	{
		destroy();
		copy( src );
	}

	return ( *this );
}



Image::~Image()
{
	destroy();
}



void Image::destroy()
{
	if ( m_iluintImgID != 0 )
	{
		boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

		ilDeleteImages(1, &m_iluintImgID);
		m_iluintImgID	= 0;
		resetInformations();
	}
}



bool Image::load( std::string strFilename )
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

#ifdef _DEBUG
	vgLogDebug("Image::load: Start reading image %s.", strFilename.c_str() );
#endif
	// Loads the image specified by strFilename into the ImgId image.
	if ( ilLoadImage( const_cast<char*>( strFilename.c_str() ) ) == IL_FALSE )
	{
		reportILError();
		
		destroy();

		return false;
	}
	else
	{
		updateInformations();

#ifdef _DEBUG
		vgLogDebug(	"Image::load: Finish reading image %s (%i x %i).",
						strFilename.c_str(), 
						width(), height() );
#endif

		return true;
	}
}



bool Image::load( std::string strFilename, const void* buffer, int size )
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

#ifdef _DEBUG
	vgLogDebug("Image::load: Start reading image %s.", strFilename.c_str() );
#endif

	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( strFilename.c_str() );
	std::string						extension = extractor.getLowerCaseExtension();

	ILenum type = IL_TYPE_UNKNOWN;

	// Loads the image specified by strFilename into the ImgId image.
	if ( ilLoadL( type, buffer, size ) == IL_FALSE )
	{
		reportILError();
		
		destroy();

		return false;
	}
	else
	{
		// Purge IL errors, as ilLoadL might log errors even on success (see http://sourceforge.net/p/openil/bugs/114/)
		while ( ilGetError() != IL_NO_ERROR );
		updateInformations();

#ifdef _DEBUG
		vgLogDebug("Image::load: Finish reading image %s (%i x %i).",
					strFilename.c_str(), width(), height() );
#endif

		return true;
	}
}



bool Image::create(	const uint32	width, const uint32 height, const uint32 depth,
					const Format	format,	const Type	type,
					const void*		pixels )
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

	//
	const void *cpixels = reinterpret_cast<const void*>(pixels);

	ilTexImage(
		width, height, depth,
		static_cast<ILubyte>(computeNumComponents(format)),
		convertMyFormat2IL(format),
		convertMyType2IL(type),
		const_cast<void*>( cpixels )
		);

	if ( reportILError() )
	{
		destroy();
		return false;
	}
	else
	{
		m_voxelSize.setValue( 1.f, 1.f, 1.f );

		updateInformations();
		return true;
	}
}



bool Image::create(	const uint32		components, 
					const uint32		width, const uint32 height, const uint32 depth,
					const Format		format,
					const Type			type,
					const void*			pixels )
{
	vgAssert( components == computeNumComponents( format ) );

	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

	//
	const void *cpixels = reinterpret_cast<const void*>(pixels);

	ilTexImage(
		width, height, depth,
		static_cast<ILubyte>(components),
		convertMyFormat2IL(format),
		convertMyType2IL(type),
		const_cast<void*>( cpixels )
		);

	if ( reportILError() )
	{
		destroy();
		return false;
	}
	else
	{
		m_voxelSize.setValue( 1.f, 1.f, 1.f );

		updateInformations();
		return true;
	}
}



bool Image::create(	const uint32		components, 
					const uint32		width, const uint32 height, const uint32 depth,
					const Format		format,
					const Type			type )
{
	vgAssert( components == computeNumComponents( format ) );

	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

	//
	
	ilTexImage(
		width, height, depth,
		static_cast<ILubyte>(components),
		convertMyFormat2IL(format),
		convertMyType2IL(type),
		0
		);

	if ( reportILError() )
	{
		destroy();
		return false;
	}
	else
	{
		m_voxelSize.setValue( 1.f, 1.f, 1.f );
		
		updateInformations();
		return true;
	}
}



bool Image::create( const IImage& image )
{
	bool bRetVal;

	bRetVal = create(	image.width(), image.height(), image.depth(),
						image.format(), image.type(),
						image.pixels() );

	if ( !bRetVal )	return false;

	if (	(image.format() == COLOR_INDEX) &&
			(image.paletteFormat() != NO_FORMAT) )
	{
		setPalette(	image.palettePixels(),
					image.paletteSize(),
					image.paletteFormat() );
	}

	voxelSize() = image.voxelSize();

	vgAssert( bRetVal );

	return bRetVal;
}



bool Image::save( const std::string filename ) const
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	bind();
	
	if ( IL_FALSE == ilSaveImage( const_cast< char* >(filename.c_str()) ) )
	{
		reportILError();
		
		return false;
	}
	else
	{
		return true;
	}
}



bool Image::save( const std::string & type, std::vector< char > & buffer ) const
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	bind();

	// Determines the target type.
	ILenum	ilType;
	if( type == "png" )	ilType = IL_PNG;
	else				ilType = 0;

	if( ilType == 0 )
	{
		vgLogDebug("Unable to save an image to a buffer. %s is not a supported target type.", type.c_str());
		buffer.clear();
		return false;
	}

	// Determines the needed buffer size,
	// allocates the buffer and
	// saves the image.
	//
	// WARNING! This causes openIL to save the image twice.
	// One time for dtermining the buffer size, and a second time 
	// to do the effective image saving. But there is no other
	// way to get the needed buffer size.
	const ILint size = ilSaveL( ilType, 0, 0 );
	buffer.resize( size, 0 );
	ilSaveL( ilType, buffer.data(), buffer.size() );

	return true;
}



const bool Image::convertTo( const Format format, const Type type )
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	bind();
	
	ilConvertImage( convertMyFormat2IL(format), convertMyType2IL(type) );
	
	updateInformations();

	return ( !reportILError() );
}



const bool Image::scale( const vgm::Vec3i size, const Filter filter )
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	bind();

	iluImageParameter( ILU_FILTER, filter );
	iluScale( size[0], size[1], size[2] );

	updateInformations();

	return ( !reportILError() );
}




const bool Image::flip()
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	bind();

	iluFlipImage();

	updateInformations();

	return ( !reportILError() );
}



const uint32 Image::components() const
{
	const uint32 components = computeNumComponents( m_format );

	return components;
}



const uint32 Image::width() const
{
	return m_width;
	//return ilGetInteger( IL_IMAGE_WIDTH );
}



const uint32 Image::height() const
{
	return m_height;
	//return ilGetInteger( IL_IMAGE_HEIGHT );
}



const uint32 Image::depth() const
{
	return m_depth;
	//return ilGetInteger( IL_IMAGE_DEPTH );
}



const Image::Format Image::format() const
{
	return m_format;
}



const Image::Type Image::type() const
{
	return m_type;
}



const void* Image::pixels() const
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	bind();

	return ( ilGetData() );
}



void* Image::editPixels()
{
	vgAssertN( !m_edit, "Image already edited." );

	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );	

	bind();
	m_edit = true;

	return ( ilGetData() );
}



void Image::editPixelsDone()
{
	vgAssertN( m_edit, "Image not currently edited" );

	m_edit = false;
}



const uint32 Image::paletteSize() const
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	bind();

	uint32 size = ilGetInteger( IL_PALETTE_NUM_COLS );
	
	return size;
}



const Image::Format Image::paletteFormat() const
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	bind();
	
	uint32 palFormat = ilGetInteger( IL_PALETTE_TYPE );
	
	return ( convertILPalFormat2My( palFormat ) );
}



const Image::Type Image::paletteType() const
{
	return UINT8;
}



const void* Image::palettePixels() const
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	bind();

	return ( ilGetPalette() );
}



void* Image::paletteEditPixels()
{
	vgAssertN( !m_edit, "Image already edited." );

	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	bind();
	m_edit = true;

	return ( ilGetPalette() );
}



void Image::paletteEditPixelsDone()
{
	vgAssertN( m_edit, "Image not currently edited" );

	m_edit = false;
}



void Image::setPalette( const void *palette, uint32 size, const Format format )
{
	vgAssertN( !m_edit, "Image already edited." );

	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	bind();

	const ILenum ilFormat = convertMyFormat2ILPal( format );
	
	// FIXME: should use ilSetSharedPal, but missing in include file !
	ilRegisterPal(	const_cast<ILubyte*>( static_cast<const ILubyte*>(palette)),
					size, ilFormat );

	reportILError();

	updateInformations();
}



vgd::Shp< Image > Image::getPaletteImage() const
{
	vgd::Shp< Image > image( new Image(	1,
										paletteSize(), 1, 1, 
										paletteFormat(), paletteType(),
										palettePixels() ) );
										
	return image;
}



vgm::Vec3f& Image::voxelSize()
{
	return m_voxelSize;
}



const vgm::Vec3f Image::voxelSize() const
{
	return m_voxelSize;
}



const bool Image::isVoxelSizeSupported() const
{
	return true;
}



ILuint Image::getName()
{
	return m_iluintImgID;
}



void Image::copy( const Image& src )
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );
	
	src.bind();

	vgAssertN( m_iluintImgID == 0, "Try to copy on a non empty image" );

	m_iluintImgID	= ilCloneCurImage();
	updateInformations();

	m_edit			= false;
	m_voxelSize		= src.m_voxelSize;
	
	reportILError();
}



/**
 * @remarks Method not protected by the mutex
 */
bool Image::bind() const
{
	ilBindImage(m_iluintImgID);
	
	return ( !reportILError() );
}



/**
 * @remarks Method not protected by the mutex
 */
bool Image::reportILError() const
{
	ILenum error = ilGetError();

	if ( error == IL_NO_ERROR )
	{
		//vgDebug::get().logTrace("Image: No error" );
		return false;
	}
	else
	{
		switch ( error )
		{
			case IL_COULD_NOT_OPEN_FILE:
				vgLogDebug("Image: Could not open file" );
				//TRACE("IL_COULD_NOT_OPEN_FILE : ");
				break;

			case IL_ILLEGAL_OPERATION:
				vgLogDebug("Image: Illegal operation" );
				//TRACE("IL_ILLEGAL_OPERATION : ");
				break;

			case IL_INVALID_EXTENSION:
				vgLogDebug("Image: Invalid extension" );
				//TRACE("IL_INVALID_EXTENSION : ");
				break;

			case IL_INVALID_PARAM:
				vgLogDebug("Image: Invalid param" );
				//TRACE("IL_INVALID_PARAM : ");
				break;
			
			default:
				vgLogDebug("Image: Unknown error" );
		}

		return true;
	}
}



Image::Format Image::convertILFormat2My( ILenum format ) const
{
	Format f;

	switch ( format )
	{
		case IL_RGB:
			f = RGB;
			break;

		case IL_RGBA:
			f = RGBA;
			break;

		case IL_BGR:
			f = BGR;
			break;

		case IL_BGRA:
			f = BGRA;
			break;

		case IL_LUMINANCE:
			f = LUMINANCE;
			break;

		case IL_LUMINANCE_ALPHA:
			f = LUMINANCE_ALPHA;
			break;
		
		case IL_COLOR_INDEX:
			f = COLOR_INDEX;
			break;

		default:
			vgAssertN(false, "Unsupported format");
			f = NO_FORMAT;
	}

	return f;
}



Image::Format Image::convertILPalFormat2My( ILenum format ) const
{
	Format retVal;
	
	switch ( format )
	{
		case IL_PAL_RGB24:
			retVal = RGB;
			break;

		case IL_PAL_RGBA32:
			retVal = RGBA;
			break;

		case IL_PAL_BGR24:
			retVal = BGR;
			break;
			
		case IL_PAL_BGRA32:
			retVal = BGRA;
			break;

		case IL_PAL_NONE:
			retVal = NO_FORMAT;
			break;

		case IL_PAL_RGB32:
		case IL_PAL_BGR32:
		default:
			vgAssertN(false, "Unsupported palette format");
			retVal = NO_FORMAT;
	}

	return retVal;
}


	
ILenum Image::convertMyFormat2IL( Format format ) const
{
	ILenum ilformat;
	
	switch ( format )
	{
		case RGB:
			ilformat = IL_RGB;
			break;

		case RGBA:
			ilformat = IL_RGBA;
			break;

		case BGR:
			ilformat = IL_BGR;
			break;

		case BGRA:
			ilformat = IL_BGRA;
			break;

		case LUMINANCE:
			ilformat = IL_LUMINANCE;
			break;
			
		case LUMINANCE_ALPHA:
			ilformat = IL_LUMINANCE_ALPHA;
			break;
			
		case COLOR_INDEX:
			ilformat = IL_COLOR_INDEX;
			break;

		default:
			vgAssertN(false, "Unsupported format");
			ilformat = IL_RGB;
	}

	return ilformat;
}



ILenum Image::convertMyFormat2ILPal( Format format	) const
{
	ILenum ilformat;
	
	switch ( format )
	{
		case RGB:
			ilformat = IL_PAL_RGB24;
			break;

		case RGBA:
			ilformat = IL_PAL_RGBA32;
			break;

		case BGR:
			ilformat = IL_PAL_BGR24;
			break;

		case BGRA:
			ilformat = IL_PAL_BGRA32;
			break;

		case LUMINANCE:
		case LUMINANCE_ALPHA:
		case COLOR_INDEX:
		default:
			vgAssertN(false, "Unsupported format");
			ilformat = IL_PAL_RGBA32;
	}
	
	return ilformat;
}



Image::Type Image::convertILType2My( ILenum myType ) const
{
	Type type;
	
	switch ( myType )
	{
		case IL_UNSIGNED_BYTE:
			type = UINT8;
			break;

		case IL_BYTE:
			type = INT8;
			break;

		case IL_UNSIGNED_SHORT:
			type = UINT16;
			break;

		case IL_SHORT:
			type = INT16;
			break;
		
		case IL_UNSIGNED_INT:
			type = UINT32;
			break;
		
		case IL_INT:
			type = INT32;
			break;
					
		case IL_FLOAT:
			type = FLOAT;
			break;

		case IL_DOUBLE:
			type = DOUBLE;
			break;

		default:
			vgAssertN(false, "Unsupported type");
			type = NO_TYPE;
	}
	
	return type;
}



ILenum Image::convertMyType2IL( Type myType ) const
{
	ILenum type;
	
	switch ( myType )
	{
		case UINT8:
			type = IL_UNSIGNED_BYTE;
			break;

		case INT8:
			type = IL_BYTE;
			break;

		case UINT16:
			type = IL_UNSIGNED_SHORT;
			break;

		case INT16:
			type = IL_SHORT;
			break;
		
		case UINT32:
			type = IL_UNSIGNED_INT;
			break;
		
		case INT32:
			type = IL_INT;
			break;
					
		case FLOAT:
			type = IL_FLOAT;
			break;

		case DOUBLE:
			type = IL_DOUBLE;
			break;

		case NO_TYPE:		
		default:
			vgAssertN(false, "Unsupported type");
			type = IL_UNSIGNED_BYTE;
	}
	
	return type;
}



void Image::resetInformations()
{
	m_width			= 0;
	m_height		= 0;
	m_depth			= 0;
	m_format		= NO_FORMAT;
	m_type			= NO_TYPE;

	m_edit			= false;

	m_voxelSize		= vgm::Vec3f( 1.f, 1.f, 1.f );
}



void Image::updateInformations()
{
	boost::recursive_mutex::scoped_lock slock( globalOpenILMutex );

	bind();

	m_width			= ilGetInteger( IL_IMAGE_WIDTH );
	m_height		= ilGetInteger( IL_IMAGE_HEIGHT );
	m_depth			= ilGetInteger( IL_IMAGE_DEPTH );
	m_format		= convertILFormat2My( ilGetInteger( IL_IMAGE_FORMAT ) );
	m_type			= convertILType2My( ilGetInteger( IL_IMAGE_TYPE ) );

	// m_edit		nothing to do

	// m_voxelSize	nothing to do

	reportILError();
}



} // namespace basic

} // namespace vgd

#endif // #ifdef __STBIMAGE__
