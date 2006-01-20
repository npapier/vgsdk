// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/IImage.hpp"

#include <limits>



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



const uint32 IImage::sizeOfPixel() const
{
	const uint32 sizeOfType = computeSizeOfType(type());
	
	return components() * sizeOfType;
}



const uint32 IImage::computeNumberOfPixels() const
{
	return width()*height()*depth();
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



const uint32 IImage::computeSizeOfType( const Type type )
{
	uint32 retVal;
	
	switch ( type )
	{
		case UINT8:
			retVal = sizeof(uint8);
			break;

		case INT8:
			retVal = sizeof(int8);
			break;

		case UINT16:
			retVal = sizeof(uint16);
			break;

		case INT16:
			retVal = sizeof(int16);
			break;

		case UINT32:
			retVal = sizeof(uint32);
			break;

		case INT32:
			retVal = sizeof(int32);
			break;

		case FLOAT:
			retVal = sizeof(float);
			break;

		case DOUBLE:
			retVal = sizeof(double);
			break;

		case NO_TYPE:
		//case BOOL:
		default:
			assert( false && "Unknown type" );
			retVal = 0;
	}
	
	return retVal;
}



const std::pair< double, double > IImage::getRange( const Type type )
{
	std::pair< double, double > retVal;

	switch ( type )
	{
		case UINT8:
			retVal.first	= std::numeric_limits<uint8>::min();
			retVal.second	= std::numeric_limits<uint8>::max();
			break;

		case INT8:
			retVal.first	= std::numeric_limits<int8>::min();
			retVal.second	= std::numeric_limits<int8>::max();
			break;

		case UINT16:
			retVal.first	= std::numeric_limits<uint16>::min();
			retVal.second	= std::numeric_limits<uint16>::max();
			break;

		case INT16:
			retVal.first	= std::numeric_limits<int16>::min();
			retVal.second	= std::numeric_limits<int16>::max();
			break;

		case UINT32:
			retVal.first	= std::numeric_limits<uint32>::min();
			retVal.second	= std::numeric_limits<uint32>::max();
			break;

		case INT32:
			retVal.first	= std::numeric_limits<int32>::min();
			retVal.second	= std::numeric_limits<int32>::max();
			break;

		case FLOAT:
			retVal.first	= std::numeric_limits<float>::min();
			retVal.second	= std::numeric_limits<float>::max();
			break;

		case DOUBLE:
			retVal.first	= std::numeric_limits<double>::min();
			retVal.second	= std::numeric_limits<double>::max();
			break;

		case NO_TYPE:
		//case BOOL:
		default:
			assert( false && "Unknown type" );
			retVal.first = retVal.second = 0.f;
	}
	
	return retVal;
}



const uint32 IImage::computeOffset( const uint32 x, const uint32 y, const uint32 z )
{
	const uint32 offset	= x + width() * ( y + height() * z );
	
	return offset*sizeOfPixel();
}



const uint32 IImage::computeOffset( const vgm::Vec3i position )
{
	return computeOffset( position[0], position[1], position[2] );
}



const uint32 IImage::computeMaximumOffset() const
{
	return width()*height()*depth()*sizeOfPixel();
}



const vgm::Vec3i IImage::computeCoordinates( const uint32 offset ) const
{
	vgm::Vec3i retVal;
	
	const uint32	sizeOfPixel( sizeOfPixel() );
	
	const int32		axialSliceSize( width()*height()*sizeOfPixel );
	
	retVal[2]			= offset / axialSliceSize;
	
	const int32 remain	= offset - retVal[2]*axialSliceSize;
	retVal[1]			= remain / (width()*sizeOfPixel);
	
	retVal[0]			= remain - retVal[1]*(width()*sizeOfPixel);

	return retVal;
}



} // namespace basic

} // namespace vgd
