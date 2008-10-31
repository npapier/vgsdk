// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/widget/String.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{



String::String()
{
	set_activates_default( true );
}



void String::clear()
{
	set_text( Glib::ustring() );
}



const std::string String::getValue() const
{
	return get_text();
}



void String::setValue( const std::string & value )
{
	set_text( value );
}



const bool String::validate()
{
	return true;
}



void String::setFrame( const bool frame )
{
	set_has_frame( frame );
}



} // namespace widget

} // namespace field

} // namespace vgGTK
