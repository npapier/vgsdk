// VGSDK - Copyright (C) 2004, 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/graph/Graph.hpp"

#include <boost/graph/graphviz.hpp>

#include "vgd/node/Node.hpp"



namespace vgd
{

namespace graph
{

namespace
{
	/**
	 * @name Definitions for graphwiz.
	 */
	//@{
	
	template <class Name>
	class my_vertex_label_writer 
	{
	public:
		my_vertex_label_writer(Name name) : m_name(name) 
		{}
	
		template <class VertexOrEdge>
		void operator()(std::ostream& out, const VertexOrEdge& v) const 
		{
			vgd::Shp< vgd::node::Node > node( m_name[v].lock() );
			
			if ( node )
			{
				out << "[label=\"" << typeid(*node.get()).name() << ", " << node->getName() << "\"]";
			}
			else
			{
				out << "[label=\"expired node\"]";
			}
		}

	private:
		Name m_name;
	};
	
	template <class Name>
	inline my_vertex_label_writer<Name>
	my_make_vertex_label_writer(Name n) 
	{
		return my_vertex_label_writer<Name>(n);
	}
	
	
	
	template <class Name>
	class my_edge_label_writer 
	{
	public:
		my_edge_label_writer(Name name) : m_name(name) 
		{}
	
		template <class VertexOrEdge>
		void operator()(std::ostream& out, const VertexOrEdge& v) const 
		{
			out << "[label=\"" << m_name[v].value() << ", ";
			if ( m_name[v].enable() )
			{
				out << "e";
			}
			else
			{
				out << "d";
			}
			out << "\"]";
		}
	private:
		Name m_name;
	};
	
	template <class Name>
	inline my_edge_label_writer<Name>
	my_make_edge_label_writer(Name n) 
	{
		return my_edge_label_writer<Name>(n);
	}
	//@}
}



// **************** Graph ****************

Graph::Graph()
://	m_graph
	m_vertexNamePropertyMap(	get(boost::vertex_name, bglGraph())	),
	m_edgeNamePropertyMap(		get(boost::edge_name,	bglGraph())	)
	//m_freeVertexDescriptors
{}



void Graph::addNode( vgd::Shp< vgd::node::Node > node )
{
	// Creates the vertex property
	vgd::WeakPtr<vgd::node::Node> wkpNode( node );
	
	// Is there a vertex to recycle ?
	if ( m_freeVertexDescriptors.empty() )
	{
		// No vertex to recycle, creates a new one
		node->vertexDescriptor() = add_vertex( detail::VertexProperty(wkpNode), bglGraph() );
	}
	else
	{
		// Recycles a vertex
		
		// Retrives the vertex descriptor to recycle (and remove it from the container of free vertex descriptors).
		vertex_descriptor vertexDescriptor = m_freeVertexDescriptors.front();
		m_freeVertexDescriptors.pop_front();
		
		// Initializes node vertex descriptor
		node->vertexDescriptor() = vertexDescriptor;

		// Initializes vertex property map
		getVertexNamePropertyMap()[vertexDescriptor] = wkpNode;
	}
}



/**
 * @remarks Remove all out edges for this node.
 * 
 * @todo The vertex set of the graph could never decreased, because the class Graph NEVER removes any vertex.
 */
void Graph::removeNode( vgd::node::Node* pNode )
{
	// std::string name = pNode->getName();

	// Removes all edges from vertex descriptor of the given node.
	bgl_removeAllOutEdges( pNode->vertexDescriptor() );

	// Appends the node vertex descriptor to the list of free ones.
	m_freeVertexDescriptors.push_back( pNode->vertexDescriptor() );

	// Cleans the vertex property map.
	getVertexNamePropertyMap()[pNode->vertexDescriptor()].reset();
}



void Graph::addEdge( vgd::node::Node* pSourceNode, vgd::Shp< vgd::node::Node > targetNode )
{
	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );

	const int32 edgeNameValue = static_cast<int32>( out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	add_edge(	pSourceNode->vertexDescriptor(), targetNode->vertexDescriptor(),
				detail::EdgeProperty( detail::EdgeName(targetNode, edgeNameValue) ),
				bglGraph() );

	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );
}



void Graph::addEdge( vgd::node::Node* pSourceNode, vgd::Shp< vgd::node::Node > targetNode, const uint32 edgeNameValue )
{
	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );
	assert(	edgeNameValue == 0 ||
			(edgeNameValue > 0 && edgeNameValue < out_degree( pSourceNode->vertexDescriptor(), bglGraph() ))	);
	
	bgl_makePlaceInOutEdges( pSourceNode->vertexDescriptor(), edgeNameValue );

	add_edge(	pSourceNode->vertexDescriptor(), targetNode->vertexDescriptor(),
				detail::EdgeProperty(detail::EdgeName(targetNode, edgeNameValue) ),
				bglGraph() );

	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );
}



