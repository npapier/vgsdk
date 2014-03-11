// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/ShowNode.hpp"

#include <vgAlg/actions/ShowNode.hpp>


namespace vgUI
{

namespace actions
{



ShowNode::ShowNode( ) :
IActionUI( "Visibility/Hidden node/nodeName", "nodeName", "ShowNode_nodeName", DEFAULT, "", new vgAlg::actions::ShowNode() )
{
}


ShowNode::ShowNode( vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode ) :
IActionUI( "Visibility/Hidden node/" + hiddenNode->getNode()->getName(), hiddenNode->getNode()->getName(), "ShowNode_" + hiddenNode->getNode()->getName(), DEFAULT, "", new vgAlg::actions::ShowNode( hiddenNode ) ),
m_hiddenNode( hiddenNode )
{
}



const bool ShowNode::isValide( State state )
{
	vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode = m_hiddenNode.lock();
	if( hiddenNode )
	{
		return true;
	}
	else
	{
		return false;
	}
}



} // namespace actions

} // namespace vgUI
