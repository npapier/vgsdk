// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/UserSettings.hpp"

#include <gtkmm/alignment.h>
#include <gtkmm/expander.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>



namespace vgGTK
{

namespace engine
{



Gtk::Widget * createFrame( const Glib::ustring & labelText, Gtk::Widget * content )
{
	Gtk::Frame		* frame		= Gtk::manage( new Gtk::Frame() );
	Gtk::Label		* label		= Gtk::manage( new Gtk::Label() );
	Gtk::Alignment	* alignment	= Gtk::manage( new Gtk::Alignment() );

	alignment->set_padding( 7, 7, 12, 12 );
	alignment->add( *content );

	label->set_markup( Glib::ustring::compose("<b>%1</b>", labelText) );

	frame->set_shadow_type( Gtk::SHADOW_NONE );
	frame->set_label_align( 0, 0.5 );
	frame->set_label_widget( *label );
	frame->add( *alignment );

	return frame;
}



UserSettings::UserSettings()
{
	Gtk::Label			* label			= Gtk::manage( new Gtk::Label() );
	Gtk::VBox			* levelBox		= Gtk::manage( new Gtk::VBox() );
	Gtk::Expander		* expander		= Gtk::manage( new Gtk::Expander("Descriptions") );
	Gtk::VBox			* descriptions	= Gtk::manage( new Gtk::VBox() );
	
	label->set_alignment( 0, 0 );
	label->set_text( "To configure rendering settings according to your hardware capabilities, \nselect a detail level or your graphic cards." );

	expander->add( *descriptions );
	descriptions->set_border_width( 7 );
	descriptions->set_spacing( 5 );

	levelBox->set_spacing( 7 );
	levelBox->add( m_levelCombo );
	levelBox->add( *expander );

	m_cardChangedConnection		= m_cardCombo.signal_changed().connect( sigc::mem_fun(this, &UserSettings::onCardChanged) );
	m_levelChangedConnection	= m_levelCombo.signal_changed().connect( sigc::mem_fun(this, &UserSettings::onLevelChanged) );
	
	set_spacing( 12 );
	pack_start( *label, Gtk::PACK_SHRINK );
	pack_start( *createFrame("Detail Levels", levelBox), Gtk::PACK_SHRINK );
	pack_start( *createFrame("Graphic Cards", &m_cardCombo), Gtk::PACK_SHRINK );


	// Fills the scale and the description expander with available levels.
	const int	levelCount = m_settings.getLevelCount();

	for( int i = 0; i != levelCount; ++i )
	{
		const Glib::ustring	levelName			= m_settings.getName(i);
		const Glib::ustring	levelDescription	= m_settings.getDescription(i);
		Gtk::Label			* descriptionWidget = Gtk::manage( new Gtk::Label() );

		m_levelCombo.append_text( levelName );

		descriptionWidget->set_alignment( 0, 0 );
		descriptionWidget->set_markup( Glib::ustring::compose("%1: <i>%2</i>", levelName, levelDescription) );
		descriptions->add( *descriptionWidget );
	}


	// Adds a notification when no description has been found.
	if( levelCount == 0 )
	{
		Gtk::Label	* descriptionWidget = Gtk::manage( new Gtk::Label() );

		descriptionWidget->set_alignment( 0, 0 );
		descriptionWidget->set_markup( "<i>No description found</i>" );
		descriptions->add( *descriptionWidget );
	}


	// Fills the list with available grapgic cards
	typedef std::vector< std::string >	StringVector;

	const StringVector	cards = m_settings.getGraphicCards< StringVector >();

	for( StringVector::const_iterator i = cards.begin(); i != cards.end(); ++i )
	{
		m_cardCombo.append_text( *i );
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
	refreshCard();
	m_signalChanged.emit();
}



void UserSettings::onCardChanged()
{
	const Glib::ustring	card( m_cardCombo.get_active_text() );

	if( !card.empty() )
	{
		m_settings.setGraphicCard( card );
		refreshLevel();
		m_signalChanged.emit();
	}
}



void UserSettings::onLevelChanged()
{
	const int level = m_levelCombo.get_active_row_number();

	if( level >= 0 )
	{
		m_settings.setLevel( level );
		refreshCard();
		m_signalChanged.emit();
	}
}



void UserSettings::refreshCard()
{
	m_cardChangedConnection.block();
	
	const Glib::ustring	card	= m_settings.getGraphicCard();

	m_cardCombo.set_active_text( card );

	m_cardChangedConnection.unblock();
}



void UserSettings::refreshLevel()
{
	m_levelChangedConnection.block();

	const int	level	= m_settings.getLevel();

	m_levelCombo.set_active( level );

	m_levelChangedConnection.unblock();
}



} // namespace engine

} // namespace vgGTK
