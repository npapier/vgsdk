// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_CORNER_HPP
#define _VGD_BASIC_CORNER_HPP

#include "vgd/vgd.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief The four corners of a rectangle.
 */
enum Corner {
	BOTTOM_LEFT = 0,
	BOTTOM_RIGHT,
	TOP_RIGHT,
	TOP_LEFT
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_CORNER_HPP
