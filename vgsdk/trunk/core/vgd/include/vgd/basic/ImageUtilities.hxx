// VGSDK - Copyright (C) 2007, Nicolas Papier, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGD_BASIC_IMAGEUTILITIES_HXX_
#define _VGD_BASIC_IMAGEUTILITIES_HXX_

#include <limits>
#include <vgm/Utilities.hpp>



namespace vgd
{

namespace basic
{
	
	
	
/**
 * @brief	Converts the given alpha value into the given component type.
 * 
 * @param	alpha	an alpha value to convert
 * 
 * @return	the alpha representation in a given component type
 */
template< typename ComponentType >
const ComponentType ImageUtilities::convertAlpha( const float alpha )
{
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );
	
	using vgm::Utilities;
	
	return static_cast< ComponentType >( 
		Utilities::linearInterpolation(	0.f, std::numeric_limits< ComponentType >::min(), 
										1.f, std::numeric_limits< ComponentType >::max(),
										alpha) ); 
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



template< typename ComponentType >
const MinMax ImageUtilities::doComputeMinMax( const IImage* pImage )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::LUMINANCE_ALPHA)	||
			(pImage->format() == IImage::LUMINANCE)			||
			(pImage->format() == IImage::COLOR_INDEX) );

	MinMax				minMax;
	const uint32		components	= pImage->components();
	const ComponentType	* iPixel	= static_cast< const ComponentType* >( pImage->pixels() );
	const ComponentType * iEnd		= iPixel + pImage->width()*pImage->height()*pImage->depth()*components;
	
	minMax.set( static_cast<float>(*iPixel), static_cast<float>(*iPixel) );
	
	for( ; iPixel != iEnd; iPixel += components )
	{
		const float fValue = static_cast< float >( *iPixel );
		if( fValue < minMax.getMin() )
		{
			minMax.setMin( fValue );
		}
		else if( fValue > minMax.getMax() )
		{
			minMax.setMax( fValue );
		}			
	}

	return ( minMax );
}



template< typename ComponentType >
vgd::Shp< Image > ImageUtilities::doExtractSlice( const IImage*	pImage, const SliceType	slice, const uint32	position )
{
	using vgd::basic::Image;
	using vgd::basic::IImage;

	assert( pImage->width() > 0 );
	assert( pImage->height() > 0 );
	assert( pImage->depth() > 0 );

	const ComponentType*	inputPixel			= static_cast<const ComponentType*>(pImage->pixels());
	const int32				components			= pImage->components();
	const int32				sizeOfComponents	= sizeof(ComponentType) * components;

	vgd::Shp< Image >	pNewImage;
	ComponentType*		outputPixel;
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
			pNewImage = vgd::Shp< Image >( new Image(	pImage->width(), pImage->height(), 1,
														outputFormat, pImage->type(),
														0 )
												);

			outputPixel = static_cast<ComponentType*>(pNewImage->editPixels());
			
			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->depth() );
			
			inputPixel += position * (components * pImage->width() * pImage->height());
			
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
			pNewImage = vgd::Shp< Image >( new Image(	pImage->width(), pImage->depth(), 1,
														outputFormat, pImage->type(),
														0 )
													);

			outputPixel = static_cast<ComponentType*>(pNewImage->editPixels());

			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->height() );

			inputPixel += position * (components * pImage->width());

			for(	uint32 j=0, jMax = pImage->depth();
					j < jMax;
					++j )
			{
				std::memcpy( outputPixel, inputPixel, sizeOfComponents * pImage->width() );
				inputPixel	+= pImage->width() * components;
				outputPixel	+= pImage->width() * components;

// non optimized version
//				for(	uint32 i=0, iMax=pImage->width();
//						i < iMax;
//						++i )
//				{
//					std::memcpy( outputPixel, inputPixel, sizeOfComponents );
//					inputPixel += sizeOfComponents;
//					outputPixel += sizeOfComponents;
//				}

				inputPixel += pImage->width() * components * (pImage->height()-1);
			}
			
			pNewImage->editPixelsDone();
		}
		break;


		case SAGITTAL_SLICE:
		{
			pNewImage = vgd::Shp< Image >( new Image(	pImage->depth(), pImage->height(), 1,
														outputFormat, pImage->type(),
														0 )
													);

			outputPixel = static_cast<ComponentType*>(pNewImage->editPixels());

			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->width() );

			inputPixel += position * components;

			//
			const int32 stepI = pImage->width() * pImage->height() * components;
			const int32 stepJ = (-stepI * pImage->depth()) + pImage->width() * components;

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
					outputPixel += components;
				}

				inputPixel += stepJ;
			}
			
			pNewImage->editPixelsDone();
		}
		break;

		default:
			assert( false && "Unknown type of slice." );
	}
	
	return pNewImage;
}



template< typename ComponentType >
void ImageUtilities::doSetAlpha( vgd::basic::IImage *pImage, const float alpha )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::RGBA) ||
			(pImage->format() == IImage::BGRA) ||
			(pImage->format() == IImage::LUMINANCE_ALPHA) );
	
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	const ComponentType	effectiveAlpha	= convertAlpha< ComponentType >(alpha);
	const uint32		components		= pImage->components();
	ComponentType		* iPixel		= static_cast< ComponentType * >( pImage->editPixels() );
	
	for(	ComponentType *iEnd = iPixel + pImage->computeNumberOfPixels()*components;
			iPixel != iEnd;
			++iPixel )
	{
		iPixel += components - 1;
		(*iPixel) = effectiveAlpha;
	}

	pImage->editPixelsDone();
}



template< typename ComponentType >
void ImageUtilities::doSetAlphaIfNotBlack( vgd::basic::IImage *pImage, const float alpha )
{
	assert(	(pImage->format() == IImage::RGBA) ||
			(pImage->format() == IImage::BGRA) ||
			(pImage->format() == IImage::LUMINANCE_ALPHA) );

	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	const ComponentType	alphaValue	= convertAlpha< ComponentType >(alpha);
	const ComponentType	minValue	= std::numeric_limits< ComponentType >::min();
	const uint32		components	= pImage->components();
	ComponentType		* iPixel	= static_cast< ComponentType * >( pImage->editPixels() );
	ComponentType		* iEnd		= iPixel + pImage->computeNumberOfPixels() * components;
	
	while( iPixel != iEnd )
	{
		// Checks if the current pixel is black.
		bool isBlack = true;
		for( uint32 i = 0; i != (components - 1); ++i )
		{
			isBlack &= (iPixel[i] == minValue);
		}
		
		// Assignes the alpha according if the pixel is black or not.
		iPixel[components - 1] = (isBlack) ? minValue : alphaValue;
		
		// Go to the next pixel.
		iPixel += components;
	}

	pImage->editPixelsDone();
}




} // namespace basic

} // namespace vgd



#endif /*_VGD_BASIC_IMAGEUTILITIES_HXX_*/
