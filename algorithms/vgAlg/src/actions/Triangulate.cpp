// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/Triangulate.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgAlg/node/VertexShape.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/Shp.hpp>

#include <vgDebug/convenience.hpp>

namespace vgAlg
{

namespace actions
{



Triangulate::Triangulate()
{

}



void Triangulate::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	
	if( node->isA< vgd::node::VertexShape >() )
	{
		vgAlg::node::triangulate( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
	}
}



} // namespace actions

} // namespace vgAlg
