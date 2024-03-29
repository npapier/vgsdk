// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Maxime Peresson

#ifndef _VGGTK_GRAPH_BROWSER_HPP_
#define _VGGTK_GRAPH_BROWSER_HPP_

#include <set>

#include <gtkmm/actiongroup.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/paned.h>
#include <gtkmm/treeview.h>
#include <gtkmm/uimanager.h>

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/graph/FieldManagerEditor.hpp"
#include "vgGTK/graph/TreeModelColumnRecord.hpp"
#include "vgGTK/graph/TreeStore.hpp"
#include "vgGTK/node/ActionsMenu.hpp"


namespace vgUI {
	struct Canvas;
}



namespace vgGTK
{

namespace graph
{


/**
 * @brief	Implements a gtkmm Widget that provide a ready to use vgSDK graph browser.
 */
struct VGGTK_API Browser : public Gtk::VBox, public boost::signals::trackable
{
	/**
	 * @brief	Constructor
	 */
	Browser();
	
	/**
	 * @brief	Assignes the pointer to the canvas to refesh on graph changes.
	 *
	 * @param	canvas	a pointer to a canvas, null if none
	 */
	void setCanvas( vgUI::Canvas * canvas );

	/**
	 * @brief	Updates the root node of the graph to browse
	 *
	 * You can pass an empty reference to clear the browser's content.
	 *
	 * @param	root	a reference to the new root node, empty if none
	 */
	void setRoot( vgd::Shp< vgd::node::Group > root );



	/**
	 * @name Actions
	 */
	//@{

	/**
	 * @brief	Search recursively a vgsdk node in the treeview
	 *
	 * @param	children: a node of the treeview
	 *
	 * @param	node: the vgsdk node
	 *
	 * @param	it: interator of the row where the node is found
	 *
	 * @return true if the node is found
	 */
	bool searchNode( Gtk::TreeModel::Children children, vgd::Shp< vgd::node::Node > node, Gtk::TreeModel::Row *it );


	/**
	 * @brief	Select a vgsdk node in the treeview
	 *
	 * @param	node: the vgsdk node
	 */
	void selectNode( vgd::Shp< vgd::node::Node > node );

	/**
	 * @brief	Move back selection
	 */
	void movePrevious();

	/**
	 * @brief	Move forward selection
	 */
	void moveNext();
	

	/**
	 * @brief	Refresh the whole tree.
	 */
	void refreshTree();

	//@}



private:

	typedef std::set< Glib::ustring > StringSet;	///< Defines a set of Glib::ustring.
	
	vgUI::Canvas	* m_canvas;	///< Points to the canvas to refresh.

	/**
	 * @name	User Interface Management
	 */
	//@{
	static const Glib::ustring			m_uiDefinition;		///< Defines the user interfaces.
	Glib::RefPtr< Gtk::ActionGroup >	m_actions;			///< Holds all actions of the user interface.
	Glib::RefPtr< Gtk::UIManager >		m_uiManager;		///< Manages the user inteface toolbar and menus.

	vgd::Shp< vgGTK::node::ActionsMenu >	m_actionsMenu;
	//@}

	/**
	 * @name	Widgets
	 */
	//@{
	Gtk::Label					m_path;		///< Shows the current selection path.
	Gtk::VPaned					m_vpaned;	///< Allows to configure size between the tree view and the field managed editor.
	Gtk::TreeView				m_treeView;	///< The treeview widget that shows the vgSDK graph.
	FieldManagerEditor			m_editor;	///< Allows to edit the fields of the selected node.
	//@}

	/**
	 * @name	Data
	 */
	//@{
	vgd::Shp< vgd::node::Group >	m_root;			///< References the root node.
	const TreeModelColumnRecord		m_columns;		///< The tree store columns.
	Glib::RefPtr< TreeStore >		m_treeStore;	///< References the tree store.
	//@}

	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onButtonReleaseEvent( GdkEventButton * event );	///< Handles button clicks on the tree view.
	void onExpandAll();										///< Handles the action that will expand all tree view content.	
	void onExpandSubTree();									///< Handles the action that will expand all the tree view sub-tree of the selection element.
	void onExportScene();									///< Handles the action that will export the selected.
	void onFullRefresh();									///< Handles the action that will perfrom a refresh of the whole tree.
	void onRemoveNode();									///< Handles the action that will remove the selected node from it parent.
	void onSelectionChanged();								///< Handles notification about a selection change.
	void onActionChanged( vgAlg::actions::ActionOnNode action );
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

