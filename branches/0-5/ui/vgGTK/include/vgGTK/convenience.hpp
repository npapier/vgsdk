// VGSDK - Copyright (C) 2008, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_CONVENIENCE_HPP_
#define _VGGTK_CONVENIENCE_HPP_

#include <limits>
#include <gdkmm/color.h>
#include <gtkmm/spinbutton.h>
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



/**
 * @brief	Configures a Gtk::SpinButton for the given numeric type
 */
template< typename NumberType >
void configure( Gtk::SpinButton & sb )
{
	typedef std::numeric_limits< NumberType >	limits;

	const guint		digits		= limits::is_integer ? 0 : 5;
	const double	lower		= limits::is_integer ? static_cast<double>(limits::min()) : -static_cast<double>(limits::max());
	const double	upper		= limits::max();
	const double	stepIncr	= limits::is_integer ? 1.0 : 0.1;
	const double	pageIncr	= 10.0;
		
	sb.set_numeric( true );
	sb.set_digits( digits );
	sb.set_range( lower, upper );
	sb.set_increments( stepIncr, pageIncr );
}



} // namespce vgGTK



#endif /*_VGGTK_CONVENIENCE_HPP_*/
