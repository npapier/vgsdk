// VGSDK - Copyright (C) 2007, Nicolas Papier, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGD_BASIC_ITRANSFERFUNCTION_HPP
#define _VGD_BASIC_ITRANSFERFUNCTION_HPP

#include "vgd/vgd.hpp"

namespace vgd { namespace basic { struct IImage; } }



namespace vgd
{
	
namespace basic
{

	
/**
 * @brief Defines the interface for ILayers transfer functions.
 *
 * @todo getShaderSrc()
 *  
 * @author	Nicolas Papier
 * @author	Guillaume Brocker
 */
struct VGD_API ITransferFunction
{
	
	/**
	 * @brief Virtual destructor
	 */
	virtual ~ITransferFunction();
	
	/**
	 * @brief Applies the transfer function on a given image.
	 * 
	 * @param image		the image to process
	 * 
	 * @return the resulting image
	 * 
	 * @remarks	The transfer function is expected to create a new image
	 *			to store the processing result.
	 */
	virtual vgd::Shp< IImage > apply( const vgd::Shp< IImage > image ) const = 0;
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_ITRANSFERFUNCTION_HPP
