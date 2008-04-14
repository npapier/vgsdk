// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_GRAPH_BROWSER_HPP_
#define _VGGTK_GRAPH_BROWSER_HPP_

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/treeview.h>

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/graph/TreeModelProvider.hpp"



namespace vgGTK
{

namespace graph
{



/**
 * @brief	Implements a gtkmm Widget that provide a ready to use vgSDK graph browser.
 */
struct VGGTK_API Browser : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	Browser();

	/**
	 * @brief	Updates the root node of the graph to browse
	 *
	 * You can pass an empty reference to clear the browser's content.
	 *
	 * @param	root	a reference to the new root node, empty if none
	 */
	void setRoot( vgd::Shp< vgd::node::Group > root );

private:

	Gtk::Toolbar		m_toolbar;			///< The managed toolbar widget.
	Gtk::ScrolledWindow	m_scrolled;			///< Contains the tree view.
	Gtk::TreeView		m_treeView;			///< The managed treeview widget;
	Gtk::ToolButton		m_refreshButton;	///< The refresh toolbar button.
	TreeModelProvider	m_modelProvider;	///< The managed tree model provider.

	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onRefresh();	///< Handles click on the refresh button.
	//@}

	/**
	 * @brief	Sets the attributs to a text cell renderer using the given model column to retrieve the right text.
	 *
	 * The purpose is to alter the text aspect to reflect that a node will not get rendered.
	 */
	void textCellDataFunc( const Gtk::TreeModelColumn< Glib::ustring > & textColumn, Gtk::CellRenderer * renderer, const Gtk::TreeModel::iterator & row );
};




} // namespace graph

} // namespace vgGTK



#endif /*_VGGTK_GRAPH_BROWSER_HPP_*/
