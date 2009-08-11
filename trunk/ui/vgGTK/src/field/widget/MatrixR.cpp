// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/widget/MatrixR.hpp"

#include <boost/lexical_cast.hpp>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>



namespace vgGTK
{

namespace field
{

namespace widget
{



MatrixR::MatrixR()
{
	set_spacing( 7 );
	
	
	// Creates the matrix edition controls layout.
	Gtk::HBox	* rows[4];
	
	rows[0] = Gtk::manage( new Gtk::HBox() );
	rows[1] = Gtk::manage( new Gtk::HBox() );
	rows[2] = Gtk::manage( new Gtk::HBox() );
	rows[3] = Gtk::manage( new Gtk::HBox() );
	
	for( int i = 0; i < 16; ++i )
	{
		m_elements[i].set_has_frame( false );
		m_elements[i].set_width_chars( 10 );
		
		rows[i/4]->add( m_elements[i] );
	}
	
	Gtk::Frame	* frame		= Gtk::manage( new Gtk::Frame() );
	Gtk::VBox	* frameBox	= Gtk::manage( new Gtk::VBox() );
	
	frameBox->add( *rows[0] );
	frameBox->add( *rows[1] );
	frameBox->add( *rows[2] );
	frameBox->add( *rows[3] );
	frame->add( *frameBox );
	frame->set_shadow_type( Gtk::SHADOW_IN );
	
	add( *frame );
	
	
	// Adds buttons to set matrix to identity or null.
	Gtk::HButtonBox	* hButtonBox		= Gtk::manage( new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER, 5) );
	Gtk::Button		* identityButton	= Gtk::manage( new Gtk::Button("_Identity", true) );
	Gtk::Button		* nullButton		= Gtk::manage( new Gtk::Button("_Null", true) );
	
	hButtonBox->add( *identityButton );
	hButtonBox->add( *nullButton );
	
	identityButton->signal_clicked().connect( sigc::mem_fun(this, &MatrixR::onIdentity) );
	nullButton->signal_clicked().connect( sigc::mem_fun(this, &MatrixR::onNull) );
	
	add( *hButtonBox );
}



void MatrixR::clear()
{
	for(int i = 0; i < 16; ++i)
	{
		m_elements[i].set_text( Glib::ustring() );
	}
}



const vgm::MatrixR MatrixR::getValue() const
{
	vgm::MatrixR	result;
	
	for( int i = 0; i < 16; ++i )
	{
		try
		{
			result(i/4, i%4) = boost::lexical_cast< float >( m_elements[i].get_text() );
		}
		catch( const boost::bad_lexical_cast & )
		{
			result(i/4, i%4) = 0.f;
		}
	}
	
	return result;
}



const bool MatrixR::hasValue() const
{
	for(int i = 0; i < 16; ++i)
	{
		if( m_elements[i].get_text().empty() == false )
		{
			return true;
		}
	}

	return false;
}



void MatrixR::setValue( const vgm::MatrixR & value )
{
	for(int i = 0; i < 16; ++i)
	{
		m_elements[i].set_text( Glib::ustring::compose("%1", value(i/4, i%4) ) );
	}
}



const bool MatrixR::validate()
{
	bool	validate = true;
	
	for(int i = 0; i < 16 && validate; ++i)
	{
		try
		{
			boost::lexical_cast< float >( m_elements[i].get_text() );
		}
		catch( const boost::bad_lexical_cast & )
		{
			showWarning("Please, enter a floating point number.");
			m_elements[i].grab_focus();
			validate = false;
		}
	}
	
	return validate;
}



const bool MatrixR::resizable() const
{
	return false;
}



void MatrixR::setFrame( const bool frame )
{
	for(int i = 0; i < 16; ++i)
	{
		m_elements[i].set_has_frame( frame );
	}
}



void MatrixR::onIdentity()
{
	vgm::MatrixR	identity;
	
	identity.setIdentity();
	setValue( identity );
}



void MatrixR::onNull()
{
	vgm::MatrixR	null( 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 );
	
	setValue( null );
}



} // namespace widget

} // namespace field

} // namespace vgGTK
