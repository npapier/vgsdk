// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/IImage.hpp"



namespace vgd
{

namespace basic
{



IImage::~IImage()
{
}



const bool IImage::isEmpty() const
{
	return (	(width() == 0) &&
				(height() == 0) &&
				(depth() == 0)
				);
}



const uint32 IImage::computeNumComponents( const Format format )
{
	uint32 components;
	
	switch ( format )
	{
		case NO_FORMAT:
			components = 0;
			break;
			
		case LUMINANCE:
		case COLOR_INDEX:
			components = 1;
			break;		
		
		case LUMINANCE_ALPHA:
			components = 2;
			break;

		case RGB:
		case BGR:
			components = 3;
			break;		
		
		case RGBA:
		case BGRA:
			components = 4;
			break;
			
		default:
			assert( false && "Unknown format." );
			components = 0;
	}
	
	return ( components );
}



const uint32 IImage::computeOffset( const uint32 x, const uint32 y, const uint32 z )
{
	const uint32	offset	= x + width() * ( y + height() * z );

	return offset;
}



const uint32 IImage::computeOffset( const vgm::Vec3i position )
{
	return computeOffset( position[0], position[1], position[2] );
}



} // namespace basic

} // namespace vgd
