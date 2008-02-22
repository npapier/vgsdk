// VGSDK - Copyright (C) 2007, Nicolas Papier, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#include <vgd/basic/Image.hpp>

#include "vgITK/Failed.hpp"


namespace vgITK
{



template< typename itkImageIOType >
vgd::Shp< vgd::basic::Image > loadImage( const std::string & imagePath )
{
	// Creates the image io filter.
	typename itkImageIOType::Pointer	imageIO = itkImageIOType::New();
	if( imageIO->CanReadFile(imagePath.c_str()) == false )
	{
		throw ::vgITK::Failed( imagePath + ": unable to read file (either missing or unsupported)." );
	}

	// Reads the image informations.
	imageIO->SetFileName( imagePath.c_str() );
	imageIO->ReadImageInformation();

	using vgd::basic::IImage;

	const uint		width	= imageIO->GetDimensions(0);
	const uint		height	= imageIO->GetDimensions(1);
	const uint		depth	= imageIO->GetDimensions(2);

	IImage::Type	type;
	switch( imageIO->GetComponentType() )
	{
		case itkImageIOType::UCHAR:		type = IImage::UINT8;	break;
		case itkImageIOType::CHAR:		type = IImage::INT8;	break;
		case itkImageIOType::USHORT:	type = IImage::UINT16;	break;
		case itkImageIOType::SHORT:		type = IImage::INT16;	break;
		case itkImageIOType::UINT:		type = IImage::UINT32;	break;
		case itkImageIOType::INT:		type = IImage::INT32;	break;
		case itkImageIOType::FLOAT:		type = IImage::FLOAT;	break;
		case itkImageIOType::DOUBLE:	type = IImage::DOUBLE;	break;

		default: throw ::vgITK::Failed( imagePath + ": image has unsupported component type." );
	}

	IImage::Format	format;
	switch( imageIO->GetPixelType() )
	{
		case itkImageIOType::SCALAR:	format = IImage::LUMINANCE;	break;
		case itkImageIOType::RGB:		format = IImage::RGB;		break;
		case itkImageIOType::RGBA:		format = IImage::RGBA;		break;

		default: throw ::vgITK::Failed( imagePath + ": image has an unsupported pixel format." );
	}

	// Creates the image and fills its buffer.
	vgd::Shp< vgd::basic::Image >	result = vgd::makeShp( new vgd::basic::Image(width, height, depth, format, type) );

	imageIO->Read( result->editPixels() );
	result->editPixelsDone();

	result->voxelSize()[0] = imageIO->GetSpacing(0);
	result->voxelSize()[1] = imageIO->GetSpacing(1);
	result->voxelSize()[2] = imageIO->GetSpacing(2);

	// Job's done.
	return result;
}


/*???
template< typename itkImageIOType >
void saveImage( vgd::Shp< vgd::basic::Image >, const std::string & imagePathName );*/

} // namespace vgITK
