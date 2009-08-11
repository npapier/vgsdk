// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/field/EditorDialog.hpp"

#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>

#include "vgGTK/field/Editor.hpp"
#include "vgGTK/field/operations.hpp"



namespace vgGTK
{

namespace field
{



EditorDialog::EditorDialog( Gtk::Window & parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName )
:	Dialog			( "Field Editor", parent ),
	m_fieldManager	( fieldManager ),
	m_fieldName		( fieldName ),
	m_editor		( createEditor(fieldManager, fieldName) )
{
	Gtk::HBox		* topBox		= Gtk::manage( new Gtk::HBox() );
	Gtk::VBox		* contentBox	= Gtk::manage( new Gtk::VBox() );
	Gtk::Alignment	* alignment		 = Gtk::manage( new Gtk::Alignment(0.5, 0.0, 1.0, 0.0) );	
	Gtk::Image		* image			= Gtk::manage( new Gtk::Image(Gtk::Stock::EDIT, Gtk::ICON_SIZE_DIALOG) );
	Gtk::Label		* label			= Gtk::manage( new Gtk::Label() );

	
	// Initial content creation.
	topBox->set_border_width( 7 );
	topBox->set_spacing( 15 );
	topBox->pack_start( *alignment, Gtk::PACK_SHRINK );
	topBox->add( *contentBox );

	alignment->add( *image );

	label->set_alignment( 0.f, 0.f );
	label->set_justify( Gtk::JUSTIFY_LEFT );
		
	contentBox->set_spacing( 15 );
	contentBox->pack_start( *label, Gtk::PACK_SHRINK );
	
	
	// Editor configuration.
	if( m_editor )
	{
		label->set_markup( Glib::ustring::compose("<big><big><i>%1</i> Field Edition</big></big>", m_fieldName) );
		contentBox->add( m_editor->getWidget() );
		
//		add_button( Gtk::Stock::REVERT_TO_SAVED, -2 );
		add_button( Gtk::Stock::CANCEL, -1 );
		add_button( Gtk::Stock::OK, 0 );
		set_default_response( 0 );
		
		m_editor->grabFocus();
	}
	else
	{
		const Glib::ustring	fieldTypeName	= m_fieldManager->getFieldType(m_fieldName).name();
		Gtk::Label			* message		= Gtk::manage( new Gtk::Label() );
		
		label->set_markup( Glib::ustring::compose("<big><big><i>%1</i> Field Edition</big></big>", m_fieldName) ); 
		message->set_text( Glib::ustring::compose("%1 is not supported yet.", fieldTypeName) );
		contentBox->add( *message );
		
		add_button( Gtk::Stock::OK, 0 );
		set_default_response( 0 );
	}

	// Final content initialization.
	set_has_separator(false);
	set_resizable( m_editor ? m_editor->resizable() : false );
	get_vbox()->add( *topBox );
	get_vbox()->show_all();
}



void EditorDialog::on_response( int response_id )
{
	// const bool	valid = (m_editor && response_id == 0) ? m_editor->validate() : true;
	
	// if( valid )
	// {
		// if( m_editor )
		// {
			// m_editor->commit();
		// }
		
		// Dialog::on_response( response_id );
	// }
	
	if( m_editor && response_id == 0 )
	{
		m_editor->commit();
	}
/*	else if ( m_editor && response_id == -2 )
	{
		m_editor->?
	}*/

	Dialog::on_response( response_id );
}



} // namespace field

} // namespace vgGTK
