// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Node.hpp"

#include "vgd/node/Group.hpp"
#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( Node ); abstract class.




Node::~Node() 
{
	// Updates boost::graph
	graph().removeNode( this );
	
	// Signal invocation
	m_destructorSignal(this);
}



Node::Node( const std::string nodeName )
:	vgd::basic::Object()
{
	// Adds field
	addField( new FNameType(getFName()) );
	
	// Adds dirty flag
	addDirtyFlag( getDFNode() );

	// Default value : see setToDefaults().
	setName( nodeName );
		
	// Links
	link( getDFNode() );
}



/**
 * @todo Implements it
 */
Node::Node( const vgd::node::Node& )
{
	assert( false );
}



/**
 * @todo Implements it
 */
vgd::node::Node& Node::operator =( const vgd::node::Node& )
{
	assert( false );
		
	return *this;
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



Node::ConnectionType Node::connect( SignalDestructorType::slot_function_type slot )
{
	return m_destructorSignal.connect( slot );
}



vgd::graph::Graph& Node::graph()
{
	// Graph data
	static vgd::graph::Graph m_graph;

	return m_graph;
}



vgd::node::Node::vertex_descriptor& Node::vertexDescriptor()
{
	return m_vertexDescriptor;
}



const vgd::node::Node::vertex_descriptor& Node::vertexDescriptor() const
{
	return m_vertexDescriptor;
}



vgd::basic::ClassRegistry< vgd::node::Node >& Node::getClassRegistry( void )
{
	static vgd::basic::ClassRegistry< vgd::node::Node > nodeRegistry;

	return nodeRegistry;
}



} // namespace node

} // namespace vgd
