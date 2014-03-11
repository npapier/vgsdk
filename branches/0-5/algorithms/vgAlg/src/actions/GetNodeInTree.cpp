// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/GetNodeInTree.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



GetNodeInTree::GetNodeInTree()
{

}



void GetNodeInTree::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
	
	//During refresh, selection may change, so we reselect current node.
	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( SELECT );
	vgLogStatus( "Node %s selected.", node->getName().c_str() );
}



} // namespace actions

} // namespace vgAlg
