// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_GRAPH_FIELDMANAGEREDITOR_HPP_
#define _VGGTK_GRAPH_FIELDMANAGEREDITOR_HPP_

#include <gtkmm/liststore.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>

#include <vgd/field/FieldManager.hpp>


namespace vgGTK
{

namespace graph
{



/**
 * @brief	Implements a gtkmm based widget that allows to edit a field manager.
 */
struct FieldManagerEditor : public Gtk::TreeView
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
	 * @brief	Assignes the field manager to editor.
	 *
	 * @param	fieldManager	a reference to a field manager, empty to clear the editor
	 *
	 * @see		clear
	 */
	void setFieldManager( vgd::Shp< vgd::field::FieldManager > fieldManager );


private:

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

};



} // namespace graph

} // namespace vgGTK



#endif /*_VGGTK_GRAPH_FIELDMANAGEREDITOR_HPP_*/
