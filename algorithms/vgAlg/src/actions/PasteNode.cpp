// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/PasteNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>

#include <vgDebug/convenience.hpp>

namespace vgAlg
{

namespace actions
{



PasteNode::PasteNode()
{

}



void PasteNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();		
	
	vgd::Shp< vgd::node::Node > clipboardedNode = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getClipboardedNode();
	if( clipboardedNode )
	{
		if( node )
		{
			if( node->isAKindOf<vgd::node::Group>() )
			{
				vgd::dynamic_pointer_cast< vgd::node::Group >( node )->addChild( clipboardedNode );
			}
			else if( parent )
			{
				parent->insertChild( clipboardedNode, parent->findChild( node ) );
			}
		}

		vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
	}
}



} // namespace actions

} // namespace vgAlg
