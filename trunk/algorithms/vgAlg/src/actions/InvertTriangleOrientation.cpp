// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/InvertTriangleOrientation.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgAlg/node/TriSet.hpp>
#include <vgAlg/node/VertexShape.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/Shp.hpp>



namespace vgAlg
{

namespace actions
{



InvertTriangleOrientation::InvertTriangleOrientation()
{

}



void InvertTriangleOrientation::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	
	if( node->isA< vgd::node::VertexShape >() )
	{
		vgAlg::node::invertPrimitiveOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );
	}
	else if( node->isA< vgd::node::TriSet >() )
	{
		vgAlg::node::invertTriangleOrientation( vgd::dynamic_pointer_cast< vgd::node::TriSet >( node ) );
	}
	else
	{
		vgLogDebug( "Unsupported node type in InvertTriangleOrientation::execute()" );
	}

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



} // namespace actions

} // namespace vgAlg
