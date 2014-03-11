// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/ExpandSubTree.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



ExpandSubTree::ExpandSubTree()
{

}



void ExpandSubTree::execute()
{
	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::EXPAND );
}



} // namespace actions

} // namespace vgAlg
