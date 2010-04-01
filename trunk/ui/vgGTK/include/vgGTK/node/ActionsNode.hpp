// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_ACTIONSNODE_HPP_
#define _VGGTK_NODE_ACTIONSNODE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgUI/Canvas.hpp>

namespace vgGTK
{

namespace graph
{
	struct Browser;
}

namespace node
{

struct HiddenNode
{
	HiddenNode(vgd::Shp< vgd::node::VertexShape > node, Gtk::MenuItem * hiddenMenuItem ) :
	m_node( node ),
	m_hiddenMenuItem ( hiddenMenuItem )
	{
	}

	void hide()
	{
		vgd::field::EditorRW< vgd::field::MFPrimitive >	editPrimitive = m_node->getFPrimitiveRW();

		for( uint i = 0; i < editPrimitive->size(); i++)
		{
			m_primitives.push_back( editPrimitive->operator[](i) );
		}

		editPrimitive->clear();
	}

	void restorePrimitives()
	{
		vgd::field::EditorRW< vgd::field::MFPrimitive >	editPrimitive = m_node->getFPrimitiveRW();

		editPrimitive->clear();
		
		for( uint i = 0; i < m_primitives.size(); i++)
		{
			editPrimitive->push_back( m_primitives[i] );
		}
	}

	vgd::Shp< vgd::node::VertexShape > getNode()
	{
		return m_node;
	}

	Gtk::MenuItem * getMenuItem()
	{
		return m_hiddenMenuItem;
	}

private:
	vgd::Shp< vgd::node::VertexShape >	m_node;
	std::vector< vgd::node::Primitive > m_primitives;
	Gtk::MenuItem						* m_hiddenMenuItem;
};

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
struct VGGTK_API ActionsNode
{
	static vgd::Shp< ActionsNode > getActionsNode();

	void setCanvas( vgUI::Canvas * canvas );
	void setBrowser( vgGTK::graph::Browser * browser );

	bool onBoutonPressEvent( GdkEventButton * event );

/**
 * @brief Show the popup menu
 * 
 * @param event: the GTK event.
 *
 * @param node: the selected vgsdk node.
 *
 * @param tree: true if we are in the treeview.
 */
	void showPopup(GdkEventButton * event, vgd::Shp< vgd::node::Node > node, POPUP_LOCATION location);

private:

	ActionsNode();
	
	static vgd::Shp< ActionsNode >		m_actionsNode;

	void onGetNodeInTree();				///< Handles the action that will select the node in the treeview.
	void onExpandSubTree();				///< Handles the action that will expand all the tree view sub-tree of the selection element.
	void onRemoveNode();				///< Handles the action that will remove the selected node from it parent.
	void onHideNode();					///< Handles the action that will hide the selected node.
	void onShowNode(vgd::Shp < HiddenNode > hidden);					///< Handles the action that will hide the selected node.
	void onExportNode();				///< Handles the action that will export the selected.
	void onSetToDefault();				///< Handles the action that will set node filed to default.
	void onSetOptionalToDefault();		///< Handles the action that will set the optional node field to default.
	void onInvertTriangleOrientation();	///< Handles the action that will invert triangles orientation.
	void onInvertNormalOrientation();	///< Handles the action that will invert nsls orientation.	

	vgUI::Canvas						* m_canvas;	///< Points to the canvas to refresh.
	vgGTK::graph::Browser				* m_browser;
	vgd::Shp< vgd::node::Node >			m_currentNode;

	/**
	 * @name	User Interface Management
	 */
	//@{
	Glib::ustring						m_uiDefinition;		///< Defines the user interfaces.
	Glib::RefPtr< Gtk::ActionGroup >	m_actions;			///< Holds all actions of the user interface.
	Glib::RefPtr< Gtk::UIManager >		m_uiManager;		///< Manages the user inteface toolbar and menus.
	Gtk::Menu							* m_hiddenMenu;
	Gtk::MenuItem						* m_hiddenMenuItem;
	//@}

	POPUP_LOCATION						m_location;
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_ACTIONSNODE_HPP_*/

