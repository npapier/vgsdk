// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_CONVENIENCE_HPP_
#define _VGGTK_CONVENIENCE_HPP_

#include <gdkmm/color.h>
#include <vgm/Vector.hpp>

#include "vgGTK/vgGTK.hpp"



namespace vgGTK
{



/**
 * @brief	Converts a vgm::Vec4f representing a color into a Gdk::Color.
 */
VGGTK_API const Gdk::Color color_cast( const vgm::Vec4f & color );



/**
 * @brief	Converts a Gdk::Color into a vgm::Vec4f representing a color.
 */
VGGTK_API const vgm::Vec4f color_cast( const Gdk::Color & color );



} // namespce vgGTK



#endif /*_VGGTK_CONVENIENCE_HPP_*/
