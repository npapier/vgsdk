// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/InvertNormalOrientation.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgAlg/node/VertexShape.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



InvertNormalOrientation::InvertNormalOrientation()
{

}



void InvertNormalOrientation::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	
	vgAlg::node::invertNormalOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



} // namespace actions

} // namespace vgAlg
