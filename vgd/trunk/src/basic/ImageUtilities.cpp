// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/ImageUtilities.hpp"

#include <cstring>



namespace vgd
{

namespace basic
{



vgd::Shp< vgd::basic::Image > ImageUtilities::extractImage2D(	vgd::Shp< vgd::basic::IImage > pImage, 
																					const SliceType slice,
																					const uint32 position )
{
	using vgd::basic::Image;
	using vgd::basic::IImage;

	assert( pImage->type() == IImage::UINT8 );

	assert( pImage->width() > 0 );
	assert( pImage->height() > 0 );
	assert( pImage->depth() > 0 );

	const uint8*	inputPixel			= static_cast<const uint8*>(pImage->pixels());
	int32				components			= pImage->components();
	int32				sizeOfComponents	= sizeof(uint8) * components;

	vgd::Shp< Image > pNewImage;
	uint8*				outputPixel;
	
	switch ( slice )
	{
		case AXIAL_SLICE:
		{
			pNewImage = vgd::Shp< Image >( new Image( pImage->components(),
																	pImage->width(), pImage->height(), 1,
																	pImage->format(), pImage->type(),
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
			pNewImage = vgd::Shp< Image >( new Image( pImage->components(),
																	pImage->width(), pImage->depth(), 1,
																	pImage->format(), pImage->type(),
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
			pNewImage = vgd::Shp< Image >( new Image( pImage->components(),
																	pImage->depth(), pImage->height(), 1,
																	pImage->format(), pImage->type(),
																	0 )
													);

			outputPixel = static_cast<uint8*>(pNewImage->editPixels());

			// seek to initial position
			assert( position >= 0 );
			assert( position < pImage->width() );

			inputPixel += position * sizeOfComponents;

			//
			const int32 stepI = sizeOfComponents * pImage->width() * pImage->height();
			const int32 stepJ = -stepI * pImage->depth() + pImage->width()*sizeOfComponents;
			
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



void ImageUtilities::setAlpha( vgd::Shp< vgd::basic::IImage > pImage, const float alpha )
{
	using vgd::basic::IImage;
	
	assert(	(pImage->format() == IImage::RGBA) ||
				(pImage->format() == IImage::BGRA) ||
				(pImage->format() == IImage::LUMINANCE_ALPHA) );

	assert( pImage->type() == IImage::UINT8 );
	
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
			uint8* iPixel = static_cast<uint8*>(pImage->editPixels());
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*4;
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
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*2;
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



void ImageUtilities::setAlphaIfNotBlack( vgd::Shp< vgd::basic::IImage > pImage, const float alpha )
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
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*4;
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
			for(	uint8	*iEnd = iPixel + pImage->width()*pImage->height()*2;
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



} // namespace basic

} // namespace vgd
