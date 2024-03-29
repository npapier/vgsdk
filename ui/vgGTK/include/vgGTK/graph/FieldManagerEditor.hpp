// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_GRAPH_FIELDMANAGEREDITOR_HPP_
#define _VGGTK_GRAPH_FIELDMANAGEREDITOR_HPP_

#include <gtkmm/liststore.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>

#include <vgd/field/FieldManager.hpp>
#include <vgd/field/IFieldObserver.hpp>

namespace vgUI {
	struct Canvas;
}


namespace vgGTK
{

namespace graph
{



/**
 * @brief	Implements a gtkmm based widget that allows to edit a field manager.
 */
struct FieldManagerEditor : public Gtk::TreeView, public vgd::field::IFieldObserver
{

	/**
	 * @brief	Constructor
	 */
	FieldManagerEditor();

	/**
	 * @brief	Clears the editor.
	 */
	void clear();
	
	/**
	 * @brief	Assignes the canvas to refresh after field changes.
	 *
	 * @param	canvas	a pointer to a canvas, null if none
	 */
	void setCanvas( vgUI::Canvas * canvas );

	/**
	 * @brief	Assignes the field manager to editor.
	 *
	 * @param	fieldManager	a reference to a field manager, empty to clear the editor
	 *
	 * @see		clear
	 */
	void setFieldManager( vgd::Shp< vgd::field::FieldManager > fieldManager );


	/**
	 * @name	Overrides
	 */
	//@{
	void updateField( const vgd::field::AbstractField & rField, const vgd::field::Event event );
	//@}


private:

	vgUI::Canvas							* m_canvas;		///< Points to the canvas to refresh.
	vgd::Shp< vgd::field::FieldManager >	m_fieldManager;	///< References the fied manager to edit.

	/**
	 * @name	Gtk::TreeView Model & Columns
	 */
	//@{
	Gtk::TreeModelColumn< Glib::ustring >	m_nameColumn;	///< Defines the name column of the model.
	Gtk::TreeModelColumn< Glib::ustring >	m_valueColumn;	///< Defines the value column of the model.
	Gtk::TreeModelColumn< Glib::ustring >	m_typeColumn;	///< Defines the type column of the model.
	Gtk::TreeModel::ColumnRecord			m_columnRecord;	///< Holds the defitions of the model's columns.
	Glib::RefPtr< Gtk::ListStore >			m_model;		///< Holds data to display.
	//@}


	/**
	 * @brief	Fills the managed model with the curent field manager.
	 */
	void fillModel();

	/**
	 * @brief	Refreshes the row at the given path.
	 */
	void refresh( const Gtk::TreeModel::Path & );

	/**
	 * @brief	refreshes the row pointed by the given iterator
	 */
	void refresh( Gtk::TreeModel::iterator );

	/**
	 * @brief	Refreshes field observation connections.
	 *
	 * @param	connect	true to connect observation on the current field manager's fields, false otherwise.
	 */
	void refreshFieldObservation( const bool connect );
	
	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
	//@}

};



} // namespace graph

} // namespace vgGTK



#endif /*_VGGTK_GRAPH_FIELDMANAGEREDITOR_HPP_*/
