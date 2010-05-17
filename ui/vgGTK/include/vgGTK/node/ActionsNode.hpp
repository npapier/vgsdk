// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_ACTIONSNODE_HPP_
#define _VGGTK_NODE_ACTIONSNODE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgd/Shp.hpp>
#include <vgd/WeakPtr.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgGTK/node/HiddenNode.hpp>
#include <vgGTK/node/InsertNode.hpp>

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
struct VGGTK_API ActionsNode
{	
	ActionsNode();

	~ActionsNode();

	void setCanvas( vgUI::Canvas * canvas );

	void onGetNodeInTree();							///< Handles the action that will select the node in the treeview.
	void onExpandSubTree();							///< Handles the action that will expand all the tree view sub-tree of the selection element.
	void onRemoveNode();							///< Handles the action that will remove the selected node from it parent.

	void onPreviousNode();							///< Handles the action that will move up the node.	
	void onNextNode();								///< Handles the action that will move down the node.	
	void onCutNode();								///< Handles the action that will cut the node.	
	void onCopyNode();								///< Handles the action that will copy the node.	
	void onPasteNode();								///< Handles the action that will paste the node.	
	
	void onHideNode();								///< Handles the action that will hide the selected node.
	void onShowNode(vgd::Shp < HiddenNode > hidden);///< Handles the action that will show the selected node.
	void onShowAllHiddenNode();						///< Handles the action that will show all hidden node.
	void onHideAll();								///< Handles the action that will hide all node.
	void onHideAllExceptSelected();					///< Handles the action that will hide all node execept selected node.
	void onExportNode();							///< Handles the action that will export the selected node.
	void onSetToDefault();							///< Handles the action that will set node filed to default.
	void onSetOptionalToDefault();					///< Handles the action that will set the optional node field to default.
	void onInvertTriangleOrientation();				///< Handles the action that will invert triangles orientation.
	void onInvertNormalOrientation();				///< Handles the action that will invert nsls orientation.
	void onApplyGeometricalTransformation();		///< Handles the action that will apply geometrical transformaiton directly on shapes.

	bool isAlreadyHidden( vgd::Shp< vgd::node::Node > node );	///< Return true if the node is actually displayed or hidden.
	int getDisplayedNodeNumber();								///< Return the number of node which are displayed.

	void setCurrentNode( vgd::Shp< vgd::node::Node > node, vgd::Shp< vgd::node::Group > parentNode );

private:

	vgd::WeakPtr< vgd::node::Node >		m_currentNode;			///< current selected node.
	vgd::WeakPtr< vgd::node::Group >	m_currentParentNode;	///< current parent of selected node.
	vgUI::Canvas						*m_canvas;				///< canvas of the application
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_ACTIONSNODE_HPP_*/

