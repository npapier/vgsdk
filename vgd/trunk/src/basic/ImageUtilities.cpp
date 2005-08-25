// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/ImageUtilities.hpp"

#include <cstring>
#include <limits>



namespace vgd
{

namespace basic
{



std::pair< float, float > ImageUtilities::computeMinMax( const IImage* pImage )
{
	using vgd::basic::IImage;
	
	assert( pImage->format() == IImage::LUMINANCE );	// FIXME
	assert( pImage->type() == IImage::UINT8 );			// FIXME
	
	int32			sizeOfComponents	= sizeof(uint8);

	std::pair< float, float > retVal( std::numeric_limits<float>::max(), std::numeric_limits<float>::min() );

	// scan image
	const uint8* iPixel = static_cast<const uint8*>(pImage->pixels());
	for(	const uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth();
			iPixel != iEnd;
			iPixel++ )
	{
		uint8 value		= (*iPixel);
		float fValue	= static_cast<float>(value);
		
		if ( fValue < retVal.first )
		{
			retVal.first = value;
		}
		else if ( fValue > retVal.second )
		{
			retVal.second = value;
		}
		// else do nothing
	}

	return ( retVal );
}


		
vgd::Shp< vgd::basic::Image > ImageUtilities::extractSlice(	const IImage*	pImage,
															const SliceType	slice,
															const uint32	position )
{
	using vgd::basic::Image;
	using vgd::basic::IImage;

	assert( pImage->type() == IImage::UINT8 );

	assert( pImage->width() > 0 );
	assert( pImage->height() > 0 );
	assert( pImage->depth() > 0 );

	const uint8*	inputPixel			= static_cast<const uint8*>(pImage->pixels());
	int32			components			= pImage->components();
	int32			sizeOfComponents	= sizeof(uint8) * components;

	vgd::Shp< Image >	pNewImage;
	uint8*				outputPixel;
	Image::Format		outputFormat;
	
	if ( pImage->format() == Image::COLOR_INDEX )
	{
		outputFormat = Image::LUMINANCE;
	}
	else
	{
		outputFormat = pImage->format();
	}
	
	switch ( slice )
	{
		case AXIAL_SLICE:
		{
			pNewImage = vgd::Shp< Image >( new Image(	pImage->components(),
														pImage->width(), pImage->height(), 1,
														outputFormat, pImage->type(),
														0 )
												);

			outputPixel = static_cast<uint8*>(pNewImage->editPixels());
			
			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->depth() );
			
			inputPixel += position * (sizeOfComponents * pImage->width() * pImage->height());
			
			std::memcpy( outputPixel, inputPixel, sizeOfComponents * pImage->height() * pImage->width() );
// non optimized version
//			for(	uint32 j=0, jMax = pImage->height();
//					j < jMax;
//					++j )
//			{
//				for(	uint32 i=0, iMax=pImage->width();
//						i < iMax;
//						++i )
//				{
//					std::memcpy( outputPixel, inputPixel, sizeOfComponents );
//					inputPixel += sizeOfComponents;
//					outputPixel += sizeOfComponents;
//				}
//			}
			
			pNewImage->editPixelsDone();
		}
		break;
		
		
		case FRONTAL_SLICE:
		{
			pNewImage = vgd::Shp< Image >( new Image(	pImage->components(),
														pImage->width(), pImage->depth(), 1,
														outputFormat, pImage->type(),
														0 )
													);

			outputPixel = static_cast<uint8*>(pNewImage->editPixels());

			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->height() );

			inputPixel += position * (sizeOfComponents * pImage->width());

			for(	uint32 j=0, jMax = pImage->depth();
					j < jMax;
					++j )
			{
				std::memcpy( outputPixel, inputPixel, sizeOfComponents * pImage->width() );
				inputPixel	+= pImage->width() * sizeOfComponents;
				outputPixel	+= pImage->width() * sizeOfComponents;
								
// non optimized version
//				for(	uint32 i=0, iMax=pImage->width();
//						i < iMax;
//						++i )
//				{
//					std::memcpy( outputPixel, inputPixel, sizeOfComponents );
//					inputPixel += sizeOfComponents;
//					outputPixel += sizeOfComponents;
//				}

				inputPixel += sizeOfComponents * (	pImage->width() * (pImage->height()-1)		);
			}
			
			pNewImage->editPixelsDone();
		}
		break;


		case SAGITTAL_SLICE:
		{
			pNewImage = vgd::Shp< Image >( new Image(	pImage->components(),
														pImage->depth(), pImage->height(), 1,
														outputFormat, pImage->type(),
														0 )
													);

			outputPixel = static_cast<uint8*>(pNewImage->editPixels());

			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->width() );

			inputPixel += position * sizeOfComponents;

			//
			const int32 stepI = sizeOfComponents * pImage->width() * pImage->height();
			const int32 stepJ = (-stepI * pImage->depth()) + pImage->width()*sizeOfComponents;

			for(	uint32 j=0, jMax = pImage->height();
					j < jMax;
					++j )
			{
				for(	uint32 i=0, iMax=pImage->depth();
						i < iMax;
						++i )
				{
					std::memcpy( outputPixel, inputPixel, sizeOfComponents );
					inputPixel += stepI;
					outputPixel += sizeOfComponents;
				}

				inputPixel += stepJ;
			}
			
			pNewImage->editPixelsDone();
		}
		break;

		default:
			assert( false && "Unknown type of slice." );
	}
	
	return ( pNewImage );
}



