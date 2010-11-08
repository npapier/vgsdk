// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_MULTIFIELDEDITOR2_HPP_
#define _VGGTK_FIELD_MULTIFIELDEDITOR2_HPP_

#include <vector>

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/stock.h>
#include <gtkmm/table.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>

#include <vgd/field/TMultiField.hpp>
#include <vgUI/helpers.hpp>

#include "vgGTK/field/FieldEditor.hpp"



namespace vgGTK
{

namespace field
{



/**
 * @brief	Second generation multi-field editor that is based on a Gtk::TreeView.
 *
 * The template parameter must specify an vgGTK::field::adapter;;MFAdapter based-type.
 *
 * @see	vgGTK::field::adapter::MFAdapater
 */
template< typename MFAdapter >
struct MultiFieldEditor2 : public FieldEditor, public Gtk::Table
{
	/**
	 * @brief	Constructor
	 */
	MultiFieldEditor2()
	:	Table					( 1, 2, false ),
		m_addButton				( Gtk::Stock::ADD ),
		m_removeButton			( Gtk::Stock::REMOVE ),
		m_moveUpButton			( Gtk::Stock::GO_UP ),
		m_moveDownButton		( Gtk::Stock::GO_DOWN ),
		m_freezeChangedNotify	( false )
	{
		// Prepares the data model.
		m_columnRecord.add( m_indexColumn );
		m_adapter.addColumnsToRecord( m_columnRecord );
		m_listStore = Gtk::ListStore::create( m_columnRecord );
		m_adapter.setModel( m_listStore );
		
		// Prepares the tree view.
		m_treeView.set_model( m_listStore );
		m_treeView.set_size_request( 320, 200 );
		m_treeView.append_column("Index", m_indexColumn);
		m_treeView.get_selection()->set_mode( Gtk::SELECTION_MULTIPLE );
		m_adapter.addColumnsToView( m_treeView );
		
		// Prepares the buttons.
		m_buttonBox.set_layout( Gtk::BUTTONBOX_START );
		m_buttonBox.set_spacing( 5 );
		m_buttonBox.add( m_addButton );
		m_buttonBox.add( m_removeButton );
		m_buttonBox.add( m_moveUpButton );
		m_buttonBox.add( m_moveDownButton );
		
		// The scrolled window that is arround the tree view.
		m_scrolled.add( m_treeView );
		m_scrolled.set_shadow_type( Gtk::SHADOW_IN );
		
		// The status label.
		m_status.set_alignment( 0.f, 0.f );
		
		// The main layout.
		set_spacings( 5 );
		attach( m_scrolled, 0, 1, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND|Gtk::FILL );
		attach( m_buttonBox, 1, 2, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL );
		attach( m_status, 0, 1, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL );
		
		// Connects signal handlers.
		m_addButton.signal_clicked().connect( sigc::mem_fun(this, &MultiFieldEditor2< MFAdapter >::addClicked) );
		m_removeButton.signal_clicked().connect( sigc::mem_fun(this, &MultiFieldEditor2< MFAdapter >::removeClicked) );
		m_moveUpButton.signal_clicked().connect( sigc::mem_fun(this, &MultiFieldEditor2< MFAdapter >::moveUpClicked) );
		m_moveDownButton.signal_clicked().connect( sigc::mem_fun(this, &MultiFieldEditor2< MFAdapter >::moveDownClicked) );
		m_listStore->signal_row_changed().connect( sigc::mem_fun(this, &MultiFieldEditor2< MFAdapter >::rowChanged) );
	}

	
	/**
	 * @name	Overrides
	 */
	//@{
	Gtk::Widget& getWidget()
	{
		return *this;
	}
	
	void grabFocus()
	{
		m_treeView.grab_focus();
	}
	
	const bool resizable() const
	{
		return true;
	}
	
	void commit()
	{
		typedef vgd::field::TMultiField< typename MFAdapter::value_type > FieldType;

		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );
		
