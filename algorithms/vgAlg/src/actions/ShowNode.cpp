// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/ShowNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>
#include <vgAlg/actions/HiddenNode.hpp>

#include <vgd/node/Node.hpp>

#include <vgDebug/convenience.hpp>

namespace vgAlg
{

namespace actions
{



ShowNode::ShowNode()
{

}



ShowNode::ShowNode( vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode )
{
	m_hiddenNode = hiddenNode;
}



void ShowNode::execute()
{
	vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode = m_hiddenNode.lock();
	hiddenNode->restorePrimitives();

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->getHiddenNodeList()->remove( hiddenNode );

	if( hiddenNode->getNode() )
	{
		vgDebug::get().logStatus( "Node %s restored.", hiddenNode->getNode()->getName().c_str() );
	}

	hiddenNode.reset();

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



} // namespace actions

} // namespace vgAlg
