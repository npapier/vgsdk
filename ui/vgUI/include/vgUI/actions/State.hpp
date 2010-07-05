// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGUI_ACTIONS_STATE_HPP
#define _VGUI_ACTIONS_STATE_HPP


#include "vgUI/vgUI.hpp"

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

namespace vgUI
{

namespace actions
{

enum LOCATION
{
	TREE,
	CANVAS
};

/**
 * @brief	The UI State class containing all visibility pertinent attributs.
 */
struct VGUI_API State
{
	State();

	int getNumberOfNode();
	void setNumberOfNode( int number );

	int getNumberOfDisplayedNode();
	void setNumberOfDisplayedNode( int number );

	bool isRoot();
	void isRoot( bool b );

	vgd::Shp< vgd::node::Node > getSelectedNode();
	void setSelectedNode( vgd::Shp< vgd::node::Node > node );

	bool hasAClipboardedNode();
	void hasAClipboardedNode( bool b );

	LOCATION getLocation();
	void setLocation( LOCATION location );

	vgd::Shp< vgd::node::Group > getParent();
	void setParent( vgd::Shp< vgd::node::Group > parent );

	bool isShape();
	void isShape( bool b );

	bool isGroup();
	void isGroup( bool b );

	bool isHidden();
	void isHidden( bool b );

	int getNumberOfHiddenNode();
	void setNumberOfHiddenNode( int number );

private:
	int								m_numberOfNode;				///< Number of node in the scene.
	int								m_numberOfDisplayedNode;	///< Number of node displayed in the scene.
	bool							m_isRoot;					///< Is current node the root node.
	vgd::Shp< vgd::node::Node >		m_selectedNode;				///< The current node.
	bool							m_hasAClipboardedNode;		///< Is a node clipboarded.
	LOCATION						m_location;					///< Location of the action.
	vgd::Shp< vgd::node::Group >	m_parentNode;				///< Parent node of the current node.
	bool							m_isShape;					///< Is the current node a shape.
	bool							m_isGroup;					///< Is the current node a group.
	bool							m_isHidden;					///< Is the current node hidden.
	int								m_numberOfHiddenNode;		///< Number of hidden node in the scene.
};

} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_STATE_HPP
