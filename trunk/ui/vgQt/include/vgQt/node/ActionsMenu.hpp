// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NODE_ACTIONSMENU_HPP_
#define _VGQT_NODE_ACTIONSMENU_HPP_

#include <vgAlg/actions/HiddenNode.hpp>

#include <vgd/Shp.hpp>
#include <vgd/Wkp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/Canvas.hpp>

#include <QMenu>

#include "vgQt/vgQt.hpp"

namespace vgQt
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
 * @brief Popup menu shared between vgQt::GenericCanvas and vgQt::graph::Browser.
 */
class VGQT_API ActionsMenu : public QMenu
{
	Q_OBJECT

public :

	/**
	 * @brief	Constructor
	 */
    ActionsMenu( QWidget* parent, POPUP_LOCATION location );

    void setCanvas( vgUI::Canvas * canvas );

    void showPopup( QPoint point, POPUP_LOCATION location );

private :

    /**
     * @brief Create a menu with a list of action.
     */
    void manageMenu( std::map< int, vgd::Shp< vgUI::actions::IActionUI > > actionsMap );

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
    int getDisplayedNodeNumber();

    /**
     * @brief Call ManageMenu with hidden node action list.
     */
    void manageHiddenNodeMenu();

    /**
     * @brief Check if a menu has submenu/items, if not, hide the menu, show it otherwise.
     */
    void manageMenuVisibility( QMenu* menu );

    /**
     * @brief Create the filter with the current state.
     */
    vgUI::actions::State createState();

    /**
     * @brief Apply state to all actions, hide/show them depending on current state.
     */
    void applyState();

    void setParams( vgAlg::actions::IAction* action );

    /**
     * @brief Add some actions into the actionsRegistry (not called but executes some macros)
     */
    void initActions();

    vgd::Wkp< vgd::node::Node >		m_currentNode;			///< current selected node.
    vgd::Wkp< vgd::node::Group >	m_currentParentNode;	///< current parent of selected node.

    vgd::Wkp< vgUI::actions::ActionsRegistry >					m_actionsRegistry;	///< Instance of the action UI registry.
    std::map< vgd::Shp < vgUI::actions::IActionUI >, QAction* >	m_actionMap;		///< Map with an action and its QT Menu.

    vgUI::Canvas	*m_canvas;				///< canvas of the application
    QMenu*			m_insertMenuItem;
    POPUP_LOCATION	m_location;				///< Location of the menu (Canvas, TreeView...).

public Q_SLOTS:

    void onCanvasMenuRequested(QPoint);

    void refresh();
};

} // namespace node

} // namespace vgQt

#endif // _VGQT_NODE_ACTIONSMENU_HPP_
