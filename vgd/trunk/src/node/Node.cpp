// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Node.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( Node ); abstract class.



Node::~Node( void ) 
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



int32 Node::getNumParents( void ) const
{
	return ( graph().getNumParents( this ) );
}



void Node::getEnabledParents( NodeList& parents, const bool bGetEnabled ) const
{
	graph().getEnabledParents( this, parents, bGetEnabled );
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



const std::string Node::getFName( void )
{
	return ( "f_name" );
}



const std::string Node::getDFNode( void )
{
	return ( "df_node" );
}



vgd::graph::Graph& Node::graph( void )
{
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



vgd::graph::Graph Node::m_graph;



} // namespace node

} // namespace vgd
