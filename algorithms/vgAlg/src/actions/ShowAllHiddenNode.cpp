// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/ShowAllHiddenNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>
#include <vgAlg/actions/ShowNode.hpp>

#include <vgd/node/Node.hpp>

#include <vgDebug/convenience.hpp>

namespace vgAlg
{

namespace actions
{



ShowAllHiddenNode::ShowAllHiddenNode()
{

}



void ShowAllHiddenNode::execute()
{
	vgd::Shp < vgAlg::actions::HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp< vgAlg::actions::HiddenNode > > > hiddenNodes = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getHiddenNodeList();	
	std::list< vgd::Shp< vgAlg::actions::HiddenNode > >::iterator it = hiddenNodes->begin();
	for( it; it !=  hiddenNodes->end(); )
	{
		hidden = (*it);
		it++;
		ShowNode showNode;
		showNode.setHiddenNode( hidden );
		showNode.execute();
	}
}



} // namespace actions

} // namespace vgAlg
