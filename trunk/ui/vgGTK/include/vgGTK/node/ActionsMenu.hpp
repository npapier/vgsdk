// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_ACTIONSMENU_HPP_
#define _VGGTK_NODE_ACTIONSMENU_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>

#include <vgd/Shp.hpp>
#include <vgd/WeakPtr.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgGTK/node/ActionsNode.hpp>
#include <vgGTK/node/HiddenNode.hpp>
#include <vgGTK/node/InsertNode.hpp>

#include <vgUI/Canvas.hpp>

namespace vgGTK
{


namespace node
{


/**
 * @brief Popup menu shared between vgGTK::GenericCanvas and vgGTK::graph::Browser.
 *
 * @todo replace singleton pattern with an observer pattern (to modify treeview by the canvas, onGetNodeInTree() method).
 */
struct VGGTK_API ActionsMenu
{
	ActionsMenu( POPUP_LOCATION location );

	~ActionsMenu();

	bool onBoutonPressEvent( GdkEventButton * event );

	void setCanvas( vgUI::Canvas * canvas );

/**
 * @brief Show the popup menu
 * 
 * @param event: the GTK event.
 *
 * @param node: the selected vgsdk node.
 *
 * @param tree: true if we are in the treeview.
 */
	void showPopup(GdkEventButton * event, POPUP_LOCATION location );

private:
	void hideAllMenu();											///< Hide all menu items.
	void manageHiddenNodeMenu( int displayedNode );				///< Manage (adds delete, check menuitems) hidden node menu.
	void showOnNodeMenu( int displayedNode );					///< Manage menu if a node is casted in canvas.
	void showInTreeViewMenu( int displayedNode );				///< Manage menu if menu is popup in treeview.

	vgd::WeakPtr< vgd::node::Node >		m_currentNode;			///< current selected node.
	vgd::WeakPtr< vgd::node::Group >	m_currentParentNode;	///< current parent of selected node.
	vgUI::Canvas						*m_canvas;				///< canvas of the application

	vgd::Shp< ActionsNode >				m_actionsNode;

	/**
	 * @name	User Interface Management
	 */
	//@{
	Glib::ustring							m_uiDefinition;		///< Defines the user interfaces.
	Glib::RefPtr< Gtk::ActionGroup >		m_actions;			///< Holds all actions of the user interface.
	Glib::RefPtr< Gtk::UIManager >			m_uiManager;		///< Manages the user inteface toolbar and menus.
	Gtk::Menu								* m_hiddenMenu;		///< Menu of hidden nodes
	Gtk::MenuItem							* m_hiddenMenuItem;	///< MenuItem of hidden nodes.
	InsertNode								* m_insertNode;		///< Menu of insert nodes
	Gtk::MenuItem							* m_insertMenuItem;	///< MenuItem of insert nodes.
	//@}

	POPUP_LOCATION						m_location;				///< Location of the menu (Canvas, TreeView...).
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_ACTIONSMENU_HPP_*/

