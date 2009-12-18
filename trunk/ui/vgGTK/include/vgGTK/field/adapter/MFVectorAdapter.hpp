// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_ADAPTER_MFVECTORADAPATER_HPP_
#define _VGGTK_FIELD_ADAPTER_MFVECTORADAPATER_HPP_

#include "vgGTK/field/adapter/MFAdapter.hpp"

#include <vector>



namespace vgGTK
{

namespace field
{

namespace adapter
{



/**
 * @brief	Multi-field editor adapter for vgd::Vector values.
 */
template< typename VectorType >
struct MFVectorAdapter : public MFAdapter< VectorType >
{
	MFVectorAdapter()
	:	m_columns( VectorType().getDim() )
	{}
	
	void addColumnsToRecord( Gtk::TreeModel::ColumnRecord & columnRecord )
	{
		for( unsigned int i = 0; i < m_columns.size(); ++i )
		{
			columnRecord.add( m_columns[i] );
		}
	}
	
	void addColumnsToView( Gtk::TreeView & view )
	{
		for( unsigned int i = 0; i < m_columns.size(); ++i )
		{
			view.append_column_editable( Glib::ustring::compose("%1",i), m_columns[i] );
		}
	}
	
	void updateToRow( const Gtk::TreeRow & row, const VectorType & value ) const
	{
		for( unsigned int i = 0; i < m_columns.size(); ++i )
		{
			(*row)[ m_columns[i] ] = value[i];
		}
	}
	
	void updateFromRow( const Gtk::TreeRow & row, VectorType & value ) const
	{
		for( unsigned int i = 0; i < m_columns.size(); ++i )
		{
			value[i] = (*row)[ m_columns[i] ];
		}
	}
	
private:

	typedef std::vector< Gtk::TreeModelColumn< typename VectorType::value_type > >	ColumnContainer;
	
	ColumnContainer	m_columns;
};



} // namespace adapter

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_ADAPTER_MFVECTORADAPATER_HPP_
