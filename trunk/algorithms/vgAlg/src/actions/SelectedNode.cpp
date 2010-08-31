// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#include "vgAlg/actions/SelectedNode.hpp"

namespace vgAlg
{

namespace actions
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
: m_hiddenNodes( vgd::makeShp( new HiddenNodeList() ) )
{}



void SelectedNode::setSelectedNode( vgd::Shp< vgd::node::Node > node,  vgd::Shp< vgd::node::Group > parent )
{
	m_node = node;
	m_parentNode = parent;
	signal_selection_changed();
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
	signal_action_changed( action );
}



vgd::Shp< std::list< vgd::Shp< HiddenNode > > > SelectedNode::getHiddenNodeList()
{
	HiddenNodeList::iterator it		= m_hiddenNodes->begin();
	HiddenNodeList::iterator itEnd	= m_hiddenNodes->end();

	while( it != itEnd )
	{
		vgd::Shp< HiddenNode > hiddenNode = (*it);

		if ( hiddenNode->getNode() == 0 )
		{
			it = m_hiddenNodes->erase( it );
			continue;
		}

		++it;
	}

	return m_hiddenNodes;
}



const bool SelectedNode::isAlreadyHidden( vgd::Shp< vgd::node::Node > node ) const
{
	bool retVal = false;
	
	HiddenNodeList::iterator it		= m_hiddenNodes->begin();
	HiddenNodeList::iterator itEnd	= m_hiddenNodes->end();
	
	while( it != itEnd)
	{
		vgd::Shp< HiddenNode > hidden( *it );

		if( hidden->getNode() == node )
		{
			return true;
		}

		++it;
	}

	return retVal;
}



void SelectedNode::setClipboardedNode( vgd::Shp< vgd::node::Node > node )
{
	m_clipboardNode = node;
}



vgd::Shp< vgd::node::Node > SelectedNode::getClipboardedNode()
{
	return m_clipboardNode;
}



} // namespace actions

} // namespace vgAlg

