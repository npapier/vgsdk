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
					const uint32		width, const uint32 height, const uint32 depth,
					const Format		format,
					const Type			type,
					const void*			pixels,
					const vgm::Vec3f	voxelSize
					 )
{
	set( 	width, height, depth,
			format, type,
			pixels,
			voxelSize );
}



ImageInfo::ImageInfo( const IImage& iimage )
{
	set( iimage );
}



void ImageInfo::set(
					const uint32		width,
					const uint32		height,
					const uint32		depth,					
					const Format		format,
					const Type			type,
					const void*			pixels,
					const vgm::Vec3f	voxelSize	)
{
	m_width			= width;
	m_height			= height;
	m_depth			= depth;
	m_format			= format;
	m_type			= type;
	m_pixels			= const_cast<void*>(pixels);
	m_voxelSize		= voxelSize;
	m_edit			= false;
}



void ImageInfo::set( const IImage& iimage )
{
	m_width			= iimage.width();
	m_height			= iimage.height();
	m_depth			= iimage.depth();	
	m_format			= iimage.format();
	m_type			= iimage.type();
	m_pixels			= const_cast<void*>(iimage.pixels());
	m_voxelSize		= iimage.voxelSize();
	m_edit			= false;
}



uint32 ImageInfo::components()
{ 
	return( computeNumComponents( format() ) );
}



const uint32 ImageInfo::components() const
{ 
	return( computeNumComponents( format() ) );
}



void* ImageInfo::editPixels()
{
	assert( !m_edit );
	
	m_edit = true;
	
	return ( m_pixels ); 
}



void ImageInfo::editPixelsDone()
{
	assert( m_edit );
	
	m_edit = false;
}



vgm::Vec3f& ImageInfo::voxelSize()
{
	return ( m_voxelSize );
}



const vgm::Vec3f ImageInfo::voxelSize() const
{
	return ( m_voxelSize );
}



} // namespace basic

} // namespace vgd
