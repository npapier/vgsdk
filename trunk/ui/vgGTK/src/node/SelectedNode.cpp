// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/SelectedNode.hpp"

namespace vgGTK
{

namespace node
{

vgd::Shp< SelectedNode > SelectedNode::m_selectedNode;



vgd::Shp< SelectedNode > SelectedNode::getSelectedNodeObject()
{
	if(!m_selectedNode)
	{
		m_selectedNode = vgd::Shp< SelectedNode >( new SelectedNode );
	}
	
	return m_selectedNode;
}



SelectedNode::SelectedNode()
{
	m_hiddenNodes = vgd::makeShp( new std::list< vgd::Shp < HiddenNode > > );
}



void SelectedNode::setSelectedNode( vgd::Shp< vgd::node::Node > node,  vgd::Shp< vgd::node::Group > parent )
{
	m_node = node;
	m_parentNode = parent;
	//signal_selection_changed.emit( node );
}



vgd::Shp< vgd::node::Node > SelectedNode::getSelectedNode()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	return node;
}



vgd::Shp< vgd::node::Group > SelectedNode::getParentSelectedNode()
{
	vgd::Shp< vgd::node::Group > parent = m_parentNode.lock();
	return parent;
}



void SelectedNode::setAction( ActionOnNode action )
{
	signal_action_changed.emit( action );
}



vgd::Shp< std::list< vgd::Shp < HiddenNode > > > SelectedNode::getHiddenNodeList()
{
	return m_hiddenNodes;
}



void SelectedNode::setClipboardedNode( vgd::Shp< vgd::node::Node > node )
{
	m_clipboardNode = node;
}



vgd::Shp< vgd::node::Node > SelectedNode::getClipboardedNode()
{
	return m_clipboardNode;
}



} // namespace node

} // namespace vgGTK

