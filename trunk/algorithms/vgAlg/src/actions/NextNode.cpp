// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/NextNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/Shp.hpp>

#include <vgDebug/convenience.hpp>

namespace vgAlg
{

namespace actions
{



NextNode::NextNode()
{

}



void NextNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();	
	
	if( node && parent )
	{
		int index = parent->findChild( node );

		if ( index < parent->size() -1 )
		{
			vgd::Shp< vgd::node::Node > nextNode = parent->getAbstractChild( index + 1 );
			parent->replaceChild( node, index + 1 );
			parent->replaceChild( nextNode, index );

			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::MOVE_NEXT );

			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );

			//during refresh, selection change, we have to reselect it.
			//vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
			//vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( SELECT );
		}
	}
}



} // namespace actions

} // namespace vgAlg
