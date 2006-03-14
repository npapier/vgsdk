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



const float IImage::getPixel1( const vgm::Vec3i position ) const
{
	assert( components() == 1 );

	const uint32 offset = computeOffset( position );
	
	return getPixel1(offset);
}



const float IImage::getPixel1( const uint32 offset ) const
{
	assert( components() == 1 );

	float retVal;
	
	switch ( type() )
	{
		case UINT8:
		{
			const uint8 *pixel = static_cast<const uint8*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}

		case INT8:
		{
			const int8 *pixel = static_cast<const int8*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}

		case UINT16:
		{
			const uint16 *pixel = static_cast<const uint16*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}

		case INT16:
		{
			const int16 *pixel = static_cast<const int16*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}

		case UINT32:
		{
			const uint32 *pixel = static_cast<const uint32*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}
	
		case INT32:
		{
			const int32 *pixel = static_cast<const int32*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}

		case FLOAT:
		{
			const float *pixel = static_cast<const float*>(pixels());
			retVal = pixel[offset];
			break;
		}

		case DOUBLE:
		{
			const double *pixel = static_cast<const double*>(pixels());
			retVal = static_cast<float>(pixel[offset]);
			break;
		}

		case NO_TYPE:
		//case BOOL:
		default:
			assert( false && "Unknown type" );
			retVal = std::numeric_limits<float>::max();
	}
	
	return retVal;
}



void IImage::setPixel1( const vgm::Vec3i position, const float color )
{
	assert( components() == 1 );

	const uint32 offset = computeOffset( position );
	
	setPixel1(offset, color);
}



void IImage::setPixel1( const uint32 offset, const float color )
{
	switch ( type() )
	{
		case UINT8:
		{
			uint8 *pixel = static_cast<uint8*>(editPixels());
			pixel[offset] = static_cast<uint8>(color);
			editPixelsDone();
			break;
		}

		case INT8:
		{
			int8 *pixel = static_cast<int8*>(editPixels());
			pixel[offset] = static_cast<int8>(color);
			editPixelsDone();
			break;
		}

		case UINT16:
		{
			uint16 *pixel = static_cast<uint16*>(editPixels());
			pixel[offset] = static_cast<uint16>(color);
			editPixelsDone();
			break;
		}

		case INT16:
		{
			int16 *pixel = static_cast<int16*>(editPixels());
			pixel[offset] = static_cast<int16>(color);
			editPixelsDone();
			break;
		}

		case UINT32:
		{
			uint32 *pixel = static_cast<uint32*>(editPixels());
			pixel[offset] = static_cast<uint32>(color);
			editPixelsDone();
			break;
		}
		
		case INT32:
		{
			int32 *pixel = static_cast<int32*>(editPixels());
			pixel[offset] = static_cast<int32>(color);
			editPixelsDone();
			break;
		}

		case FLOAT:
		{
			float *pixel = static_cast<float*>(editPixels());
			pixel[offset] = static_cast<float>(color);
			editPixelsDone();
			break;
		}

		case DOUBLE:
		{
			double *pixel = static_cast<double*>(editPixels());
			pixel[offset] = static_cast<double>(color);
			editPixelsDone();
			break;
		}

		case NO_TYPE:
		//case BOOL:
		default:
			assert( false && "Unknown type" );
	}
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



const uint32 IImage::computeOffset( const uint32 x, const uint32 y, const uint32 z ) const
{
	assert( x < width() );
	assert( y < height() );
	assert( z < depth() );

	const uint32 numPixels	= x + width() * ( y + height() * z );
	
	return numPixels*sizeOfPixel();
}



const uint32 IImage::computeOffset( const vgm::Vec3i position ) const
{
	assert( position[0] < width() );
	assert( position[1] < height() );
	assert( position[2] < depth() );

	return computeOffset( position[0], position[1], position[2] );
}



const uint32 IImage::computeMaximumOffset() const
{
	uint32 sizeofPixel = sizeOfPixel();

	return width()*height()*depth()*sizeofPixel;
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
	
	assert( 0 <= retVal[0] );
	assert( retVal[0] < width() );

	assert( 0 <= retVal[1] );
	assert( retVal[1] < height() );
	
	assert( 0 <= retVal[2] );
	assert( retVal[2] < depth() );
	
	return retVal;
}



} // namespace basic

} // namespace vgd
