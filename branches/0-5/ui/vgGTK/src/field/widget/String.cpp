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
	const Pango::FontDescription	fontDesc("Monospace");
	
	
	m_entry.modify_font( fontDesc );
	m_entry.set_width_chars( 20 );
	m_entry.set_activates_default( true );
	m_entry.signal_changed().connect( sigc::mem_fun(this, &String::onTextChanged) );

    
	m_textViewScroll.add( m_textView );
	m_textViewScroll.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	m_textViewScroll.set_shadow_type( Gtk::SHADOW_IN );
	m_textViewScroll.show_all();

	m_textView.modify_font( fontDesc );
	m_textView.get_buffer()->signal_changed().connect( sigc::mem_fun(this, &String::onTextChanged) );


	Gtk::Alignment	* multiLineButtonAlign = Gtk::manage( new Gtk::Alignment(0, 0, 0, 0) );

	multiLineButtonAlign->add( m_multiLineButton );
	multiLineButtonAlign->show_all();

	m_multiLineButton.set_label( "Multi-line" );
	m_multiLineButton.signal_toggled().connect( sigc::mem_fun(this, &String::onMultiLineToggled) );
	
	
	pack_start( m_entry, Gtk::PACK_SHRINK );
	add( m_textViewScroll );
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
	return m_textViewScroll.is_visible();
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


void String::show_all_vfunc()
{
	show();
	if( isMultiLine() )
	{
		m_textViewScroll.show_all();
	}
	else
	{
		m_entry.show();
	}
}



void String::setMultiLine( const bool multi )
{
	m_ignoreTextChanges = true;

	if( multi )
	{
		m_entry.hide();
		m_textViewScroll.show_all();
		m_textView.get_buffer()->set_text( m_entry.get_text() );
	}
	else
	{
		m_textViewScroll.hide();
		m_entry.show();
		m_entry.set_text( m_textView.get_buffer()->property_text() );
	}

	m_ignoreTextChanges = false;
}



void String::setValue( const std::string & value )
{
	// Assigns the new text to the widgets.
	m_entry.set_text( value );
	m_textView.get_buffer()->set_text( value );

	// Computes the new width of the entry widget.
	const int	valueWidth = value.size();

	if( valueWidth > m_entry.get_width_chars()  )
	{
		const int newWidth = valueWidth + 5;

		m_entry.set_width_chars( newWidth > 80 ? 80 : newWidth );
	}

	// If the new value containes at least one cariage return, then switch in multi-line edition mode.
	const bool	goMultiLine = value.find_first_of("\n") != std::string::npos;

	m_multiLineButton.set_active( goMultiLine );
	setMultiLine( goMultiLine );
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
