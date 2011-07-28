// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_BASIC_HELPERS_HPP
#define _VGEGL_BASIC_HELPERS_HPP

#include <vgd/basic/Image.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{

namespace basic
{


/**
 * @name Helpers
 */
//@{

/**
 * @brief Convert IImage format to the OpenGL equivalent format.
 */
VGEGL_API const GLenum convertMyFormat2GL( const vgd::basic::IImage::Format format );

/**
 * @brief Convert OpenGL format to the IImage format and type.
 */
VGEGL_API const bool convertGLInternalFormat2My( const GLenum internalFormat, vgd::basic::IImage::Format& format, vgd::basic::IImage::Type& type );

/**
 * @brief Convert IImage type to the OpenGL equivalent type.
 */
VGEGL_API const GLenum convertMyType2GL( const vgd::basic::IImage::Type type );


//@}



} // namespace basic

} // namespace vgeGL

#endif //#ifndef _VGEGL_BASIC_HELPERS_HPP
