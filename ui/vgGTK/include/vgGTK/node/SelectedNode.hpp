// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_SELECTEDNODE_HPP_
#define _VGGTK_NODE_SELECTEDNODE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgd/node/Node.hpp>
#include <vgGTK/node/HiddenNode.hpp>
#include <sigc++/sigc++.h>

namespace vgGTK
{

namespace node
{

enum ActionOnNode
{
	NONE,
	EXPAND,
	EXPORT,
	REFRESH,
	REMOVE,
	SELECT,
	MOVE_PREVIOUS,
	MOVE_NEXT
};

/**
* @brief	Singleton of current selected node.
*/
struct VGGTK_API SelectedNode
{

	/**
	* @brief	Get the instance of SelectedNode.
	*/
	static vgd::Shp< SelectedNode > getSelectedNodeObject();

	/**
	* @brief		Set the current selected node.
	*
	* @param node	Current selected node.
	*/
	void setSelectedNode( vgd::Shp< vgd::node::Node > node,  vgd::Shp< vgd::node::Group > parent = vgd::Shp< vgd::node::Group >() );

	/**
	* @brief	Get the current selected node.
	*
	* @return 	Current selected node.
	*/
	vgd::Shp< vgd::node::Node > getSelectedNode();

	/**
	* @brief	Get the parent of the current selected node.
	*
	* @return 	Current parent of selected node.
	*/
	vgd::Shp< vgd::node::Group > getParentSelectedNode();


	/**
	* @brief	Set custom action needed for the selected node.
	*
	* @param action	Action to do.
	*/
	void setAction( ActionOnNode action );

	/**
	* @brief	Get the hidden node list.
	*
	* @return	The node list.
	*/
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > getHiddenNodeList();

	/**
	* @brief	Get the current clipboarded node.
	*/
	void setClipboardedNode( vgd::Shp< vgd::node::Node > node );

	/**
	* @brief	Get the current clipboarded node.
	*/
	vgd::Shp< vgd::node::Node > getClipboardedNode();

	sigc::signal< void, vgd::Shp< vgd::node::Node > > signal_selection_changed; ///< Signal emited when the selected node changes.
	sigc::signal< void, ActionOnNode > signal_action_changed;					///< Signal emited when an action is called.

private:
	SelectedNode();

	static vgd::Shp< SelectedNode >						m_selectedNode;	///< Singleton of SelectedNode.

	vgd::WeakPtr< vgd::node::Node >						m_node;			///< Current selected node.
	vgd::WeakPtr< vgd::node::Group >					m_parentNode;	///< Parnet of current selected node.

	vgd::Shp< std::list< vgd::Shp < HiddenNode > > >	m_hiddenNodes; ///< List of hidden nodes.

	vgd::Shp< vgd::node::Node >							m_clipboardNode;///< Current clipboarded node.
	
};

} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_SELECTEDNODE_HPP_*/
