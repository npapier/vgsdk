// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/HideNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>



namespace vgAlg
{

namespace actions
{



HideNode::HideNode()
{

}



void HideNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();

	if( vgAlg::actions::SelectedNode::getSelectedNodeObject()->isAlreadyHidden( node ) )
	{
		return; //node is already hidden.
	}

	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node );

	vgd::Shp < vgAlg::actions::HiddenNode > hidden = vgd::makeShp( new vgAlg::actions::HiddenNode(vertexShape) );
	vgAlg::actions::SelectedNode::getSelectedNodeObject()->getHiddenNodeList()->push_back( hidden );
	hidden->hide();

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );

	vgLogStatus( "Node %s hidden.", node->getName().c_str() );
}



} // namespace actions

} // namespace vgAlg
