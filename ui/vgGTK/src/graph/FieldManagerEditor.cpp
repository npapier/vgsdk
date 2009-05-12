// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/graph/FieldManagerEditor.hpp"

#include <cassert>
#include <typeinfo>

#include <gtkmm/dialog.h>
#include <gtkmm/messagedialog.h>

#include <vgd/node/IBoundingBox.hpp>
#include <vgUI/Canvas.hpp>

#include "vgGTK/field/EditorDialog.hpp"
#include "vgGTK/graph/convenience.hpp"



namespace vgGTK
{

namespace graph
{

namespace
{
	/**
	 * @name	Node Properties Prefixes
	 */
	//@{
	static const Glib::ustring	FIELD_PREFIX("f_");
	static const Glib::ustring	DIRTY_FLAG_PREFIX("df_");
	static const Glib::ustring	IBOUNDINGBOX_PREFIX("IBoundingBox");
	//@}
}



FieldManagerEditor::FieldManagerEditor()
:	m_canvas( 0 )
{
	m_columnRecord.add( m_nameColumn );
	m_columnRecord.add( m_valueColumn );
	m_columnRecord.add( m_typeColumn );
	m_model = Gtk::ListStore::create( m_columnRecord );

	set_model( m_model );
	append_column( "Name", m_nameColumn );
	append_column( "Value", m_valueColumn );
	append_column( "Type", m_typeColumn );

	get_column(0)->set_resizable();
	get_column(1)->set_resizable();
	get_column(2)->set_resizable();
	
	signal_row_activated().connect( sigc::mem_fun(this, &FieldManagerEditor::onRowActivated) );
}



void FieldManagerEditor::clear()
{
	m_model->clear();
	m_fieldManager.reset();
}



void FieldManagerEditor::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



void FieldManagerEditor::setFieldManager( vgd::Shp< vgd::field::FieldManager > fieldManager )
{
	// Clear the current state.
	m_model->clear();
	m_fieldManager.reset();


	// If a new field manager is passed, then update the state.
	if( fieldManager )
	{
		m_fieldManager = fieldManager;
		fillModel();
	}
}



void FieldManagerEditor::fillModel()
{
	assert( m_fieldManager );
	assert( m_model );


	// Retrieves all field names.
	typedef std::vector< std::string > 						StringContainer;
	typedef std::back_insert_iterator< StringContainer >	InsertIterator;

	StringContainer	fieldNames;
	InsertIterator	inserter( fieldNames );

	m_fieldManager->getFieldNames( inserter );


	// Updates the managed model.
	StringContainer::const_iterator	i;

	for( i = fieldNames.begin(); i != fieldNames.end(); ++i )
	{
		const std::string		name		= *i;
		const std::string		value		= getFieldAsString( m_fieldManager, name );
		const std::type_info	& typeInfo	= m_fieldManager->getFieldType( name );

		// Appends a new row to the model.
		const Gtk::TreeRow	& row( *m_model->append() );

		row[ m_nameColumn ]		= name.c_str();
		row[ m_valueColumn ]	= value.c_str();
		row[ m_typeColumn ]		= typeInfo.name();
	}



	// Retrieves all dirty flags names.
	StringContainer	dirtyFlagNames;
	InsertIterator	dirtyFlagInserter( dirtyFlagNames );

	m_fieldManager->getDirtyFlagNames( dirtyFlagInserter );

	// Updates the managed model.
	for( i = dirtyFlagNames.begin(); i != dirtyFlagNames.end(); ++i )
	{
		const std::string				name		= *i;
		const vgd::field::DirtyFlag *	dirtyFlag	= m_fieldManager->getDirtyFlag( name );
		assert( dirtyFlag != 0 );

		const std::string value = dirtyFlag->isDirty() ? "dirty" : "valid";
		const std::type_info	& typeInfo	= typeid(*dirtyFlag);



		// Appends a new row to the model.
		const Gtk::TreeRow	& row( *m_model->append() );

		row[ m_nameColumn ]		= name.c_str();
		row[ m_valueColumn ]	= value.c_str();
		row[ m_typeColumn ]		= typeInfo.name();
	}

	// Retrieves bounding box
	using vgd::node::IBoundingBox;
	vgd::Shp< IBoundingBox > ibb = vgd::dynamic_pointer_cast< IBoundingBox >( m_fieldManager );

	if ( ibb != 0 )
	{
		// Retrieves information about bounding box
		const std::string value = toString( ibb.get() );

		// Appends a new row to the model.
		const Gtk::TreeRow	& row( *m_model->append() );

		row[ m_nameColumn ]		= IBOUNDINGBOX_PREFIX;
		row[ m_valueColumn ]	= value.c_str();
	}
}



void FieldManagerEditor::refresh(const Gtk::TreeModel::Path& path)
{
	// Retrieves the data row.
	Gtk::TreeIter				i			= m_model->get_iter( path );
	const Gtk::TreeModel::Row	& row		= *i;
	const Glib::ustring			entryName	= row[m_nameColumn];
	
	if( entryName.find(FIELD_PREFIX) == 0 )
	{
		const std::string		value		= getFieldAsString( m_fieldManager, entryName );
		const std::type_info	& typeInfo	= m_fieldManager->getFieldType( entryName );

		row[ m_valueColumn ]	= value.c_str();
		row[ m_typeColumn ]		= typeInfo.name();
	}
	else if( entryName.find(DIRTY_FLAG_PREFIX) == 0 )
	{
		const vgd::field::DirtyFlag *	dirtyFlag	= m_fieldManager->getDirtyFlag( entryName );
		assert( dirtyFlag != 0 );

		const std::string value = dirtyFlag->isDirty() ? "dirty" : "valid";
		const std::type_info	& typeInfo	= typeid(*dirtyFlag);
	
		row[ m_valueColumn ]	= value.c_str();
		row[ m_typeColumn ]		= typeInfo.name();
	}
	else if( entryName.find(IBOUNDINGBOX_PREFIX) == 0 )
	{
		using vgd::node::IBoundingBox;

		vgd::Shp< IBoundingBox > ibb = vgd::dynamic_pointer_cast< IBoundingBox >( m_fieldManager );
		assert( ibb != 0 );
		
		// Retrieves information about bounding box
		const std::string value = toString( ibb.get() );

		row[ m_valueColumn ]	= value.c_str();		}
}



void FieldManagerEditor::onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
	// Retrieves the data row.
	Gtk::TreeIter				i		= m_model->get_iter( path );
	const Gtk::TreeModel::Row	& row	= *i;
	
	// Uses the row for edition, if it is a field.
	Gtk::Window					* topLevel	= dynamic_cast< Gtk::Window * >( get_toplevel() );
	const static Glib::ustring	fieldPrefix	= "f_";
	const Glib::ustring			fieldName	= row[m_nameColumn];
	
	if( fieldName.find(FIELD_PREFIX) == 0 )
	{
		vgGTK::field::EditorDialog	dialog( *topLevel, m_fieldManager, fieldName );
		
		if( dialog.run() == 0 )
		{
			refresh( path );
			if( m_canvas != 0 )
			{
				m_canvas->refresh();
			}
		}
	}
	else
	{
		Gtk::MessageDialog	dialog( *topLevel, "Sorry, this property is not editable." );
		
		dialog.set_title("Property Edition");
		dialog.run();
	}
}



} // namespace graph

} // namespace vgGTK