		fieldEditor->clear();
		
		for( Gtk::TreeModel::iterator i = m_listStore->children().begin(); i; ++i )
		{
			typename MFAdapter::value_type	value;
			
			m_adapter.updateFromRow( *i, value );
			fieldEditor->push_back( value );
		}
	}
	
	void refresh()
	{
		m_freezeChangedNotify = true;

		// Clears the view and the data backup copy.
		m_listStore->clear();
		m_backupValue.clear();
		

		// Gets the editor of the field.
		typedef vgd::field::TMultiField< typename MFAdapter::value_type > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );


		// Copies values from the field into the local edition model and backup of the data.
		for( unsigned int i = 0; i < fieldEditor->size(); ++i )
		{
			const Gtk::TreeRow	& row = *m_listStore->append();
			
			row[ m_indexColumn ] = i;
			m_adapter.updateToRow( row, (*fieldEditor)[i] );
			m_backupValue.push_back( (*fieldEditor)[i] );
		}

		
		// Updates the status label to show the number of elements.
		m_status.set_label( vgUI::compose("%1% elements", fieldEditor->size()) );


		// Sends a change notification.
		m_freezeChangedNotify = false;
		m_signalChanged.emit();
	}

	void rollback()
	{
		m_freezeChangedNotify = true;


		// Gets the editor of the field.
		typedef vgd::field::TMultiField< typename MFAdapter::value_type > FieldType;

		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );


		// Clears the view and the edited field.
		m_listStore->clear();
		fieldEditor->clear();
		
		
		// Copies values from the backup value into the local edition model and the field.
		for( unsigned int i = 0; i < m_backupValue.size(); ++i )
		{
			const Gtk::TreeRow	& row = *m_listStore->append();
			
			row[ m_indexColumn ] = i;
			m_adapter.updateToRow( row, m_backupValue[i] );
			fieldEditor->push_back( m_backupValue[i] );
		}


		// Updates the status label to show the number of elements.
		m_status.set_label( vgUI::compose("%1% elements", fieldEditor->size()) );


		// Sends a change notification.
		m_freezeChangedNotify = false;
		m_signalChanged.emit();
	}

	sigc::signal< void > & signalChanged()
	{
		return m_signalChanged;
	}
	
	const bool validate()
	{
		return true;
	}
	//@}
	
