// VGSDK - Copyright (C) 2007, Nicolas Papier, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGITK_IMAGEIO_HPP
#define _VGITK_IMAGEIO_HPP

#include <string>
#include <vgd/Shp.hpp>

namespace vgd { namespace basic { struct Image; } }



namespace vgITK
{



/**
 * @brief	Creates a vgd::basic::Image using the given itk image reader.
 * 
 * @param	imagePath	a path to the image to load
 *
 * @return	a reference to the created image
 * 
 * @throw ::vgITK::Failed()
 *
 * @remark	@c itkImageIOType is expected to inherit from itk::ImageIOBase class.
 * 
 * @remark	The following image types are supported : UINT8, INT8, UINT16, INT16, UINT32, INT32, FLOAT and DOUBLE.
 * @remark	The following image formats are supported : LUMINANCE, RGB and RGBA.
 *
 * @todo an helper function to instanciate loadImage<T>() with the good T using extension of the file.
 */
template< typename itkImageIOType >
vgd::Shp< vgd::basic::Image > loadImage( const std::string & imagePath ) /* throw ::vgITK::Failed() */;



//???// @todo code and doc
//template< typename itkImageIOType >
//void saveImage( vgd::Shp< vgd::basic::Image >, const std::string & imagePathName ) /* throw ::vgITK::Failed() */;



} // namespace vgITK



#include "vgITK/ImageIO.hxx"



#endif // #ifndef _VGITK_IMAGEIO_HPP
