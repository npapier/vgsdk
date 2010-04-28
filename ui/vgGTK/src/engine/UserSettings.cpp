// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/UserSettings.hpp"

#include <gtkmm/alignment.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/stock.h>



namespace vgGTK
{

namespace engine
{



UserSettings::UserSettings()
{
	Gtk::Label	* label		= Gtk::manage( new Gtk::Label() );
	Gtk::HBox	* levelBox	= Gtk::manage( new Gtk::HBox() );
	
	label->set_alignment( 0, 0 );
	label->set_line_wrap( true );
	label->set_width_chars( -1 );
	label->set_max_width_chars( -1 );

	label->set_text( "To configure rendering settings according to your hardware capabilities, select a detail level in the list below.\n\nYou can also activate the appropriate detail level by selecting your graphic card in advanced mode." );

	m_selectCard.set_label( "Advanced..." );
	m_selectCard.signal_clicked().connect( sigc::mem_fun(this, &UserSettings::onSelectCardClicked) );

	levelBox->set_spacing( 7 );
	levelBox->add( m_levelCombo );
	levelBox->pack_end( m_selectCard, Gtk::PACK_SHRINK );

	m_levelCombo.signal_changed().connect( sigc::mem_fun(this, &UserSettings::onLevelChanged) );

	m_description.set_alignment( 0, 0 );
	m_description.set_line_wrap( true );
	m_description.set_width_chars( -1 );
	m_description.set_max_width_chars( -1 );

	set_spacing( 12 );
	pack_start( *label, Gtk::PACK_SHRINK );
	pack_start( *levelBox, Gtk::PACK_SHRINK );
	pack_start( m_description, Gtk::PACK_SHRINK );


	// Fills the combo with available levels.
	const int	levelCount = m_settings.getLevelCount();

	for( int i = 0; i != levelCount; ++i )
	{
		m_levelCombo.append_text( m_settings.getName(i) );
	}
}



const vge::engine::UserSettings & UserSettings::get() const
{
	return m_settings;
}



sigc::signal< void > & UserSettings::signalChanged()
{
	return m_signalChanged;
}



void UserSettings::set( const vge::engine::UserSettings & settings )
{
	m_settings = settings;
	refreshLevel();
	m_signalChanged.emit();
}



void UserSettings::onLevelChanged()
{
	const int level = m_levelCombo.get_active_row_number();

	if( level >= 0 )
	{
		m_settings.setLevel( level );
		m_description.set_markup( Glib::ustring::compose("<i>%1</i>", m_settings.getDescription(level)) );
		m_signalChanged.emit();
	}
	else
	{
		m_description.set_markup( "<i>No detail level selected.</i>" );
	}
}



void UserSettings::onSelectCardClicked()
{
	// Builds the main dialog layout.
	Gtk::Window	* toplevel = dynamic_cast< Gtk::Window* >( get_toplevel() );

	Gtk::Dialog			dialog;
	Gtk::VBox			box;
	Gtk::Label			label;
	Gtk::ListViewText	list( 1 );
	Gtk::ScrolledWindow	scrolled;

	label.set_text("In order to adjust the detail level to your hardware capabilities, select a graphic card in list below.");
	label.set_alignment( 0, 0 );
	label.set_width_chars( -1 );
	label.set_line_wrap( true );


	list.set_headers_visible( false );
	

	scrolled.add( list );
	scrolled.set_shadow_type( Gtk::SHADOW_IN );
	scrolled.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

	box.pack_start( label, Gtk::PACK_SHRINK );
	box.add( scrolled );
	box.set_spacing( 12 );
	box.set_border_width( 12 );

	dialog.get_vbox()->add( box );
	dialog.set_has_separator( false );
	dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	dialog.set_title( "Graphic card selection" );
	dialog.set_transient_for( *toplevel );
	dialog.show_all();


	// Fills the list with available graphic cards.
	typedef std::vector< std::string >	StringVector;
	const StringVector					cards = m_settings.getGraphicCards< StringVector >();

	for( StringVector::const_iterator i = cards.begin(); i != cards.end(); ++i )
	{
		list.append_text( *i );
	}
	

	// Runs the dialog.
	if( dialog.run() == Gtk::RESPONSE_OK )
	{
		const Gtk::ListViewText::SelectionList	selection = list.get_selected();

		if( selection.size() == 1 )
		{
			m_settings.setGraphicCard( list.get_text(selection.front()) );
			refreshLevel();
			m_signalChanged.emit();
		}
	}
}



void UserSettings::refreshLevel()
{
	const int	level	= m_settings.getLevel();

	m_levelCombo.set_active( level );
}



} // namespace engine

} // namespace vgGTK