void Graph::removeEdge( vgd::node::Node* pSourceNode, const uint32 edgeNameValue, const bool bRepack )
{
	// assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) ); not necessary.
	assert( edgeNameValue < out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	std::pair< vertex_descriptor, bool > retVal;
	retVal = bgl_removeOutEdge( pSourceNode->vertexDescriptor(), edgeNameValue, bRepack );
	assert( retVal.second );
}



void Graph::removeEdges( vgd::node::Node* pSourceNode )
{
	bgl_removeAllOutEdges( pSourceNode->vertexDescriptor() );
}



vgd::Shp<vgd::node::Node> Graph::getChild( const vgd::node::Node* pSourceNode, const uint32 edgeNameValue ) const
{
	assert( edgeNameValue < out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	std::pair< edge_descriptor, bool > retVal;
	retVal = bgl_findOutEdgeWithEdgeName( pSourceNode->vertexDescriptor(), edgeNameValue );
	assert( retVal.second );
	
	vgd::Shp<vgd::node::Node> node = getEdgeNamePropertyMap()[ retVal.first ].child();

	return node;
}



void Graph::getChildren( const vgd::node::Node* pSourceNode, vgd::node::NodeList& outChildren ) const
{
	assert( bgl_isOutEdgesPacked(pSourceNode->vertexDescriptor()) && "OutEdges not packed" );

	const detail::EdgeNamePropertyMap& edgeNamePM = getEdgeNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator	out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		vgd::Shp<vgd::node::Node> child = edgeNamePM[ *out_i ].child();
		
		outChildren.push_back( child );
	}
}



void Graph::getEnabledChildren(	const vgd::node::Node* pSourceNode, vgd::node::NodeList& outChildren, 
								const bool bGetEnabled ) const
{
	const detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator	out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		const detail::EdgeName& edgeName = edgeNamePM[ *out_i ];
		
		if ( edgeName.enable() == bGetEnabled )
		{
			vgd::Shp<vgd::node::Node> child = edgeName.child();
			outChildren.push_back( child );
		}
	}
}



const uint32 Graph::getNumChildren( const vgd::node::Node* pSourceNode ) const
{
	const uint32 retVal = static_cast<uint32>( out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	return retVal;
}



void Graph::getParents( const vgd::node::Node* pTargetNode,	vgd::node::NodeList& outParents ) const
{
	const detail::VertexNamePropertyMap&	vertexNamePM = getVertexNamePropertyMap();

	detail::bglGraphTraits::in_edge_iterator	in_i, in_end;
	for(	tie(in_i, in_end) = in_edges(pTargetNode->vertexDescriptor(), bglGraph());
			in_i != in_end;
			++in_i )
	{
		vertex_descriptor vdSource = source(*in_i, bglGraph());
		
		vgd::Shp<vgd::node::Node> parent( vertexNamePM[vdSource] );

		outParents.push_back( parent );
	}
}



void Graph::getEnabledParents(	const vgd::node::Node* pTargetNode, vgd::node::NodeList& outParents, 
								const bool bGetEnabled ) const
{
	const detail::VertexNamePropertyMap&	vertexNamePM	= getVertexNamePropertyMap();
	const detail::EdgeNamePropertyMap&		edgeNamePM		= getEdgeNamePropertyMap();

	detail::bglGraphTraits::in_edge_iterator		in_i, in_end;
	for(	tie(in_i, in_end) = in_edges(pTargetNode->vertexDescriptor(), bglGraph());
			in_i != in_end;
			++in_i )
	{
		const detail::EdgeName& edgeName = edgeNamePM[ *in_i ];
		
		if ( edgeName.enable() == bGetEnabled )
		{
			vertex_descriptor vdSource = source(*in_i, bglGraph());

			vgd::Shp< vgd::node::Node > parent( vertexNamePM[vdSource] );
			outParents.push_back( parent );
		}
	}
}



const uint32 Graph::getNumParents( const vgd::node::Node* pTargetNode ) const
{
	const uint32 retVal = static_cast<uint32>( in_degree( pTargetNode->vertexDescriptor(), bglGraph() ) );

	return retVal;
}



void Graph::setEdges( const vgd::node::Node* pSourceNode, const bool isEnable )
{
	const detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator		out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		edgeNamePM[ *out_i ].enable() = isEnable;
	}
}



void Graph::setEdges( const vgd::node::Node* pSourceNode, const std::set< int32 >& setEdgeNameValue, const bool bToEnable )
{
	const detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator	out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		const int32 edgeNameValue = edgeNamePM[ *out_i ].value();
		if ( setEdgeNameValue.find( edgeNameValue ) != setEdgeNameValue.end() )
		{
			// Founded current edge name value in setEdgeNameValue => set it to bToEnable.
			edgeNamePM[ *out_i ].enable() = bToEnable;
		}
		else
		{
			// Not founded
			edgeNamePM[ *out_i ].enable() = !bToEnable;
		}
	}
}