void ImageUtilities::setAlpha( vgd::basic::IImage *pImage, const float alpha )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::RGBA) ||
			(pImage->format() == IImage::BGRA) ||
			(pImage->format() == IImage::LUMINANCE_ALPHA) );

	assert( pImage->type() == IImage::UINT8 );
	
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	uint8	ui8Alpha = static_cast< uint8 >( alpha * 255.f );

	switch ( pImage->format() )
	{
		case IImage::RGBA:
		case IImage::BGRA:
		{
			// scan image
			uint8* iPixel = static_cast<uint8*>(pImage->editPixels());
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth()*4;
					iPixel != iEnd;
					iPixel++ )
			{
				iPixel += 3;
				(*iPixel) = ui8Alpha;
			}
			pImage->editPixelsDone();
		}
		break;

		case IImage::LUMINANCE_ALPHA:
		{
			// scan image
			uint8* iPixel = static_cast<uint8*>(pImage->editPixels());
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth()*2;
					iPixel != iEnd;
					iPixel++ )
			{
				++iPixel;
				(*iPixel) = ui8Alpha;
			}
			pImage->editPixelsDone();
		}
		break;
		
		default:
			assert( false && "Internal error" );
	}
}



void ImageUtilities::setAlphaIfNotBlack( vgd::basic::IImage *pImage, const float alpha )
{
	assert(	(pImage->format() == IImage::RGBA) ||
			(pImage->format() == IImage::BGRA) ||
			(pImage->format() == IImage::LUMINANCE_ALPHA) );

	assert( pImage->type() == vgd::basic::IImage::UINT8 );	
		
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	uint8	ui8Alpha;
	ui8Alpha	= static_cast< uint8 >( alpha * 255.f );
	
	switch ( pImage->format() )
	{
		case IImage::RGBA:
		case IImage::BGRA:
		{	
			// scan image
			uint8*		iPixel = static_cast<uint8*>(pImage->editPixels());
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth()*4;
					iPixel != iEnd;
					iPixel++ )
			{
				if (	(iPixel[0] == 0) &&
						(iPixel[1] == 0) &&
						(iPixel[2] == 0) )
				{
					iPixel		+=	3;								
					(*iPixel)	=	0;
				}
				else
				{
					iPixel		+=	3;
					(*iPixel)	=	ui8Alpha;
				}	
			}
			pImage->editPixelsDone();
		}
		break;

		case IImage::LUMINANCE_ALPHA:
		{
			// scan image
			uint8*		iPixel = static_cast<uint8*>(pImage->editPixels());
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth()*2;
					iPixel != iEnd;
					iPixel++ )
			{
				if (iPixel[0] == 0)
				{
					++iPixel;
					(*iPixel)	=	0;
				}
				else
				{
					++iPixel;
					(*iPixel)	=	ui8Alpha;
				}
			}
			pImage->editPixelsDone();
		}
		break;
		
		default:
			assert( false && "Internal error" );
	}		
}



void ImageUtilities::setupPalette(	const int32 minValue, const int32 maxValue,
									const int32 interval1, const int32 interval2,
									const PaletteFunctionType fun1, const float alpha1,
									const PaletteFunctionType fun2, const float alpha2,
									const PaletteFunctionType fun3, const float alpha3,
									uint8 *pPalette )
{
	if ( interval1-1 >= minValue )
	{
		setupPalette(	minValue, maxValue,
						minValue, interval1-1,
						fun1, alpha1,
						pPalette );
	}

	if ( interval2-1 >= interval1 )
	{
		setupPalette(	minValue, maxValue,
						interval1, interval2-1,
						fun2, alpha2,
						pPalette );
	}
	
	if ( maxValue >= interval2 )
	{
		setupPalette(	minValue, maxValue,
						interval2, maxValue,
						fun3, alpha3,
						pPalette );
	}
}



void ImageUtilities::setupPalette(	const int32 minValue, const int32 maxValue,
									const int32 beginInterval, const int32 endInterval,
									const PaletteFunctionType function,
									const float fAlpha,
									uint8 *pPalette )
{
	const float		fMin	= static_cast<float>(minValue);
	const float		fMax	= static_cast<float>(maxValue);
	const float		fBegin	= static_cast<const float>(beginInterval);
	const float		fEnd	= static_cast<const float>(endInterval);

	assert( beginInterval >= minValue && beginInterval <= maxValue );
	assert( endInterval >= minValue && endInterval <= maxValue );
	
	assert( 0.f <= fAlpha && fAlpha <= 1.f );
	assert( pPalette != 0 );

	int32	i		= beginInterval*4;
	int32 iEnd	= endInterval*4;
	uint8	color	= 0;
	uint8 alpha = static_cast<uint8>( fAlpha * 255.f );

	//
	switch ( function )
	{
		case BLACK_TO_WHITE:
		{
			float a = (fMax - fMin ) / (fEnd - fBegin);
			float b = fMin - a * fBegin;				// fMin = a * fBegin + b

			while ( i <= iEnd )
			{
				// y = ax + b
				// FIXME: optme this expression could be simplified and compute by only addition.
				color = static_cast<uint8>( a*(static_cast<float>(i/4)) + b );
				
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
			float a = (fMin - fMax ) / (fEnd - fBegin);
			float b = fMax - a * fBegin;				// fMax = a * fBegin + b

			while ( i <= iEnd )
			{
				// y = ax + b
				// FIXME: optme this expression could be simplified and compute by only addition.
				color = static_cast<uint8>( a*(static_cast<float>(i/4)) + b );
				
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
