// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/Image.hpp"

#include <vgDebug/Global.hpp>



namespace vgd
{

namespace basic
{



Image::Image() :
	m_iluintImgID(0)
{
	if ( m_firstInstance )
	{
		// This is the first instance of this class.

		// Do some initialization.
		ilInit();
		
		// Don't do the same for any others instances.
		m_firstInstance = false;
	}

	resetInformations();
}



Image::Image( std::string strFilename ) :
	m_iluintImgID(0)
{
	if ( m_firstInstance )
	{
		// This is the first instance of this class.

		// Do some initialization.
		ilInit();
		
		// Don't do the same for any others instances.
		m_firstInstance = false;
	}
	
	resetInformations();
	
	load( strFilename );
}



Image::Image(	const uint32	components,
					const uint32	width, const uint32 height, const uint32 depth,
					const Format	format,
					const Type		type,
					const void*		pixels ) :
	m_iluintImgID(0)
{
	if ( m_firstInstance )
	{
		// This is the first instance of this class.

		// Do some initialization.
		ilInit();
		
		// Don't do the same for any others instances.
		m_firstInstance = false;
	}
	
	resetInformations();
		
	create(	components,
				width, height, depth,
				format, type,
				pixels );
}



Image::Image(	const uint32	components,
					const uint32	width, const uint32 height, const uint32 depth,
					const Format	format,
					const Type		type ) :
	m_iluintImgID(0)
{
	if ( m_firstInstance )
	{
		// This is the first instance of this class.

		// Do some initialization.
		ilInit();
		
		// Don't do the same for any others instances.
		m_firstInstance = false;
	}
	
	resetInformations();
		
	create(	components,
				width, height, depth,
				format, type 
				);
}



Image::Image( const IImage& image ) :
	m_iluintImgID(0)
{
	if ( m_firstInstance )
	{
		// This is the first instance of this class.

		// Do some initialization.
		ilInit();
		
		// Don't do the same for any others instances.
		m_firstInstance = false;
	}
	
	resetInformations();
		
	create(	image.components(),
				image.width(), image.height(), image.depth(),
				image.format(), image.type(),
				image.pixels() );
}



Image::Image( const Image& src )
{
	copy(src);
	updateInformations();
}



Image& Image::operator = ( const Image& src )
{
	if ( this != &src )
	{
		destroy();
		copy( src );
		updateInformations();
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
		ilDeleteImages(1, &m_iluintImgID);
		m_iluintImgID	= 0;
		resetInformations();
	}
}



bool Image::load( std::string strFilename )
{
	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

	vgDebug::get().logDebug("Image::load: Start reading image %s.", strFilename.c_str() );
	
	// Loads the image specified by strFilename into the ImgId image.
	if ( ilLoadImage( const_cast<char*>( strFilename.c_str() ) ) == IL_FALSE )
	{
		reportILError();
		
		destroy();

		return ( false );
	}
	else
	{
		if ( IL_COLOR_INDEX == ilGetInteger( IL_IMAGE_FORMAT ) )
		{
			vgDebug::get().logDebug("Image::load: Convert from COLOR INDEX mode to RGBA image %s.", strFilename.c_str() );
			convertTo( RGBA, convertILType2My(ilGetInteger(IL_IMAGE_TYPE)) );
		}
		
		updateInformations();
		
		vgDebug::get().logDebug("Image::load: Finish reading image %s (%i x %i).",
			strFilename.c_str(), width(), height() );		

		return ( true );
	}
}



bool Image::create(	const uint32	components, 
							const uint32	width, const uint32 height, const uint32 depth,
							const Format	format,
							const Type		type,
							const void*		pixels )
{
	destroy();

	// Create a new image name.
	ilGenImages(1, &m_iluintImgID);

	// Bind this image name.
	bind();

	//
	const ILvoid *cpixels = reinterpret_cast<const ILvoid*>(pixels);

	ilTexImage(
		width, height, depth,
		static_cast<ILubyte>(components),
		convertMyFormat2IL(format),
		convertMyType2IL(type),
		const_cast<ILvoid*>( cpixels )
		);

	if ( reportILError() )
	{
		destroy();
		return ( false );
	}
	else
	{
		updateInformations();
		return ( true );
	}
}



bool Image::create(	const uint32	components, 
							const uint32	width, const uint32 height, const uint32 depth,
							const Format	format,
							const Type		type )
{
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
		return ( false );
	}
	else
	{
		updateInformations();
		return ( true );
	}
}



bool Image::create( const IImage& image )
{
	bool bRetVal;
	
	bRetVal = create(	
					image.components(),
					image.width(), image.height(), image.depth(),
					image.format(), image.type(),
					image.pixels() );
					
	return ( bRetVal );
}



bool Image::save( const std::string filename ) const
{
	bind();
	
	if ( IL_FALSE == ilSaveImage( const_cast< char* >(filename.c_str()) ) )
	{
		reportILError();
		
		return ( false );
	}
	else
	{
		return ( true );
	}
}



bool Image::convertTo( const Format format, const Type type )
{
	bind();
	
	ilConvertImage( convertMyFormat2IL(format), convertMyType2IL(type) );
	
	updateInformations();

	return ( !reportILError() );
}



const uint32 Image::components() const
{
	return ( m_components );
}



const uint32 Image::width() const
{
	return ( m_width );
}



const uint32 Image::height() const
{
	return ( m_height );
}



const uint32 Image::depth() const
{
	return ( m_depth );
}



const Image::Format Image::format() const
{
	return ( m_format );
}



const Image::Type Image::type() const
{
	return ( m_type  );
}



const void* Image::pixels() const
{
	bind();

	return ( ilGetData() );
}



void* Image::editPixels()
{
	assert( !m_edit && "Image already edited." );

	bind();
	m_edit = true;

	return ( ilGetData() );
}



void Image::editPixelsDone()
{
	assert( m_edit && "Image not currently edited" );

	m_edit = false;
}



void Image::copy( const Image& src )
{
	src.bind();

	m_iluintImgID = ilCloneCurImage();
	
	reportILError();
}



bool Image::bind() const
{
	ilBindImage(m_iluintImgID);
	
	return ( !reportILError() );
}



bool Image::reportILError() const
{
	ILenum error = ilGetError();

	if ( error == IL_NO_ERROR )
	{
		//vgDebug::get().logTrace("Image: No error" );
		return ( false );
	}
	else
	{
		switch ( error )
		{
			case IL_COULD_NOT_OPEN_FILE:
			vgDebug::get().logDebug("Image: Could not open file" );
			//TRACE("IL_COULD_NOT_OPEN_FILE : ");
			break;

			case IL_ILLEGAL_OPERATION:
			vgDebug::get().logDebug("Image: Illegal operation" );
			//TRACE("IL_ILLEGAL_OPERATION : ");
			break;

			case IL_INVALID_EXTENSION:
			vgDebug::get().logDebug("Image: Invalid extension" );
			//TRACE("IL_INVALID_EXTENSION : ");
			break;

			case IL_INVALID_PARAM:
			vgDebug::get().logDebug("Image: Invalid param" );
			//TRACE("IL_INVALID_PARAM : ");
			break;
			
			default:
			vgDebug::get().logDebug("Image: Unknown error" );
		}
		
		return ( true );
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

		default:
			assert(false && "Unsupported format");
			f = NO_FORMAT;
	}

	return ( f );
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

		default:
			assert(false && "Unsupported format");
			ilformat = IL_RGB;
	}

	return ( ilformat );
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
			assert(false && "Unsupported type");
			type = NO_TYPE;
	}
	
	return ( type );
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
			assert(false && "Unsupported type");
			type = IL_UNSIGNED_BYTE;
	}
	
	return ( type );
}



void Image::resetInformations()
{
	m_components	= m_width = m_height = m_depth = 0;
	m_format			= NO_FORMAT;
	m_type			= NO_TYPE;
	m_edit			= false;
}



void Image::updateInformations()
{
	bind();

	m_components	= ilGetInteger( IL_IMAGE_BYTES_PER_PIXEL );
	m_width			= ilGetInteger( IL_IMAGE_WIDTH );	
	m_height			= ilGetInteger( IL_IMAGE_HEIGHT );
	m_depth			= ilGetInteger( IL_IMAGE_DEPTH );	
	m_format			= convertILFormat2My( ilGetInteger( IL_IMAGE_FORMAT ) );
	m_type			= convertILType2My( ilGetInteger( IL_IMAGE_TYPE ) );
	
	reportILError();
}



bool Image::m_firstInstance	= true;



} // namespace basic
	
} // namespace vgd
