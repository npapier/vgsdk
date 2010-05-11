// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_INSERTSNODE_HPP_
#define _VGGTK_NODE_INSERTSNODE_HPP_

#include "vgGTK/vgGTK.hpp"


#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>

#include <vgd/Shp.hpp>
#include <vgd/WeakPtr.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

namespace vgGTK
{

namespace node
{


/**
 * @brief Sub menu of ActionsNode to insert node in graph.
 *
 * @todo replace singleton pattern with an observer pattern (to modify treeview by the canvas, onGetNodeInTree() method).
 */
struct VGGTK_API InsertNode
{

	InsertNode();

	~InsertNode();

	/**
	 * @brief return the menu previously created
	 *
	 * @return the insert node menu
	 */
	Gtk::Menu* getMenu();

	/**
	 * @brief Set the current selected node and its parent.
	 *
	 * @param currentNode Current selected node
	 *
	 * @param currentParentNode Parent node of the selected node
	 */
	void setCurrentNode( vgd::Shp< vgd::node::Node > currentNode, vgd::Shp< vgd::node::Group > currentParentNode );

	/**
	* @brief Set the created node
	*
	* @param node the previously created node
	*/
	void setCreatedNode( vgd::Shp< vgd::node::Node > node );

	/**
	* @brief Add a name to class name vector
	*
	* @param name new name to add
	*/
	void addClassName( std::string name );

private:

	void onInsertNode( std::string name );

	/**
	 * @name	User Interface Management
	 */
	//@{
	Gtk::Menu							* m_insertMenu;		///< Menu of hidden nodes
	//@}

	vgd::Shp< vgd::node::Node >			m_createdNode;			///< node to add.
	vgd::WeakPtr< vgd::node::Node >		m_currentNode;			///< current selected node.
	vgd::WeakPtr< vgd::node::Group >	m_currentParentNode;	///< current parent of selected node.
	std::vector< std::string >			m_classNames;			///< typeid name list of all creatable nodes.

};


} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_INSERTSNODE_HPP_*/
