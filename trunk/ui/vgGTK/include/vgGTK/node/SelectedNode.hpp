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
	REMOVE
};


struct VGGTK_API SelectedNode
{
	static vgd::Shp< SelectedNode > getSelectedNode();

	void setSelectedNode( vgd::Shp< vgd::node::Node > node );

	void setAction( ActionOnNode action );

	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > getHiddenNodeList();

	sigc::signal< void, vgd::Shp< vgd::node::Node > > signal_selection_changed;
	sigc::signal< void, ActionOnNode > signal_action_changed;

private:
	SelectedNode();

	static vgd::Shp< SelectedNode >			m_selectedNode;

	vgd::Shp< vgd::node::Node >				m_node;

	vgd::Shp< std::list< vgd::Shp < HiddenNode > > >	m_hiddenNodes;
	
};

} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_SELECTEDNODE_HPP_*/
