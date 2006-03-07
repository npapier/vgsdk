// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include <itkImportImageContainer.h>
#include <vgd/basic/IImage.hpp>



namespace vgITK
{

/**
 * @brief Converts an vgsdk image into an itk image.
 * 
 * @remarks The image data is imported (no copy occurs). And the memory of the imaga data would not be freeing by the 
 * ITK image.
 * 
 * @pre iimage != 0
 */
template< typename ItkImageType >
typename ItkImageType::Pointer convertIImage2ItkImage( vgd::Shp< vgd::basic::IImage > iimage )
{
	assert( iimage != 0 );

	ItkImageType::Pointer dstImage = ItkImageType::New();
	
	// Create the region for the ITK image
	ItkImageType::SizeType size;
	size[0] = iimage->width();
	size[1] = iimage->height();
	size[2] = iimage->depth();
	ItkImageType::RegionType const region(size);
	dstImage->SetRegions(region);
	
	// Get a pointer to the voxels in the IImage
	ItkImageType::PixelType* voxels = reinterpret_cast<ItkImageType::PixelType*>(iimage->editPixels());
	iimage->editPixelsDone();

	// Assign the pointer to the ITK image container
	itk::ImportImageContainer<uint32, ItkImageType::PixelType>::Pointer container;
	container = itk::ImportImageContainer<uint32, ItkImageType::PixelType>::New();

	container->SetImportPointer(voxels, iimage->computeNumberOfPixels(), false);

	dstImage->SetPixelContainer(container);
	
	return dstImage;
}


} // namespace vgITK
