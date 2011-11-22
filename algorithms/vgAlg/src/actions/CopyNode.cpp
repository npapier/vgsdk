// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/CopyNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



CopyNode::CopyNode()
{

}



void CopyNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();
	
	if( node && parent )
	{
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->setClipboardedNode( node );
	}
}



} // namespace actions

} // namespace vgAlg