void Graph::setEdgesNegate( const vgd::node::Node* pSourceNode )
{
	const detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator		out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		edgeNamePM[ *out_i ].negate();
	}
}



const bool Graph::containsChild( const vgd::node::Node* pSourceNode, const vgd::node::Node* pNodeToFind )
{
	std::pair< edge_descriptor, bool > retValFind = 
		bgl_findOutEdge( pSourceNode->vertexDescriptor(), pNodeToFind->vertexDescriptor() );
		
	return ( retValFind.second );
}



const int32 Graph::findChild( const vgd::node::Node* pSourceNode, const vgd::node::Node* pNodeToFind )
{
	assert( bgl_isOutEdgesPacked(pSourceNode->vertexDescriptor()) && "OutEdges not packed" );

	std::pair< edge_descriptor, bool > retValFind = 
		bgl_findOutEdge( pSourceNode->vertexDescriptor(), pNodeToFind->vertexDescriptor() );
		
	if ( retValFind.second )
	{
		const detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();

		return ( edgeNamePM[ retValFind.first ].value() );
	}
	
	return ( getNumChildren(pSourceNode) );
}



void Graph::writeGraphviz( const vgd::node::Node* pSourceNode, std::ostream& out ) /*const*/
{
	boost::write_graphviz(out , bglGraph(),
		my_make_vertex_label_writer(getVertexNamePropertyMap()),
		my_make_edge_label_writer(getEdgeNamePropertyMap()) );
}



detail::bglGraph& Graph::bglGraph()
{
	return m_graph;
}



const detail::bglGraph&	Graph::bglGraph() const 
{
	return m_graph;
}



const bool Graph::bgl_isOutEdgesPacked( vertex_descriptor vertexDescriptor ) const
{
	int32										i32I;
	detail::bglGraphTraits::out_edge_iterator	out_i;
	detail::bglGraphTraits::out_edge_iterator	out_end;

	const detail::EdgeNamePropertyMap&			edgeNamePM = getEdgeNamePropertyMap();

	for (	i32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, i32I++)
	{
		if ( edgeNamePM[ *out_i ].value() != i32I )
		{
			return false;
		}
	}
	
	return true;
}



void Graph::bgl_packOutEdges( vertex_descriptor vertexDescriptor )
{
	assert( !bgl_isOutEdgesPacked(vertexDescriptor) && "already packed");

	uint32										ui32I;
	detail::bglGraphTraits::out_edge_iterator	out_i;
	detail::bglGraphTraits::out_edge_iterator	out_end;

	detail::EdgeNamePropertyMap&			edgeNamePM = getEdgeNamePropertyMap();

	for(	ui32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, ui32I++ )
	{
		edgeNamePM[ *out_i ].value() = ui32I;
	}
}



void Graph::bgl_makePlaceInOutEdges( vertex_descriptor vertexDescriptor, const uint32 edgeNameValue )
{
	assert( bgl_isOutEdgesPacked(vertexDescriptor) && "OutEdges not packed" );
	assert(	edgeNameValue == 0 ||
			(edgeNameValue > 0 && edgeNameValue < out_degree(vertexDescriptor, bglGraph()))	);

	uint32										ui32I;
	detail::bglGraphTraits::out_edge_iterator	out_i;
	detail::bglGraphTraits::out_edge_iterator	out_end;

	for(	ui32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, ui32I++ )
	{
		if ( ui32I == edgeNameValue )
		{
			break;
		}
	}

	assert(	(out_i != out_end && "edgeNameValue not found") ||
			(out_i == out_end && (ui32I == 0) && (edgeNameValue == 0)) );

	detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();
	while ( out_i != out_end )
	{
		edgeNamePM[ *out_i ].value() += 1;
		++out_i; // ui32I++
	}
}



/**
 * @todo FIXME use remove_out_edge_if(), but it does'nt work on Linux.
 */
void Graph::bgl_removeAllOutEdges( vertex_descriptor vertexDescriptor )
{
	// Work fine on windows, but don't compile on LINUX. Strange...
	//	true_edge_predicate<edge_descriptor> predicate;
	//	remove_out_edge_if(vertexDescriptor, predicate, bglGraph());
	
	//
	typedef std::list< vertex_descriptor > ListVD;

	ListVD											children;
	detail::bglGraphTraits::out_edge_iterator		out_i, out_end;

	// collect children vertex descriptor.
	for(	tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i )
	{
		vertex_descriptor vdTarget;
		
		vdTarget = target( *out_i, bglGraph() );
		
		children.push_back( vdTarget );
	}
	
	// remove edges
	ListVD::iterator list_i, list_end;
	
	for(	list_i		= children.begin(),
			list_end	= children.end();
			
			list_i != list_end;
			
			++list_i)
	{
		vertex_descriptor vdTarget;
		vdTarget = *list_i;
		
		remove_edge( vertexDescriptor, vdTarget, bglGraph() );
	}
}



