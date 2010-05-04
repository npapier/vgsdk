// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_HIDDENNODE_HPP_
#define _VGGTK_NODE_HIDDENNODE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/menu.h>

#include <vgd/Shp.hpp>
#include <vgd/WeakPtr.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgGTK
{

namespace node
{

/**
 * @brief	Structure that contains a hidden node.
 *			Node is hidden by deletting its primitives.
 */
struct HiddenNode
{
	HiddenNode(vgd::Shp< vgd::node::VertexShape > node );

	~HiddenNode();

	/**
	* @brief	Hide the node by deleting its primitives.
	*			Primitives are stocked in m_primitives.
	*/
	void hide();

	/**
	* @brief	Show the node by resdtoring its primitives
	*/
	void restorePrimitives();

	/**
	* @brief	Get the current node.
	*
	* @return	the current node.
	*/
	vgd::Shp< vgd::node::VertexShape > getNode();

	/**
	* @brief	Check if the hidden node still existe. A node can be deleted even if it is hidden.
	*
	* @return	true if current node exists.
	*/
	bool hasNode();

	/**
	* @brief	When a node is hidden, a menu item is created in "hidden node" sub menu.
	*
	* @return	The current menu item.
	*/
	Gtk::MenuItem * getMenuItem();

	/**
	* @brief	When a node is hidden, a menu item is created in "hidden node" sub menu.
	*
	* @param menuItem	the menu item used.
	*/
	void setMenuItem( Gtk::MenuItem * menuItem );

private:
	vgd::WeakPtr< vgd::node::VertexShape >	m_node;
	std::vector< vgd::node::Primitive >		m_primitives;
	Gtk::MenuItem							* m_hiddenMenuItem;
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_ACTIONSNODE_HPP_*/
