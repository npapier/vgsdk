// VGSDK - Copyright (C) 2008, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCAIRO_HELPERS_HPP
#define _VGCAIRO_HELPERS_HPP

#include "vgCairo/vgCairo.hpp"
#include <cairo.h>



namespace vgCairo
{



/**
 * @brief Creates a rounded rectangular path.
 *
 * @param cr	a cairo context
 * @param x		the x coordinate of the top left corner of the rounded rectangle 
 * @param y		the y coordinate to the top left corner of the rounded rectangle 
 * @param width	the width of rounded rectangle
 * @param height	the height of rounded rectangle
 * @param radius	the radius of rounded corner
 *
 * @ingroup g_images
 */
VGCAIRO_API void rounded_rectangle( cairo_t * cr, const float x, const float y, const float width, const float height, const float radius );

/**
 * @brief Creates an ellipse in the box given by x, y, width, height.
 *
 * @param cr		a cairo context
 * @param x			the x coordinate of the top left corner of the box 
 * @param y			the y coordinate to the top left corner of box
 * @param width		the width of the box
 * @param height	the height of the box
 *
 * @ingroup g_images
 */
VGCAIRO_API void ellipse( cairo_t * cr, const float x, const float y, const float width, const float height );



} // namespace vgCairo

#endif // #ifndef _VGCAIRO_HELPERS_HPP
