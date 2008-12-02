// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_ADAPTER_MFPRIMITIVEADAPTER_HPP_
#define _VGGTK_FIELD_ADAPTER_MFPRIMITIVEADAPTER_HPP_

#include <gtkmm/cellrenderercombo.h>
#include <gtkmm/liststore.h>

#include <vgd/node/Primitive.hpp>

#include "vgGTK/field/adapter/MFAdapter.hpp"



namespace vgGTK
{

namespace field
{

namespace adapter
{



/**
 * @brief	Multi-field editor adapter for vgd::node::Primitive values.
 */
struct MFPrimitiveAdapter : public MFAdapter< vgd::node::Primitive >
{
	/**
	 * @brief	Constructor
	 */
	MFPrimitiveAdapter();
	
	/**
	 * @name	Overides
	 */
	//@{
	void addColumnsToRecord( Gtk::TreeModel::ColumnRecord & columnRecord );	
	void addColumnsToView( Gtk::TreeView & view );	
	void updateToRow( const Gtk::TreeRow & row, const vgd::node::Primitive & value ) const;	
	void updateFromRow( const Gtk::TreeRow & row, vgd::node::Primitive & value ) const;
	//@}
	
private:

	/**
	 * @name	Tree Model Columns
	 */
	//@{
	Gtk::TreeModelColumn< vgd::node::Primitive::Type >	m_typeColumn;
	Gtk::TreeModelColumn< Glib::ustring >				m_typeNameColumn;
	Gtk::TreeModelColumn< int >							m_startIndexColumn;
	Gtk::TreeModelColumn< int >							m_numIndicesColumn;
	//@}
	
	/**
	 * @name	Primitive Type Cell Rendering
	 */
	//@{
	Glib::RefPtr< Gtk::ListStore> 						m_primitiveTypeList;
	Gtk::TreeModel::ColumnRecord						m_primitiveTypeColumnRecord;
	Gtk::TreeModelColumn< vgd::node::Primitive::Type >	m_primitiveTypeValueColumn;
	Gtk::TreeModelColumn< Glib::ustring >				m_primitiveTypeNameColumn;
	Gtk::CellRendererCombo								m_primitiveTypeCellRenderer;
	
	void appendPrimitiveType( Glib::RefPtr< Gtk::ListStore > list, const vgd::node::Primitive::Type value );
	void primitiveTypeChanged( const Glib::ustring& path, const Gtk::TreeModel::iterator& iter );
	//@}
};



} // namespace adapter

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_ADAPTER_MFPRIMITIVEADAPTER_HPP_
