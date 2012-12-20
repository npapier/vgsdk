// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgAlg/actions/NormalizeNormals.hpp"

#include <vgAlg/actions/SelectedNode.hpp>
#include <vgAlg/node/VertexShape.hpp>



namespace vgAlg
{

namespace actions
{



NormalizeNormals::NormalizeNormals()
{}



void NormalizeNormals::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();

	using vgd::node::VertexShape;
	if( node->isA< VertexShape >() )
	{
		vgAlg::node::normalizeNormals( vgd::dynamic_pointer_cast< VertexShape >( node ) );
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
	}
}



} // namespace actions

} // namespace vgAlg
