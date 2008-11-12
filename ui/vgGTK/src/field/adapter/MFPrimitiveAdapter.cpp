// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/adapter/MFPrimitiveAdapter.hpp"

#include <vgio/operators.hpp>



namespace vgGTK
{

namespace field
{

namespace adapter
{



MFPrimitiveAdapter::MFPrimitiveAdapter()
{
	// Prepares the primitive type cell renderer's list store.
	m_primitiveTypeColumnRecord.add( m_primitiveTypeValueColumn );
	m_primitiveTypeColumnRecord.add( m_primitiveTypeNameColumn );
	m_primitiveTypeList = Gtk::ListStore::create( m_primitiveTypeColumnRecord );
	
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::NONE			);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::POINTS			);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::LINES			);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::LINE_STRIP		);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::LINE_LOOP		);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::TRIANGLES		);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::TRIANGLE_STRIP	);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::TRIANGLE_FAN	);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::QUADS			);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::QUAD_STRIP		);
	appendPrimitiveType( m_primitiveTypeList, vgd::node::Primitive::POLYGON			);
	
	// Prepares the primitive type cell renderer.
	m_primitiveTypeCellRenderer.property_editable()		= true;
	m_primitiveTypeCellRenderer.property_editable_set()	= true;
	m_primitiveTypeCellRenderer.property_has_entry()	= false;
	m_primitiveTypeCellRenderer.property_mode()			= Gtk::CELL_RENDERER_MODE_EDITABLE;
	m_primitiveTypeCellRenderer.property_model()		= m_primitiveTypeList;
	m_primitiveTypeCellRenderer.property_text_column()	= 1;
	
	m_primitiveTypeCellRenderer.signal_changed().connect( sigc::mem_fun(this, &MFPrimitiveAdapter::primitiveTypeChanged) );
}



void MFPrimitiveAdapter::addColumnsToRecord( Gtk::TreeModel::ColumnRecord & columnRecord )
{
	columnRecord.add( m_typeColumn );
	columnRecord.add( m_typeNameColumn );
	columnRecord.add( m_startIndexColumn );
	columnRecord.add( m_numIndicesColumn );
}



void MFPrimitiveAdapter::addColumnsToView( Gtk::TreeView & view )
{
	int colNum;
	
	colNum = view.append_column( "Type", m_primitiveTypeCellRenderer );
	view.get_column( colNum - 1 )->add_attribute( m_primitiveTypeCellRenderer.property_text(), m_typeNameColumn );
	
	view.append_column_editable( "Start Index", m_startIndexColumn );
	view.append_column_editable( "Num Indices", m_numIndicesColumn );
}



void MFPrimitiveAdapter::updateToRow( const Gtk::TreeRow & row, const vgd::node::Primitive & value ) const
{
	(*row)[ m_typeColumn ] = value.getType();
	(*row)[ m_typeNameColumn ] = toString( value.getType() );
	(*row)[ m_startIndexColumn ] = value.getIndex();
	(*row)[ m_numIndicesColumn ] = value.getNumIndices();
}



void MFPrimitiveAdapter::updateFromRow( const Gtk::TreeRow & row, vgd::node::Primitive & value ) const
{
	value.setType( (*row)[ m_typeColumn ] );
	value.setIndex( (*row)[ m_startIndexColumn ] );
	value.setNumIndices( (*row)[ m_numIndicesColumn ] );
}



void MFPrimitiveAdapter::appendPrimitiveType( Glib::RefPtr< Gtk::ListStore > list, const vgd::node::Primitive::Type value )
{
	const Gtk::TreeRow & row = *list->append();
	
	row[ m_primitiveTypeValueColumn ] = value;
	row[ m_primitiveTypeNameColumn ] = toString(value);
}



void MFPrimitiveAdapter::primitiveTypeChanged( const Glib::ustring& path, const Gtk::TreeModel::iterator& iter )
{
	const Gtk::TreeRow	& primitiveRow = * m_listStore->get_iter( path );
	
	(*primitiveRow)[ m_typeColumn ]		= iter->get_value( m_primitiveTypeValueColumn );
	(*primitiveRow)[ m_typeNameColumn ]	= iter->get_value( m_primitiveTypeNameColumn );
}




} // namespace adapter

} // namespace field

} // namespace vgGTK