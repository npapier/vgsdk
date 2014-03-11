// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NODE_EDITMENU_HPP_
#define _VGQT_NODE_EDITMENU_HPP_

#include <QMenu>

#include <vgd/Shp.hpp>
#include <vgd/node/Node.hpp>

#include <vgUI/actions/ActionsRegistry.hpp>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace node
{

/**
 * @brief Popup menu to edit node.
 */
struct VGQT_API EditMenu : public QMenu
{
    EditMenu();

    ~EditMenu();

private:

    void onSelectionChanged();

    /**
     * @name	User Interface Management
     */
    /*
    //@{
    Glib::ustring							m_uiDefinition;		///< Defines the user interfaces.
    Glib::RefPtr< Gtk::ActionGroup >		m_actions;			///< Holds all actions of the user interface.
    Glib::RefPtr< Gtk::UIManager >			m_uiManager;		///< Manages the user inteface toolbar and menus.
    //@}
    */
    QList < vgd::Shp< vgUI::actions::IActionUI > >	m_actionList;		///< List of all action used in edit menu.

};


} // namespace node

} // namespace vgQt

#endif _VGQT_NODE_EDITMENU_HPP_
