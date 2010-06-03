// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/field/FieldEditorDialog.hpp"

#include <cassert>

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>

#include <vgUI/Canvas.hpp>

#include "vgGTK/graph/convenience.hpp"
#include "vgGTK/field/FieldEditor.hpp"
#include "vgGTK/field/operations.hpp"



namespace vgGTK
{

namespace field
{



FieldEditorDialog::DialogContainer FieldEditorDialog::m_dialogs;



FieldEditorDialog::FieldEditorDialog( Gtk::Window & parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName, vgUI::Canvas * canvas )
:	Dialog			( "Field Editor", parent ),
	m_fieldManager	( fieldManager ),
	m_fieldName		( fieldName ),
	m_editor		( createEditor(fieldManager, fieldName) ),
	m_canvas		( canvas ),
	m_closeButton	( Gtk::Stock::CLOSE ),
	m_rollbackButton( Gtk::Stock::REVERT_TO_SAVED )
{
	Gtk::HBox	* headerBox		= Gtk::manage( new Gtk::HBox() );
	Gtk::VBox	* contentBox	= Gtk::manage( new Gtk::VBox() );
	Gtk::Image	* image			= Gtk::manage( new Gtk::Image(Gtk::Stock::EDIT, Gtk::ICON_SIZE_SMALL_TOOLBAR) );


	// Content box initialization.
	contentBox->set_border_width( 12 );
	contentBox->set_spacing( 12 );


	// Header box content creation.
	headerBox->pack_start( *image, Gtk::PACK_SHRINK );
	headerBox->add( m_label );
	headerBox->set_spacing( 7 );
	contentBox->pack_start( *headerBox, Gtk::PACK_SHRINK );

	m_label.set_alignment( 0.f, 0.5f );
		

	// Editor configuration.
	if( m_editor )
	{
		// Adds the editor's widget to the dialog and connects to some signals.
		contentBox->add( m_editor->getWidget() );
		m_editor->signalChanged().connect( sigc::mem_fun(this, &FieldEditorDialog::onEditorChanged) );

		
		// Adds buttons for the rollback and apply.
		get_action_area()->pack_start( m_rollbackButton, Gtk::PACK_SHRINK );
		m_rollbackButton.signal_clicked().connect( sigc::mem_fun(this, &FieldEditorDialog::onRollback) );
		m_rollbackButton.set_sensitive( false );

		
		// Gives the focus to the editor.
		m_editor->grabFocus();
	}
	else
	{
		const Glib::ustring	fieldTypeName	= m_fieldManager->getFieldType(m_fieldName).name();
		Gtk::Label			* message		= Gtk::manage( new Gtk::Label() );
		
		message->set_text( Glib::ustring::compose("%1 is not supported yet.", fieldTypeName) );
		contentBox->add( *message );
	}


	// Adds default button.
	get_action_area()->pack_start( m_closeButton, Gtk::PACK_SHRINK );
	m_closeButton.signal_clicked().connect( sigc::mem_fun(this, &FieldEditorDialog::onClose) );


	// Final content initialization.
	refreshLabel();
	set_has_separator(false);
	set_resizable( m_editor ? m_editor->resizable() : false );
	get_vbox()->add( *contentBox );


	// Connects observation to the eventual f_name field 
	if( m_fieldManager->isField("f_name") )
	{
		vgd::field::EditorRO< vgd::field::AbstractField >	nameEditor = m_fieldManager->getFieldRO< vgd::field::AbstractField >( "f_name" );

		nameEditor->attach( this );
	}
}



FieldEditorDialog::~FieldEditorDialog()
{
	// Disconnects observation to the eventual f_name field 
	if( m_fieldManager->isField("f_name") )
	{
		vgd::field::EditorRO< vgd::field::AbstractField >	nameEditor = m_fieldManager->getFieldRO< vgd::field::AbstractField >( "f_name" );

		nameEditor->detach( this );
	}
}



void FieldEditorDialog::create( Gtk::Window & parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName, vgUI::Canvas * canvas )
{
	// Searches for a dialog that already exists for the given field manager and field.
	DialogContainer::iterator	found = m_dialogs.end();

	for( found = m_dialogs.begin(); found != m_dialogs.end(); ++found )
	{
		FieldEditorDialog	* dialog = *found;

		if( dialog->m_fieldManager == fieldManager && dialog->m_fieldName == fieldName )
		{
			break;
		}
	}

	// Shows any existing dialog 
	if( found != m_dialogs.end() )
	{
		(*found)->raise();
		(*found)->grab_focus();
	}
	// Or builds a new dialog and shows it.
	else
	{
		FieldEditorDialog	* dialog = new FieldEditorDialog( parent, fieldManager, fieldName, canvas );

		m_dialogs.insert( m_dialogs.end(), dialog );
		dialog->show_all();
		dialog->signal_hide().connect( sigc::bind(sigc::ptr_fun(&FieldEditorDialog::onDialogHidden), dialog) );
	}
}



void FieldEditorDialog::onClose()
{
	hide();
}



void FieldEditorDialog::onDialogHidden( FieldEditorDialog * dialog )
{
	DialogContainer::iterator	found = std::find( m_dialogs.begin(), m_dialogs.end(), dialog );

	if( found != m_dialogs.end() )
	{
		m_dialogs.erase( found );
		delete dialog;
	}
}



void FieldEditorDialog::onEditorChanged()
{
	assert( m_editor );

	m_editor->commit();
	m_rollbackButton.set_sensitive( true );

	if( m_canvas )
	{
		m_canvas->refresh();
	}
}



void FieldEditorDialog::onRollback()
{
	assert( m_editor );

	m_editor->rollback();
	m_editor->grabFocus();
	m_rollbackButton.set_sensitive( false );

	if( m_canvas )
	{
		m_canvas->refresh();
	}
}



void FieldEditorDialog::refreshLabel()
{
	const std::string	name = vgGTK::graph::getFieldAsString(m_fieldManager, "f_name");

	m_label.set_markup( Glib::ustring::compose("<big><b>%1.%2</b></big>", name.empty() ? "Unamed" : name, m_fieldName) );
}



void FieldEditorDialog::updateField( const vgd::field::AbstractField & rField, const vgd::field::Event event )
{
	if( rField.name() == "f_name" )
	{
		refreshLabel();
	}
}



} // namespace field

} // namespace vgGTK
