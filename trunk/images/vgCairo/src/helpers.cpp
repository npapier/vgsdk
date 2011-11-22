// VGSDK - Copyright (C) 2008, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgCairo/helpers.hpp"

#include <vgm/vgm.hpp>



namespace vgCairo
{



void rounded_rectangle( cairo_t * cr, const float x, const float y, const float width, const float height, const float radius )
{
	//   A****BQ
	//   H      C
	//   *      *
	//   G      D
	//  F****E

	cairo_move_to(cr, x+radius,y);													// Move to A
	cairo_line_to(cr, x+width-radius,y);											// Straight line to B
	cairo_curve_to(cr, x+width,y,x+width,y,x+width,y+radius);						// Curve to C, Control points are both at Q
	cairo_line_to(cr, x+width,y+height-radius);										// Move to D
	cairo_curve_to(cr, x+width,y+height,x+width,y+height,x+width-radius,y+height);	// Curve to E
	cairo_line_to(cr, x+radius,y+height);											// Line to F
	cairo_curve_to(cr, x,y+height,x,y+height,x,y+height-radius);					// Curve to G
	cairo_line_to(cr, x,y+radius);													// Line to H
	cairo_curve_to(cr, x,y,x,y,x+radius,y);											// Curve to A
}



void ellipse( cairo_t * cr, const float x, const float y, const float width, const float height )
{
	cairo_translate( cr, x + width / 2.f, y + height / 2.f );
	cairo_scale( cr, width / 2.f, height / 2.f );
	cairo_arc( cr, 0.f, 0.f, 1.f, 0.f, 2.f * vgm::PI );
}



} // namespace vgCairo