std::pair< Graph::vertex_descriptor, bool > 
Graph::bgl_removeOutEdge( vertex_descriptor vertexDescriptor, const uint32 edgeNameValue, const bool bAutoRepack )
{
	assert( edgeNameValue < out_degree(vertexDescriptor, bglGraph()) );

	std::pair< vertex_descriptor, bool >	retVal;
	retVal.second = false;

	uint32											ui32I;
	detail::bglGraphTraits::out_edge_iterator		out_i;
	detail::bglGraphTraits::out_edge_iterator		out_end;

	for(	ui32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, ++ui32I )
	{
		if ( ui32I == edgeNameValue )
		{
			// found out_edge to remove.
			retVal.first	= target( *out_i, bglGraph() ); // vertex descriptor of child.
			retVal.second	= true;
			
			detail::bglGraphTraits::out_edge_iterator		out_toRemove( out_i );
			
			// 
			if ( bAutoRepack )
			{
				detail::EdgeNamePropertyMap&	edgeNamePM = getEdgeNamePropertyMap();
			
				for(	++out_i;
						out_i != out_end;
						++out_i/*, ui32I++*/ )
				{
					edgeNamePM[ *out_i ].value() -= 1;
				}
				
				// remove out_edge
				remove_edge( out_toRemove, bglGraph() );				
				
				assert( bgl_isOutEdgesPacked(vertexDescriptor) && "OutEdges not packed" );				
			}
			else
			{
				// remove out_edge
				remove_edge( out_toRemove, bglGraph() );
			}
			break;
		}
	}

	return retVal;
}



//FIXME bool Graph::bgl_removeOutEdge( vertex_descriptor vertexDescriptorSource, vertex_descriptor vertexDescriptorTarget )
//{
//	std::pair< edge_descriptor, bool >		outedge;
//	outedge = bgl_findOutEdge( vertexDescriptorSource, vertexDescriptorTarget );
//	
//	if ( outedge.second )
//	{
//		// find out-edge.
//		remove_edge( retVal.first, bglGraph() );
//		return ( true );
//	}
//	else
//	{
//		return ( false );
//	}
//}



std::pair< Graph::edge_descriptor, bool >
Graph::bgl_findOutEdgeWithEdgeName( vertex_descriptor vertexDescriptor, const uint32 edgeNameValue ) const
{
	assert( edgeNameValue < out_degree(vertexDescriptor, bglGraph()) );

	std::pair< Graph::edge_descriptor, bool >	retVal;
	retVal.second = false;

	uint32										ui32I;
	detail::bglGraphTraits::out_edge_iterator	out_i;
	detail::bglGraphTraits::out_edge_iterator	out_end;

	for(	ui32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, ui32I++ )
	{
		if ( ui32I == edgeNameValue )
		{
			retVal.first	= *out_i;
			retVal.second	= true;
			
			return retVal;
		}
	}
	
	return retVal;
}



std::pair< Graph::edge_descriptor, bool > 
Graph::bgl_findOutEdge( vertex_descriptor vertexDescriptorSource, vertex_descriptor vertexDescriptorTarget ) const
{
	std::pair< Graph::edge_descriptor, bool >	retVal;
	retVal.second = false;

	detail::bglGraphTraits::out_edge_iterator		out_i;
	detail::bglGraphTraits::out_edge_iterator		out_end;

	for(	tie(out_i, out_end) = out_edges(vertexDescriptorSource, bglGraph());
			out_i != out_end;
			++out_i )
	{
		if ( target(*out_i, bglGraph()) == vertexDescriptorTarget )
		{
			// Found vertexDescritorTarget => found outEdge.
			retVal.first	= *out_i;
			retVal.second	= true;
			
			return retVal;
		}
	}
	
	return retVal;
}



detail::VertexNamePropertyMap& Graph::getVertexNamePropertyMap()
{
	return m_vertexNamePropertyMap;
}



const detail::VertexNamePropertyMap& Graph::getVertexNamePropertyMap() const
{
	return m_vertexNamePropertyMap;
}



detail::EdgeNamePropertyMap& Graph::getEdgeNamePropertyMap()
{
	return m_edgeNamePropertyMap;
}



const detail::EdgeNamePropertyMap& Graph::getEdgeNamePropertyMap() const
{
	return m_edgeNamePropertyMap;
}



} // namespace graph

} // namespace vgd
