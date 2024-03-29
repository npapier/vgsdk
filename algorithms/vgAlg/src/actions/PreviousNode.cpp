// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/PreviousNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



PreviousNode::PreviousNode()
{

}



void PreviousNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();		

	if( node && parent )
	{
		int index = parent->findChild( node );

		if ( index > 0 )
		{
			vgd::Shp< vgd::node::Node > prevNode = parent->getAbstractChild( index - 1 );

			parent->replaceChild( node, index - 1 );
			parent->replaceChild( prevNode, index );

			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::MOVE_PREVIOUS );

			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );

			////during refresh, selection change, we have to reselect it.
			//vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
			//vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( SELECT );


		}
	}	
}



} // namespace actions

} // namespace vgAlg
