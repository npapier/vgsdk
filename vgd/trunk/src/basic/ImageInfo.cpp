// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/ImageInfo.hpp"



namespace vgd
{

namespace basic
{



ImageInfo::ImageInfo(	
					const int32		width, const int32 height,
					const Format	format,
					const Type		type,
					const uint8		*pixels )
{
	set( 	width, height,
			format, type,
			pixels );
}



ImageInfo::ImageInfo( const IImage& iimage )
{
	set( iimage );
}



void ImageInfo::set(
					const int32		width,
					const int32		height,
					const Format	format,
					const Type		type,
					const uint8		*pixels	)
{
	m_width			= width;
	m_height			= height;
	m_format			= format;
	m_type			= type;
	m_pixels			= const_cast<uint8*>(pixels);
	m_edit			= false;
}



void ImageInfo::set( const IImage& iimage )
{
	m_width			= iimage.width();
	m_height			= iimage.height();
	m_format			= iimage.format();
	m_type			= iimage.type();
	m_pixels			= const_cast<uint8*>(iimage.pixels());
	m_edit			= false;
}



int32 ImageInfo::components( void )
{ 
	return( computeNumComponents( format() ) );
}



const int32 ImageInfo::components( void ) const
{ 
	return( computeNumComponents( format() ) );
}



} // namespace basic

} // namespace vgd
