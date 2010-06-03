// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/widget/String.hpp"

#include <gtkmm/alignment.h>



namespace vgGTK
{

namespace field
{

namespace widget
{



String::String()
:	m_ignoreTextChanges( false )
{
	m_entry.set_width_chars( 20 );
	m_entry.set_activates_default( true );
	m_entry.signal_changed().connect( sigc::mem_fun(this, &String::onTextChanged) );

	m_textView.get_buffer()->signal_changed().connect( sigc::mem_fun(this, &String::onTextChanged) );

	m_scrolled.add( m_textView );
	m_scrolled.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	m_scrolled.set_shadow_type( Gtk::SHADOW_IN );
	m_scrolled.show_all();

	Gtk::Alignment	* multiLineButtonAlign = Gtk::manage( new Gtk::Alignment(0, 0, 0, 0) );

	m_multiLineButton.set_label( "Multiline" );
	m_multiLineButton.signal_toggled().connect( sigc::mem_fun(this, &String::onMultiLineToggled) );
	multiLineButtonAlign->add( m_multiLineButton );
	
	pack_end( *multiLineButtonAlign, Gtk::PACK_SHRINK );
	set_spacing( 7 );
	setMultiLine( false );
}



void String::clear()
{
	m_entry.set_text( Glib::ustring() );
}



const bool String::hasValue() const
{
	return m_entry.get_text().empty() == false;
}



const std::string String::getValue() const
{
	return isMultiLine() ? m_textView.get_buffer()->property_text() : m_entry.get_text();
}



void String::grabFocus()
{
	m_entry.grab_focus();
}



const bool String::isMultiLine() const
{
	return m_scrolled.is_visible();
}



void String::onMultiLineToggled()
{
	setMultiLine( m_multiLineButton.get_active() );
}



void String::onTextChanged()
{
	if( !m_ignoreTextChanges )
	{
		m_signalChanged.emit();
	}
}



void String::setMultiLine( const bool multi )
{
	m_ignoreTextChanges = true;

	if( multi )
	{
		remove( m_entry );
		add( m_scrolled );
		
		m_textView.get_buffer()->set_text( m_entry.get_text() );

	}
	else
	{
		remove( m_scrolled );
		add( m_entry );
		
		m_entry.set_text( m_textView.get_buffer()->property_text() );
	}

	m_ignoreTextChanges = false;
}



void String::setValue( const std::string & value )
{
	// Assigns the new text to the widget.
	m_entry.set_text( value );
	
	// Computes the new width of the widget.
	const int	valueWidth = value.size();

	if( valueWidth > m_entry.get_width_chars()  )
	{
		const int newWidth = valueWidth + 5;

		m_entry.set_width_chars( newWidth > 80 ? 80 : newWidth );
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
	m_entry.set_has_frame( frame );
}



} // namespace widget

} // namespace field

} // namespace vgGTK
