// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
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
	set_width_chars( 20 );
	set_activates_default( true );
}



void String::clear()
{
	set_text( Glib::ustring() );
}



const bool String::hasValue() const
{
	return get_text().empty() == false;
}



const std::string String::getValue() const
{
	return get_text();
}



void String::grabFocus()
{
	grab_focus();
}



void String::on_changed()
{
	Gtk::Entry::on_changed();
	m_signalChanged.emit();
}



void String::setValue( const std::string & value )
{
	// Assigns the new text to the widget.
	set_text( value );
	
	// Computes the new width of the widget.
	const int	valueWidth = value.size();

	if( valueWidth > get_width_chars()  )
	{
		const int newWidth = valueWidth + 5;

		set_width_chars( newWidth > 80 ? 80 : newWidth );
	}
}



const bool String::validate()
{
	return true;
}



const bool String::resizable() const
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
