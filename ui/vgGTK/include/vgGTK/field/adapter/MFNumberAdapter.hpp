// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_ADAPTER_MFNUMBERADAPTER_HPP_
#define _VGGTK_FIELD_ADAPTER_MFNUMBERADAPTER_HPP_

#include "vgGTK/field/adapter/MFAdapter.hpp"

#include <vector>



namespace vgGTK
{

namespace field
{

namespace adapter
{



/**
 * @brief	Multi-field editor adapter for numeric values.
 */
template< typename NumberType >
struct MFNumberAdapter : public MFAdapter< NumberType >
{
	void addColumnsToRecord( Gtk::TreeModel::ColumnRecord & columnRecord )
	{
		columnRecord.add( m_valueColumn );
	}
	
	void addColumnsToView( Gtk::TreeView & view )
	{
		view.append_column_editable( "Value", m_valueColumn );
	}
	
	void updateToRow( const Gtk::TreeRow & row, const NumberType & value ) const
	{
		(*row)[ m_valueColumn ] = value;
	}
	
	void updateFromRow( const Gtk::TreeRow & row, NumberType & value ) const
	{
		value = (*row)[ m_valueColumn ];
	}
	
private:

	Gtk::TreeModelColumn< NumberType >	m_valueColumn;
};



} // namespace adapter

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_ADAPTER_MFNUMBERADAPTER_HPP_
