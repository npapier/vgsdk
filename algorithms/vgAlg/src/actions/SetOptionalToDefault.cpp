// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/SetOptionalToDefault.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



SetOptionalToDefault::SetOptionalToDefault()
{

}



void SetOptionalToDefault::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	
	node->setOptionalsToDefaults();

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



} // namespace actions

} // namespace vgAlg
