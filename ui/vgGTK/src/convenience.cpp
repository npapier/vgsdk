// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/convenience.hpp"



namespace vgGTK
{



const Gdk::Color color_cast( const vgm::Vec4f & color )
{
	Gdk::Color	result;
	
	result.set_rgb_p( color[0], color[1], color[2] );
	
	return result;
}



const vgm::Vec4f color_cast( const Gdk::Color & color )
{
	vgm::Vec4f	result;
	
	result[0] = static_cast< float >( color.get_red_p() );
	result[1] = static_cast< float >( color.get_green_p() );
	result[2] = static_cast< float >( color.get_blue_p() );
	result[3] = 1.f;
	
	return result;
}



} // namespce vgGTK
