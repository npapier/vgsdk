// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#include "vgd/basic/ImageUtilities.hpp"

#include <cstring>
#include <limits>

#include "vgm/Utilities.hpp"



namespace vgd
{

namespace basic
{



const MinMax ImageUtilities::computeMinMax( const IImage* pImage )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::LUMINANCE_ALPHA)	||
			(pImage->format() == IImage::LUMINANCE)			||
			(pImage->format() == IImage::COLOR_INDEX) );

	switch( pImage->type() )
	{
	case Image::UINT8:	return doComputeMinMax<  uint8 >( pImage );
	case Image::INT8:	return doComputeMinMax<   int8 >( pImage );
	case Image::UINT16: return doComputeMinMax< uint16 >( pImage );
	case Image::INT16:	return doComputeMinMax<  int16 >( pImage );
	case Image::UINT32:	return doComputeMinMax< uint32 >( pImage );
	case Image::INT32:	return doComputeMinMax<  int32 >( pImage );
	case Image::FLOAT:	return doComputeMinMax<  float >( pImage );
	case Image::DOUBLE:	return doComputeMinMax< double >( pImage );
	default:			assert( false && "Unsupported image type." );
	}
}



const MinMax ImageUtilities::computeMinMax( const vgd::Shp< IImage > image ) 
{ 
	return ( computeMinMax(image.get()) );
}



template<>
const float ImageUtilities::convertAlpha< float >( const float alpha )
{
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	return alpha;
}



template<>
const double ImageUtilities::convertAlpha< double >( const float alpha )
{
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	return alpha;
}



/**
 * @todo OPTME For 16 bits images containing only values inside (0, 255), don't interpolate values.
 */
vgd::Shp< Image > ImageUtilities::createImage(	const vgd::Shp< IImage> srcImage, 
												const IImage::Type dstType,
												MinMax& minMax )
{
	// srcImage
	assert( srcImage->format() == IImage::LUMINANCE );
	assert( srcImage->components() == 1 );
	assert(	(srcImage->type() == IImage::UINT8) ||
			(srcImage->type() == IImage::INT16)	);

	// dstImage
	assert( dstType == IImage::UINT8 );

	// Process min-max
	if ( minMax.isValid() == false )
	{
		minMax = ImageUtilities::computeMinMax( srcImage );
	}
	
	assert( minMax.isValid() );

	// Creates the new image
	Shp< Image > dstImage( new Image(	srcImage->components(),
										srcImage->width(), srcImage->height(), srcImage->depth(),
										srcImage->format(), dstType ) );
										
	if ( srcImage->isVoxelSizeSupported() )
	{
		dstImage->voxelSize() = srcImage->voxelSize();
	}
							
	typedef uint8 DstPixelType;
	DstPixelType *iDstPixel = static_cast<DstPixelType*>(dstImage->editPixels());

	// y = a*x + b
	const DstPixelType newMin = std::numeric_limits<DstPixelType>::min();
	const DstPixelType newMax = std::numeric_limits<DstPixelType>::max();

	///@todo Uses vgm::Utilities::linearInterpolation().
	const float a = static_cast<float>( newMax - newMin ) / minMax.getDelta();
	const float b = newMin - a*minMax.getMin();

	// Scans the source image and assigns to the destination image each converted pixel...
	switch ( srcImage->type() )
	{
		case IImage::UINT8:
		{
			typedef uint8 SrcPixelType;
			const SrcPixelType *iSrcPixel = static_cast<const SrcPixelType*>(srcImage->pixels());
			
			// @todo FIXME IImage::copyPixels()
			std::memcpy( iDstPixel, iSrcPixel, srcImage->computeMaximumOffset() );
		}
		break;

		case IImage::INT16:
		{
			typedef int16 SrcPixelType;

			const SrcPixelType *iSrcPixel = static_cast<const SrcPixelType*>(srcImage->pixels());

			for(	const SrcPixelType *iEndSrcPixel = iSrcPixel + srcImage->computeNumberOfPixels();
					iSrcPixel != iEndSrcPixel;
					++iSrcPixel )
			{
				const SrcPixelType	color		= *iSrcPixel;
				const float			fNewColor	= vgm::clamp(	a*static_cast<float>(color) + b, 
																static_cast< const float >( newMin ),
																static_cast< const float >( newMax )	);
				const DstPixelType	newColor	= static_cast<const DstPixelType>( fNewColor );
				
				// @todo FIXME IImage::adaptPixels()
				// @todo FIXME opt lookup table
				(*iDstPixel) = newColor;
				
				++iDstPixel;
			}
		}
		break;
		
		default:
			dstImage.reset();
	}
	
	if ( dstImage != 0 )
	{
		dstImage->editPixelsDone();
	}
	
	return dstImage;
}



