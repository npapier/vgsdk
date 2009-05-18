// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_ADAPTER_MFADAPTER_HPP_
#define _VGGTK_FIELD_ADAPTER_MFADAPTER_HPP_

#include <cassert>
#include <gtkmm/liststore.h>
#include <gtkmm/treeiter.h>
#include <gtkmm/treeview.h>



namespace vgGTK
{

namespace field
{

namespace adapter
{



/**
 * @brief	Abstract adapter for multi-field value edition.
 *
 * @see	vgGTK::field::MultiFieldEditor2
 */
template< typename T >
struct MFAdapter
{
	typedef T value_type;	///< Defines an alias on the value type to edit.
	
	/**
	 * @name	Interface
	 */
	//@{
	/**
	 * @brief	Asks the adapter to append relevant columns to the data model column record.
	 */
	virtual void addColumnsToRecord( Gtk::TreeModel::ColumnRecord & columnRecord ) = 0;
	
	/**
	 * @brief	Asks the adapter to append relevant columns to the tree view.
	 */
	virtual void addColumnsToView( Gtk::TreeView & view ) = 0;
	
	/**
	 * @brief	Asks the adapter to update the tree row with the given value.
	 */
	virtual void updateToRow( const Gtk::TreeRow & row ,const T & value ) const = 0;
	
	/**
	 * @brief	Asks the adapter to update the value with the given tree row.
	 */
	virtual void updateFromRow( const Gtk::TreeRow & row, T & value ) const = 0;
	//@}
	
	/**
	 * @brief	Assignes the model begin editied.
	 */
	void setModel( Glib::RefPtr< Gtk::ListStore > model )
	{
		assert( ! m_listStore );
		
		m_listStore = model;
	}
	
protected:
	Glib::RefPtr< Gtk::ListStore > m_listStore;	///< References the model that stores the whole data to edit.
};



} // namespace adapater

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_ADAPTER_MFADAPTER_HPP_