private:

	/**
	 * @name	Widgets
	 */
	//@{
	Gtk::ScrolledWindow	m_scrolled;
	Gtk::TreeView		m_treeView;
	Gtk::Label			m_status;
	Gtk::VButtonBox		m_buttonBox;
	Gtk::Button			m_addButton;
	Gtk::Button			m_removeButton;
	Gtk::Button			m_moveUpButton;
	Gtk::Button			m_moveDownButton;
	//@}
	
	/**
	 * @name	Data
	 */
	//@{
	MFAdapter										m_adapter;				///< Used to wrap items of the multifield to/from the edition model.
	std::vector< typename MFAdapter::value_type	>	m_backupValue;			///< Holds a copy of the initial multifield data.
	Gtk::TreeModelColumn< int >						m_indexColumn;			///< The columns that shows the row index.
	Gtk::TreeModel::ColumnRecord					m_columnRecord;			///< Holds all columns of the edition model.
	Glib::RefPtr< Gtk::ListStore >					m_listStore;			///< The edition model.
	sigc::signal< void >							m_signalChanged;		///< Emited when te content changed.
	bool											m_freezeChangedNotify;	///< True to prevent change notifications to get sent.
	//@}
	
	/**
	 * @name	Signal Handlers
	 */
	//@{	
	/**
	 * @brief	Handles clicks on the add button
	 */
	void addClicked()
	{
		m_freezeChangedNotify = true;


		Glib::RefPtr< Gtk::TreeSelection >	selection		= m_treeView.get_selection();
		const std::vector< Gtk::TreePath >	selectedPaths	= selection->get_selected_rows();
		Gtk::TreeModel::iterator			newRow;
		
		if( selectedPaths.empty() )
		{
			newRow = m_listStore->append();
		}
		else
		{
			newRow = m_listStore->insert_after( m_listStore->get_iter(selectedPaths.back()) );
		}
		
		if( newRow )
		{
			(*newRow)[ m_indexColumn ] = -1;
			m_adapter.updateToRow( (*newRow), typename MFAdapter::value_type() );
			
			selection->unselect_all();
			selection->select( newRow );
			m_treeView.scroll_to_row( m_listStore->get_path(newRow) );
			rebuildRowIndexes();
		}


		// Sends a change notification.
		m_freezeChangedNotify = false;
		m_signalChanged.emit();
	}
	
	/**
	 * @brief	Handles clicks on the remove button
	 */
	void removeClicked()
	{
		m_freezeChangedNotify = true;


		const std::vector< Gtk::TreePath >	selectedPaths	= m_treeView.get_selection()->get_selected_rows();
		
		for( int i = selectedPaths.size() - 1; i >= 0; --i )
		{
			m_listStore->erase( m_listStore->get_iter(selectedPaths[i]) );
		}
		
		rebuildRowIndexes();


		// Sends a change notification.
		m_freezeChangedNotify = false;
		m_signalChanged.emit();
	}
	
	/**
	 * @brief	Handle sthe click on the move up button
	 */
	void moveUpClicked()
	{
		const std::vector< Gtk::TreePath >	selectedPaths	= m_treeView.get_selection()->get_selected_rows();
		
		if( selectedPaths.empty() )
		{
			return;
		}
		else if( m_listStore->get_iter(selectedPaths.front()) == m_listStore->children().begin() )
		{
			return;
		}
		else
		{
			m_freezeChangedNotify = true;


			// Retrieves the value that is before the first selected row.
			const Gtk::TreeModel::iterator	oldRow	= -- m_listStore->get_iter(selectedPaths.front());
			const Gtk::TreeModel::iterator	newRow	= ++ m_listStore->get_iter(selectedPaths.back());
			
			m_listStore->move( oldRow, newRow );
			rebuildRowIndexes();


			// Sends a change notification.
			m_freezeChangedNotify = false;
			m_signalChanged.emit();
		}
	}
	
	/**
	 * @brief	Handle sthe click on the move down button
	 */
	void moveDownClicked()
	{
		const std::vector< Gtk::TreePath >	selectedPaths	= m_treeView.get_selection()->get_selected_rows();
		
		if( selectedPaths.empty() )
		{
			return;
		}
		else if( m_listStore->get_iter(selectedPaths.back()) == --m_listStore->children().end() )
		{
			return;
		}
		else
		{
			m_freezeChangedNotify = true;


			// Retrieves the value that is before the first selected row.
			const Gtk::TreeModel::iterator	oldRow	= ++ m_listStore->get_iter(selectedPaths.back());
			const Gtk::TreeModel::iterator	newRow	= m_listStore->get_iter(selectedPaths.front());
			
			m_listStore->move( oldRow, newRow );
			rebuildRowIndexes();


			// Sends a change notification.
			m_freezeChangedNotify = false;
			m_signalChanged.emit();
		}
	}

	void rowChanged( const Gtk::TreeModel::Path&, const Gtk::TreeModel::iterator& )
	{
		if( ! m_freezeChangedNotify )
		{
			m_signalChanged.emit();
		}
	}
	//@}
	
	/**
	 * @brief	Rebuilds the row indexes.
	 */
	void rebuildRowIndexes()
	{
		Gtk::TreeModel::iterator	row;
		unsigned int				index;
		
		for( row = m_listStore->children().begin(), index = 0; row != m_listStore->children().end(); ++row, ++index )
		{
			(*row)[ m_indexColumn ] = index;
		}
	}
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_MULTIFIELDEDITOR2_HPP_
