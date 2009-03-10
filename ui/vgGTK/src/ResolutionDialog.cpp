// VGSDK - Copyright (C) 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/ResolutionDialog.hpp"

#include <boost/lexical_cast.hpp>

#include <glibmm/regex.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>



namespace vgGTK
{



ResolutionDialog::ResolutionDialog( Gtk::Widget * widget )
:	Dialog			( "Resolution" ),
	m_resetButton	( Gtk::Stock::UNDO ),
	m_applyButton	( Gtk::Stock::APPLY ),
	m_widget		( widget ),
	m_oldResolution	( widget->get_width(), widget->get_height() ),
	m_newResolution	( 0, 0 )
{
	// Creates the main layout.
	Gtk::Label	* label = Gtk::manage( new Gtk::Label("Select, in the list bellow, a resolution to apply, \nor specify your own.", 0, 0) );
	Gtk::VBox	* box	= Gtk::manage( new Gtk::VBox(false, 8) );
	
	box->set_border_width( 12 );
	box->pack_start( *label, Gtk::PACK_SHRINK );
	box->pack_start( m_resolutions, Gtk::PACK_SHRINK );
	get_vbox()->add( *box );
	
	
	// Adds buttons.
	get_action_area()->add( m_resetButton );
	get_action_area()->add( m_applyButton );
	add_button( Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE );
	
	m_applyButton.set_sensitive( false );
	
	
	// Connects to some signals.
	m_applyButton.signal_clicked().connect( sigc::mem_fun(this, &ResolutionDialog::applyClicked) );
	m_resetButton.signal_clicked().connect( sigc::mem_fun(this, &ResolutionDialog::resetClicked) );
	m_resolutions.get_entry()->signal_changed().connect( sigc::mem_fun(this, &ResolutionDialog::resolutionChanged) );
	
	
	// Fills the resolution box with predefined resolutions.
	m_resolutions.append_text("1024x768");
	m_resolutions.append_text("800x600");
	m_resolutions.append_text("720x576");
	m_resolutions.append_text("640x480");
	
	
	// Shows the whole things
	show_all();
	
	
	// Assigns the initial resolution.
	m_resolutions.get_entry()->set_text( resolutionToString(m_oldResolution.first, m_oldResolution.second) );
}



void ResolutionDialog::applyResolution( Gtk::Widget * widget, const int width, const int height )
{
	Gtk::Window * top = dynamic_cast< Gtk::Window * >( widget->get_toplevel() );
	
	widget->set_size_request( width, height );
	top->unmaximize();
	top->unfullscreen();
	top->resize( width, height );
}



void ResolutionDialog::applyClicked()
{
	if( m_newResolution.first != m_widget->get_width() || m_newResolution.second != m_widget->get_height() )
	{
		applyResolution( m_widget, m_newResolution.first, m_newResolution.second );
	}
}



void ResolutionDialog::resetClicked()
{
	m_resolutions.get_entry()->set_text( resolutionToString(m_oldResolution.first, m_oldResolution.second) );
	applyResolution( m_widget, m_oldResolution.first, m_oldResolution.second );
}



void ResolutionDialog::resolutionChanged()
{
	const bool parsed = resolutionFromString( m_resolutions.get_entry()->get_text(), m_newResolution.first, m_newResolution.second );
	
	m_applyButton.set_sensitive( parsed );
}



const bool ResolutionDialog::resolutionFromString( const Glib::ustring & str, int & width, int & height )
{
	static const Glib::RefPtr< Glib::Regex >	regex	= Glib::Regex::create( "^\\s*(\\d+)\\s*x\\s*(\\d+)\\s*$" );
	const std::vector< Glib::ustring >			splits	= regex->split( str, Glib::REGEX_MATCH_ANCHORED );

	if( splits.empty() == false && splits[0] != str )
	{	
		width  = boost::lexical_cast< int >( splits[1] );
		height = boost::lexical_cast< int >( splits[2] );
		return true;
	}
	else
	{
		return false;
	}
}



const Glib::ustring ResolutionDialog::resolutionToString( const int width, const int height )
{
	return Glib::ustring::compose("%1x%2", width, height);
}



} // namespace vgGTK
