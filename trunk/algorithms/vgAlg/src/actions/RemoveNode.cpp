// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/RemoveNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>

#include <vgDebug/convenience.hpp>

namespace vgAlg
{

namespace actions
{



RemoveNode::RemoveNode()
{

}



void RemoveNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();		
	
	if( node )
	{
		// vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
		// vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::SELECT );
		// vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REMOVE );
		
		parent->removeChild( node );
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
		vgDebug::get().logStatus( "Node %s removed.", node->getName().c_str() );
	}
}



} // namespace actions

} // namespace vgAlg