vgd::Shp< vgd::basic::Image > ImageUtilities::extractSlice(	const IImage*	pImage,
															const SliceType	slice,
															const uint32	position )
{
	using vgd::basic::Image;

	assert( pImage->width() > 0 );
	assert( pImage->height() > 0 );
	assert( pImage->depth() > 0 );
	
	switch( pImage->type() )
	{
	case Image::UINT8:	return doExtractSlice<  uint8 >( pImage, slice, position );
	case Image::INT8:	return doExtractSlice<   int8 >( pImage, slice, position );
	case Image::UINT16: return doExtractSlice< uint16 >( pImage, slice, position );
	case Image::INT16:	return doExtractSlice<  int16 >( pImage, slice, position );
	case Image::UINT32:	return doExtractSlice< uint32 >( pImage, slice, position );
	case Image::INT32:	return doExtractSlice<  int32 >( pImage, slice, position );
	case Image::FLOAT:	return doExtractSlice<  float >( pImage, slice, position );
	case Image::DOUBLE:	return doExtractSlice< double >( pImage, slice, position );
	default:			assert( false && "Unsupported image type." );
	}
}



void ImageUtilities::setAlphaFromLuminance( vgd::basic::IImage *pImage, const float scale )
{
	using vgd::basic::IImage;
	
	assert(	pImage->format() == IImage::LUMINANCE_ALPHA );

	
	assert( pImage->type() == IImage::UINT8 );
	switch ( pImage->format() )
	{
		case IImage::LUMINANCE_ALPHA:
		{
			// scan image
			uint8* iPixel = static_cast<uint8*>(pImage->editPixels());
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth()*2;
					iPixel != iEnd;
					iPixel++ )
			{
				const uint8 luminance = (*iPixel);
				const float fScaledLuminance = static_cast< float >( luminance ) * scale;
				const float fClampedScaledLuminance = vgm::clamp( fScaledLuminance, 0.f, 255.f );
			
				++iPixel;
				(*iPixel) = static_cast< uint8 >( fClampedScaledLuminance );
			}
			pImage->editPixelsDone();
		}
		break;
		
		default:
			assert( false && "Internal error" );
	}
}



void ImageUtilities::setAlpha( vgd::basic::IImage *pImage, const float alpha )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::RGBA) ||
			(pImage->format() == IImage::BGRA) ||
			(pImage->format() == IImage::LUMINANCE_ALPHA) );

	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	switch( pImage->type() )
	{
	case Image::UINT8:	doSetAlpha<  uint8 >( pImage, alpha ); break;
	case Image::INT8:	doSetAlpha<   int8 >( pImage, alpha ); break;
	case Image::UINT16: doSetAlpha< uint16 >( pImage, alpha ); break; 
	case Image::INT16:	doSetAlpha<  int16 >( pImage, alpha ); break;
	case Image::UINT32:	doSetAlpha< uint32 >( pImage, alpha ); break;
	case Image::INT32:	doSetAlpha<  int32 >( pImage, alpha ); break;
	case Image::FLOAT:	doSetAlpha<  float >( pImage, alpha ); break;
	case Image::DOUBLE:	doSetAlpha< double >( pImage, alpha ); break;
	default:			assert( false && "Unsupported image type." );
	}
}



void ImageUtilities::setAlphaIfNotBlack( vgd::basic::IImage *pImage, const float alpha )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::RGBA) ||
			(pImage->format() == IImage::BGRA) ||
			(pImage->format() == IImage::LUMINANCE_ALPHA) );

	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	switch( pImage->type() )
	{
	case Image::UINT8:	doSetAlphaIfNotBlack< uint8  >( pImage, alpha ); break;
	case Image::INT8:	doSetAlphaIfNotBlack< int8   >( pImage, alpha ); break;
	case Image::UINT16: doSetAlphaIfNotBlack< uint16 >( pImage, alpha ); break; 
	case Image::INT16:	doSetAlphaIfNotBlack< int16  >( pImage, alpha ); break;
	case Image::UINT32:	doSetAlphaIfNotBlack< uint32 >( pImage, alpha ); break;
	case Image::INT32:	doSetAlphaIfNotBlack< int32  >( pImage, alpha ); break;
	case Image::FLOAT:	doSetAlphaIfNotBlack< float  >( pImage, alpha ); break;
	case Image::DOUBLE:	doSetAlphaIfNotBlack< double >( pImage, alpha ); break;
	default:			assert( false && "Unsupported image type." );
	}
}



