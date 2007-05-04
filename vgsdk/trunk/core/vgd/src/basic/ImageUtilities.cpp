// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

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
	
	assert(	(pImage->format() == IImage::LUMINANCE) ||
			(pImage->format() == IImage::COLOR_INDEX) );

	MinMax minMax;
	
	switch ( pImage->type() )
	{
		case IImage::UINT8:
		{
			// scan image
			const uint8 *iPixel( static_cast<const uint8*>(pImage->pixels()) );
			minMax.set( static_cast<float>(*iPixel), static_cast<float>(*iPixel) );

			for(	const uint8	*iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth();
					iPixel != iEnd;
					iPixel++ )
			{
				uint8 value		= (*iPixel);
				float fValue	= static_cast<float>(value);
				
				if ( fValue < minMax.getMin() )
				{
					minMax.setMin( value );
				}
				else if ( fValue > minMax.getMax() )
				{
					minMax.setMax( value );
				}
				// else do nothing
			}
		}
		break;

		case IImage::INT16:
		{
			// scan image
			const int16 *iPixel( static_cast<const int16*>(pImage->pixels()) );
			minMax.set( static_cast<float>(*iPixel), static_cast<float>(*iPixel) );

			for(	const int16 *iEnd = iPixel + pImage->width()*pImage->height()*pImage->depth();
					iPixel != iEnd;
					iPixel++ )
			{
				int16 value		= (*iPixel);
				float fValue	= static_cast<float>(value);
				
				if ( fValue < minMax.getMin() )
				{
					minMax.setMin( value );
				}
				else if ( fValue > minMax.getMax() )
				{
					minMax.setMax( value );
				}
				// else do nothing
			}
		}
		break;
		
		default:
			assert( false && "Unsupported image type" );
	}

	return ( minMax );
}



const MinMax ImageUtilities::computeMinMax( const vgd::Shp< IImage > image ) 
{ 
	return ( computeMinMax(image.get()) );
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
				const float			fNewColor	= a*static_cast<float>(color) + b;
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
