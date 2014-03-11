// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_ACTIONSMENU_HPP_
#define _VGGTK_NODE_ACTIONSMENU_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>

#include <vgAlg/actions/HiddenNode.hpp>

#include <vgd/Shp.hpp>
#include <vgd/Wkp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgGTK/node/InsertNode.hpp>

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/Canvas.hpp>

namespace vgGTK
{


namespace node
{

enum POPUP_LOCATION
{
	TREE,
	NODE,
	CANVAS
};


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
	 * @param event	the GTK event.
	 *
	 * @param node	the selected vgsdk node.
	 *
	 * @param tree	true if we are in the treeview.
	 */
	void showPopup(GdkEventButton * event, POPUP_LOCATION location );

private:
	/**
	 * @brief Create a menu with a list of action.
	 */
	void manageMenu( std::map< int, vgd::Shp< vgUI::actions::IActionUI > > actionsMap );

	/**
	 * @brief Call ManageMenu with hidden node action list.
	 */
	void manageHiddenNodeMenu();

	/**
	 * @brief Check if a menu has submenu/items, if not, hide the menu, show it otherwise.
	 */
	void ManageMenuVisibility( Gtk::Menu* menu, Gtk::MenuItem* menuItem = 0);

	/**
	 * @brief Create the filter with the current state.
	 */
	vgUI::actions::State	createState();

	/**
	 * @brief Apply state to all actions, hide/show them depending on current state.
	 */
	void					applyState();

	/**
	 * @brief Set required parameters for action.
	 *
	 * param action	action to define parameter.
	 */
	void					setParams( vgAlg::actions::IAction* action );

	/**
	 * @brief Check the number of node in the scene.
	 * 
	 * @return	Number of node in scene.
	 */
	int getTotalNumberOfShape();

	/**
	 * @brief Check the number of displayed node in the scene.
	 * 
	 * @return	Number of displayed node in scene.
	 */
	int	getDisplayedNodeNumber();



	vgd::Wkp< vgd::node::Node >		m_currentNode;			///< current selected node.
	vgd::Wkp< vgd::node::Group >	m_currentParentNode;	///< current parent of selected node.
	vgUI::Canvas					*m_canvas;				///< canvas of the application


	POPUP_LOCATION						m_location;				///< Location of the menu (Canvas, TreeView...).

	//new action manager variable
	Gtk::Menu*															m_rootMenu;			///< The root menu.
	vgd::Wkp< vgUI::actions::ActionsRegistry >							m_actionsRegistry;	///< Instance of the action UI registry.
	std::map< vgd::Shp < vgUI::actions::IActionUI >, Gtk::MenuItem* >	m_actionMap;		///< Map with an action and its GTK MenuItem.

	/**
	 * @name	User Interface Management
	 */
	//@{
	Glib::ustring							m_uiDefinition;		///< Defines the user interfaces.
	Glib::RefPtr< Gtk::ActionGroup >		m_actions;			///< Holds all actions of the user interface.
	Glib::RefPtr< Gtk::UIManager >			m_uiManager;		///< Manages the user inteface toolbar and menus.
	InsertNode								* m_insertNode;		///< Menu of insert nodes
	Gtk::MenuItem							* m_insertMenuItem;	///< MenuItem of insert nodes.
	//@}
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_ACTIONSMENU_HPP_*/

