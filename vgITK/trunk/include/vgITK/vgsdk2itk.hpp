// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGITK_VGSDK2ITK_H
#define _VGITK_VGSDK2ITK_H

#include <itkImage.h>
#include <vgd/Shp.hpp>

#include "vgITK/vgITK.hpp"
#include "vgITK/Failed.hpp"

namespace vgd
{
	namespace basic
	{
		struct IImage;
	}
}



namespace vgITK
{

typedef itk::Image< uint8, 3 >	ItkImageLuminanceUINT8Type;
typedef itk::Image< int8, 3 >	ItkImageLuminanceINT8Type;
typedef itk::Image< uint16, 3 >	ItkImageLuminanceUINT16Type;
typedef itk::Image< int16, 3 >	ItkImageLuminanceINT16Type;
typedef itk::Image< uint32, 3 >	ItkImageLuminanceUINT32Type;
typedef itk::Image< int32, 3 >	ItkImageLuminanceINT32Type;



/**
 * @brief Converts an vgsdk image into an itk image.
 *
 * @pre iimage != 0
 * @pre iimage->format() == IImage::LUMINANCE or COLOR_INDEX.
 * @pre iimage->type() == UINT8 or INT8 or UINT16 or INT16 or UINT32 or INT32
 * 
 * @remarks if iimage->format() == COLOR_INDEX, then the palette is ignored.
 * 
 * @remarks The image data is imported (no copy occurs). And the memory of the imaga data would not be freeing by the 
 * ITK image.
 * 
 * @verbatim itk::ImageBase<3>::Pointer convertedImageBase = ::vgITK::convertIImage2ItkImageBase( inputVGSDKImage );
 * typedef uint8 PixelType;
 * typedef itk::Image< PixelType, 3> ItkImageType;
 * ItkImageType::Pointer convertedImage = dynamic_cast<ItkImageType*>(convertedImageBase.GetPointer());
 * @endverbatim
 */
VGITK_API itk::ImageBase<3>::Pointer convertIImage2ItkImageBase( vgd::Shp< vgd::basic::IImage > iimage ) throw (::vgITK::Failed);



} // namespace vgITK


#include "vgITK/vgsdk2itk.hxx"


#endif //#ifndef _VGITK_VGSDK2ITK_H
