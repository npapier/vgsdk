// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgITK/vgsdk2itk.hpp"

#include "vgITK/Failed.hpp"



namespace vgITK
{



itk::ImageBase<3>::Pointer convertIImage2ItkImageBase( vgd::Shp< vgd::basic::IImage > iimage ) throw (::vgITK::Failed)
{
	using vgd::basic::IImage;
	
	assert( iimage != 0 );

	assert(	(iimage->format() == IImage::LUMINANCE) ||
			(iimage->format() == IImage::COLOR_INDEX)	);
	
	itk::ImageBase<3>::Pointer retVal;
	
	switch ( iimage->type() )
	{
		case IImage::UINT8:
			retVal = convertIImage2ItkImage< ItkImageLuminanceUINT8Type >( iimage );
			break;

		case IImage::INT8:
			retVal = convertIImage2ItkImage< ItkImageLuminanceINT8Type >( iimage );
			break;

		case IImage::UINT16:
			retVal = convertIImage2ItkImage< ItkImageLuminanceUINT16Type >( iimage );
			break;

		case IImage::INT16:
			retVal = convertIImage2ItkImage< ItkImageLuminanceINT16Type >( iimage );
			break;

		case IImage::UINT32:
			retVal = convertIImage2ItkImage< ItkImageLuminanceUINT32Type >( iimage );
			break;

		case IImage::INT32:
			retVal = convertIImage2ItkImage< ItkImageLuminanceINT32Type >( iimage );
			break;
		
		default:
			throw Failed("Unable to convert vgsdk iimage to itk image (unsupported iimage.type).");
	}
	
	return retVal;
}



} // namespace vgITK
