// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgAlg/actions/HiddenNode.hpp"


namespace vgAlg
{

namespace actions
{
	

HiddenNode::HiddenNode(vgd::Shp< vgd::node::VertexShape > node ) :
m_node( node )
{
}



HiddenNode::~HiddenNode()
{
	m_node.reset();
}



void HiddenNode::hide()
{
	vgd::Shp< vgd::node::VertexShape > node = m_node.lock();
	if( node )
	{
		vgd::field::EditorRW< vgd::field::MFPrimitive >	editPrimitive = node->getPrimitiveRW();

		for( uint i = 0; i < editPrimitive->size(); i++)
		{
			m_primitives.push_back( editPrimitive->operator[](i) );
		}

		editPrimitive->clear();
	}
}



void HiddenNode::restorePrimitives()
{
	vgd::Shp< vgd::node::VertexShape > node = m_node.lock();
	if( node )
	{		
		vgd::field::EditorRW< vgd::field::MFPrimitive >	editPrimitive = node->getPrimitiveRW();

		editPrimitive->clear();
		
		for( uint i = 0; i < m_primitives.size(); i++)
		{
			editPrimitive->push_back( m_primitives[i] );
		}
	}
}



vgd::Shp< vgd::node::VertexShape > HiddenNode::getNode()
{
	vgd::Shp< vgd::node::VertexShape > node = m_node.lock();
	return node;
}



bool HiddenNode::hasNode()
{
	vgd::Shp< vgd::node::VertexShape > node = m_node.lock();
	if( node )
	{	
		return true;
	}
	else
	{
		return false;
	}
}



} // namespace actions

} // namespace vgAlg

