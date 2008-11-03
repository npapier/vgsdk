// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/field/EditorDialog.hpp"

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
	// Initial content creation.
	m_label.set_justify( Gtk::JUSTIFY_LEFT );
		
	m_content.set_border_width( 7 );
	m_content.set_spacing( 5 );
	m_content.pack_start( m_label );
	
	if( m_editor )
	{
		m_label.set_markup( Glib::ustring::compose("Change the value of the field <b>%1</b> :", m_fieldName) );
		m_content.pack_start( m_editor->getWidget() );
		
		add_button( Gtk::Stock::CANCEL, -1 );
		add_button( Gtk::Stock::OK, 0 );
		set_default_response( 0 );
		
		m_editor->grabFocus();
	}
	else
	{
		const Glib::ustring	fieldTypeName( m_fieldManager->getFieldType(m_fieldName).name() );
		
		m_label.set_label( Glib::ustring::compose("The edition of fields of type %1 is not supported yet.", fieldTypeName) ); 

		add_button( Gtk::Stock::OK, 0 );
		set_default_response( 0 );
	}

	// Final content initialization.
	set_has_separator(false);
	set_resizable( false );
	get_vbox()->pack_start( m_content, Gtk::PACK_SHRINK );
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
	
	if( m_editor )
	{
		m_editor->commit();
	}
	Dialog::on_response( response_id );
}



} // namespace field

} // namespace vgGTK
