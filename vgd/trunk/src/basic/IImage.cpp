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
				(height() == 0)
				);
}



const uint32 IImage::computeNumComponents( const Format format ) const
{
	uint32 components;
	
	switch ( format )
	{
		case NO_FORMAT:
			components = 0;
			break;
			
		case LUMINANCE:
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



} // namespace basic

} // namespace vgd
