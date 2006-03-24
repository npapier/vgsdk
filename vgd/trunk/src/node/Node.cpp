// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Node.hpp"

// #include "vgd/graph/Graph.hpp" FIXME
#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( Node ); abstract class.



Node::~Node() 
{
}



Node::Node( const std::string nodeName ) :
	vgd::basic::Object()
{
	// Add field
	addField( new FNameType(getFName()) );
	
	// Add dirty flag
	addDirtyFlag( getDFNode() );

	// Default value : see setToDefaults().
	setName( nodeName );
		
	// Links
	link( getDFNode() );
}



void Node::setToDefaults( void )
{
	// field name is not like other field, because value is done by factory(no real defaults value).
}



void Node::setOptionalsToDefaults()
{
	// nothing to do
}



void Node::getParents( NodeList& parents ) const
{
	return ( graph().getParents( this, parents ) );
}



int32 Node::getNumParents() const
{
	return ( graph().getNumParents( this ) );
}



void Node::getEnabledParents( NodeList& parents, const bool bGetEnabled ) const
{
	graph().getEnabledParents( this, parents, bGetEnabled );
}



void Node::invalidateParentsBoundingBoxDirtyFlag() 
{
	NodeList parents;
	
	getEnabledParents( parents );
	
	// for each node.
	for(	NodeList::iterator	i	= parents.begin(),
										ie	= parents.end();
			i != ie;
			++i
		)
	{
		// Parent nodes are always group node.
		assert( (*i)->isAKindOf< vgd::node::Group >() );
		
		vgd::Shp< vgd::node::Group > group( vgd::dynamic_pointer_cast< vgd::node::Group >( *i ) );

		group->invalidateBoundingBox();
	}
}



const std::string Node::getName( void ) const
{
	return ( getFieldRO<FNameType>(getFName())->getValue() );
}



void Node::setName( const std::string strNodeName )
{
	getFieldRW<FNameType>(getFName())->setValue( strNodeName );
}



int8 Node::getMultiAttributeIndex() const
{
	return ( 0 );
}



const std::string Node::getFName()
{
	return ( "f_name" );
}



const std::string Node::getDFNode()
{
	return ( "df_node" );
}



vgd::graph::Graph& Node::graph()
{
	// Graph data
	static vgd::graph::Graph m_graph;

	return ( m_graph );
}



vgd::graph::detail::bglGraphTraits::vertex_descriptor& Node::vertexDescriptor( void )
{
	return ( m_vertexDescriptor );
}



const vgd::graph::detail::bglGraphTraits::vertex_descriptor& Node::vertexDescriptor( void ) const
{
	return ( m_vertexDescriptor );
}



vgd::basic::ClassRegistry< vgd::node::Node >& Node::getClassRegistry( void )
{
	static vgd::basic::ClassRegistry< vgd::node::Node > nodeRegistry;

	return ( nodeRegistry );
}



} // namespace node

} // namespace vgd
