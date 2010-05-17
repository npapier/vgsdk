// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_EDITMENU_HPP_
#define _VGGTK_NODE_EDITMENU_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/actiongroup.h>
#include <gtkmm/menu.h>
#include <gtkmm/uimanager.h>

#include <vgd/Shp.hpp>

#include <vgGTK/node/ActionsNode.hpp>

namespace vgGTK
{


namespace node
{


/**
 * @brief Popup menu to edit node.
 */
struct VGGTK_API EditMenu
{
	EditMenu();

	~EditMenu();

	Gtk::Menu * getMenu();	///< returns the GTK Menu widget.

	Glib::RefPtr< Gtk::UIManager > getUIManager();	///< returns the GTK Menu UIManager to manage acceleration keys.

private:

	vgd::Shp< ActionsNode >					m_actionsNode;	///< Actions class.

	/**
	 * @name	User Interface Management
	 */
	//@{
	Glib::ustring							m_uiDefinition;		///< Defines the user interfaces.
	Glib::RefPtr< Gtk::ActionGroup >		m_actions;			///< Holds all actions of the user interface.
	Glib::RefPtr< Gtk::UIManager >			m_uiManager;		///< Manages the user inteface toolbar and menus.
	//@}
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_EDITMENU_HPP_*/

