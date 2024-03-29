// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/HideAllExceptSelectedNode.hpp"

#include <vgAlg/actions/HideNode.hpp>
#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgd/visitor/predicate/ByKindOfType.hpp>
#include <vgd/visitor/helpers.hpp>



namespace vgAlg
{

namespace actions
{



HideAllExceptSelectedNode::HideAllExceptSelectedNode()
{
}



void HideAllExceptSelectedNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	
	vgAlg::actions::HideNode hideNode;

	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_root, predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator it = result->begin();
	for( it; it !=  result->end(); it++ )
	{
		if ( node != (*it) )
		{
			hideNode.setNode( (*it) );
			hideNode.execute();
		}
	}
}



} // namespace actions

} // namespace vgAlg
