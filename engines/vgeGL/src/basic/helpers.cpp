// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/basic/helpers.hpp"

#include <vgDebug/helpers.hpp>



namespace vgeGL
{

namespace basic
{


const GLenum convertMyFormat2GL( const vgd::basic::IImage::Format format )
{
	GLenum glformat;

	using vgd::basic::IImage;

	switch ( format )
	{
		case IImage::NO_FORMAT:
			glformat = 0;
			vgAssertN( false, "Unable to convert IImage::NO_FORMAT to OpenGL format." );
			break;

		case IImage::RGB:
			glformat = GL_RGB;
			break;

		case IImage::RGBA:
			glformat = GL_RGBA;
			break;

		case IImage::BGR:
			glformat = GL_BGR_EXT;
			break;

		case IImage::BGRA:
			glformat = GL_BGRA_EXT;
			break;

		case IImage::LUMINANCE:
		case IImage::COLOR_INDEX:
			glformat = GL_LUMINANCE;
			break;

		case IImage::LUMINANCE_ALPHA:
			glformat = GL_LUMINANCE_ALPHA;
			break;

		default:
			vgAssertN( false, "Unknown or unsupported format." );
			glformat = 0;
	}

	return glformat;
}


const bool convertGLInternalFormat2My( const GLenum internalFormat, vgd::basic::IImage::Format& format, vgd::basic::IImage::Type& type )
{
	using vgd::basic::IImage;

	format	= IImage::NO_FORMAT;
	type	= IImage::NO_TYPE;

	switch ( internalFormat )
	{
		case GL_DEPTH_COMPONENT16:
			vgAssertN( false, "Unsupported OpenGL internal format" );
			return false;
		case GL_DEPTH_COMPONENT24:
			vgAssertN( false, "Unsupported OpenGL internal format" );
			return false;
		case GL_DEPTH_COMPONENT32:
			vgAssertN( false, "Unsupported OpenGL internal format" );
			return false;
		case GL_DEPTH_COMPONENT32F:
			vgAssertN( false, "Unsupported OpenGL internal format" );
			return false;

		case GL_RGB16F:
		case GL_RGB32F:
			format	= IImage::RGB;
			type	= IImage::FLOAT;
			return true;

		case GL_RGBA16F:
		case GL_RGBA32F:
			format	= IImage::RGBA;
			type	= IImage::FLOAT;
			return true;

		case GL_LUMINANCE16F_ARB: // @todo GL_R16 ?
		case GL_LUMINANCE32F_ARB:
			format	= IImage::LUMINANCE;
			type	= IImage::FLOAT;
			return true;

		case GL_LUMINANCE_ALPHA16F_ARB:
		case GL_LUMINANCE_ALPHA32F_ARB:
			format	= IImage::LUMINANCE_ALPHA;
			type	= IImage::FLOAT;
			return true;

		case 1:
		case 2:
		case 3:
		case 4:
		default:
			vgAssertN( false, "Unsupported OpenGL internal format" );
			return false;
	}

	return true;
}


const GLenum convertMyType2GL( const vgd::basic::IImage::Type type )
{
	GLenum gltype;

	using vgd::basic::IImage;

	switch ( type )
	{
		case IImage::NO_TYPE:
			gltype = 0;
			vgAssertN( false, "Unable to convert IImage::NO_TYPE to OpenGL format." );
			break;

		case IImage::UINT8:
			gltype = GL_UNSIGNED_BYTE;
			break;

		case IImage::INT8:
			gltype = GL_BYTE;
			break;

		case IImage::UINT16:
			gltype = GL_UNSIGNED_SHORT;
			break;

		case IImage::INT16:
			gltype = GL_SHORT;
			break;

		case IImage::UINT32:
			gltype = GL_UNSIGNED_INT;
			break;

		case IImage::INT32:
			gltype = GL_INT;
			break;

		case IImage::FLOAT:
			gltype = GL_FLOAT;
			break;

		case IImage::DOUBLE:
		default:
			vgAssertN( false, "Unknown or unsupported type.");
			gltype = 0;
	}

	return gltype;
}



} // namespace basic

} // namespace vgeGL