void ImageUtilities::setupPalette(	const int32 minValue, const int32 maxValue,
									const int32 interval1, const int32 interval2,
									const PaletteFunctionType fun1, const float alpha1,
									const PaletteFunctionType fun2, const float alpha2,
									const PaletteFunctionType fun3, const float alpha3,
									uint8 *pPalette )
{
	if ( interval1 > minValue )
	{
		setupPalette(	minValue, maxValue,
						minValue, interval1,
						fun1, alpha1,
						pPalette );
	}
	
	if ( interval2 < maxValue )
	{
		setupPalette(	minValue, maxValue,
						interval2, maxValue,
						fun3, alpha3,
						pPalette );
	}
	
	setupPalette(	minValue, maxValue,
					interval1, interval2,
					fun2, alpha2,
					pPalette );
}



void ImageUtilities::setupPalette(	const int32 minValue, const int32 maxValue,
									const int32 beginInterval, const int32 endInterval,
									const PaletteFunctionType function,
									const float fAlpha,
									uint8 *pPalette )
{
	const float		fMin	= static_cast<float>(minValue);
	const float		fMax	= static_cast<float>(maxValue);
	const float		fBegin	= static_cast<float>(beginInterval);
	const float		fEnd	= static_cast<float>(endInterval);

	assert( beginInterval >= minValue && beginInterval <= maxValue );
	assert( endInterval >= minValue && endInterval <= maxValue );
	
	assert( 0.f <= fAlpha && fAlpha <= 1.f );
	assert( pPalette != 0 );

	int32	i		= beginInterval*4;
	int32	iEnd	= endInterval*4;
	uint8	color	= 0;
	uint8	alpha	= static_cast<uint8>( fAlpha * 255.f );
	
	PaletteFunctionType newFunction;
	
	if ( fBegin == fEnd )
	{
		if ( function == BLACK_TO_WHITE )
		{
			newFunction = WHITE;
		}
		else if ( function == WHITE_TO_BLACK )
		{
			newFunction = BLACK;
		}
		else
		{
			newFunction = function;
		}
	}
	else
	{
		newFunction = function;
	}
	
	//
	switch ( newFunction )
	{
		case BLACK_TO_WHITE:
		{
			assert( fBegin != fEnd );

			float a, b;
			vgm::Utilities::linearInterpolation( fBegin, fMin, fEnd, fMax, a, b );
			
			while ( i <= iEnd )
			{
				// FIXME: optme this expression could be simplified and compute by only addition.
				color = static_cast<uint8>( vgm::Utilities::linearInterpolation( a, b, static_cast<float>(i/4) ) );
				
				pPalette[i] = color;
				++i;
				
				pPalette[i] = color;
				++i;
				
				pPalette[i] = color;
				++i;
				
				pPalette[i] = alpha;
				++i;
			}

			break;
		}
		

		case WHITE_TO_BLACK:
		{
			assert( fBegin != fEnd );
			
			float a, b;
			vgm::Utilities::linearInterpolation( fBegin, fMax, fEnd, fMin, a, b );

			while ( i <= iEnd )
			{
				// FIXME: optme this expression could be simplified and compute by only addition.
				color = static_cast<uint8>( vgm::Utilities::linearInterpolation( a, b, static_cast<float>(i/4) ) );
				
				pPalette[i] = color;
				++i;
				
				pPalette[i] = color;
				++i;
				
				pPalette[i] = color;
				++i;
				
				pPalette[i] = alpha;
				++i;
			}

			break;
		}
	

		case BLACK:
		{
			while ( i <= iEnd )
			{
				pPalette[i] = 0;
				++i;
				
				pPalette[i] = 0;
				++i;
				
				pPalette[i] = 0;
				++i;
				
				pPalette[i] = alpha;
				++i;
			}
			
			break;
		}
		

		case WHITE:
		{
			while ( i <= iEnd )
			{
				pPalette[i] = 255;
				++i;
				
				pPalette[i] = 255;
				++i;
				
				pPalette[i] = 255;
				++i;
				
				pPalette[i] = alpha;
				++i;
			}
			
			break;
		}
		

		default:
		assert( false && "Unexpected palette function." );
	}
}



} // namespace basic

} // namespace vgd
