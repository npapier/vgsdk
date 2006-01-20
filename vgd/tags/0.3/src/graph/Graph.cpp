// VGSDK - Copyright (C) 2004, IRCAD.
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



Graph::Graph( void ) :
//	m_graph
	m_vertexNamePropertyMap(	get(boost::vertex_name, bglGraph())	),
	m_edgeNamePropertyMap(		get(boost::edge_name,	bglGraph())	)
{
}



void Graph::addNode( vgd::Shp<vgd::node::Node> node )
{
	node->vertexDescriptor() = add_vertex( detail::VertexProperty(node), bglGraph() );
}



void Graph::removeNode( vgd::node::Node* pNode )
{
	clear_vertex( pNode->vertexDescriptor(), bglGraph() );
	// remove_vertex( pNode->vertexDescriptor(), bglGraph() ); FIXME ???
}



void Graph::addEdge( vgd::node::Node* pSourceNode, vgd::node::Node* pTargetNode )
{
	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );

	int32 edgeNameValue = static_cast<int32>( out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	add_edge(	pSourceNode->vertexDescriptor(), pTargetNode->vertexDescriptor(),
					detail::EdgeProperty(detail::EdgeName(edgeNameValue)), bglGraph() );

	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );
}



void Graph::addEdge( vgd::node::Node* pSourceNode, vgd::node::Node* pTargetNode, const uint32 edgeNameValue )
{
	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );
	assert(	edgeNameValue == 0 ||
				(edgeNameValue > 0 && edgeNameValue < out_degree( pSourceNode->vertexDescriptor(), bglGraph() ))
				);
	
	bgl_makePlaceInOutEdges( pSourceNode->vertexDescriptor(), edgeNameValue );

	add_edge(	pSourceNode->vertexDescriptor(), pTargetNode->vertexDescriptor(),
				detail::EdgeProperty(detail::EdgeName(edgeNameValue)), bglGraph() );

	assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) );
}



void Graph::removeEdge( vgd::node::Node* pSourceNode, const uint32 edgeNameValue, const bool bRepack )
{
	// assert( bgl_isOutEdgesPacked( pSourceNode->vertexDescriptor() ) ); not necessary.
	assert( edgeNameValue < out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	std::pair< detail::bglGraphTraits::vertex_descriptor, bool > retVal;
	retVal = bgl_removeOutEdge( pSourceNode->vertexDescriptor(), edgeNameValue, bRepack );
	assert( retVal.second );
}



void Graph::removeEdges( vgd::node::Node* pSourceNode )
{
	// Work fine on windows, but don't compile on LINUX. Strange...
	//	true_edge_predicate<bglGraphTraits::edge_descriptor> predicate;
	//	remove_out_edge_if(pSourceNode->vertexDescriptor(), predicate, bglGraph());
	
	//
	typedef std::list< detail::bglGraphTraits::vertex_descriptor > ListVD;

	ListVD													children;
	detail::bglGraphTraits::out_edge_iterator		out_i, out_end;

	// collect children vertex descriptor.
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		detail::bglGraphTraits::vertex_descriptor vdTarget;
		
		vdTarget = target( *out_i, bglGraph() );
		
		children.push_back( vdTarget );
	}
	
	// remove edges
	ListVD::iterator list_i, list_end;
	
	for(	list_i		= children.begin(),
			list_end		= children.end();
			
			list_i != list_end;
			
			++list_i)
	{
		detail::bglGraphTraits::vertex_descriptor vdTarget;
		vdTarget = *list_i;
		
		remove_edge( pSourceNode->vertexDescriptor(), vdTarget, bglGraph() );
	}
}



vgd::Shp<vgd::node::Node> Graph::getChild( const vgd::node::Node* pSourceNode, const uint32 edgeNameValue ) const
{
	assert( edgeNameValue < out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	std::pair< detail::bglGraphTraits::edge_descriptor, bool > retVal;
	retVal = bgl_findOutEdgeWithEdgeName( pSourceNode->vertexDescriptor(), edgeNameValue );
	assert( retVal.second );
	
	detail::bglGraphTraits::vertex_descriptor vdTarget = target(retVal.first, bglGraph());
	
	vgd::Shp<vgd::node::Node> node = getVertexNamePropertyMap()[vdTarget];
	return ( node );
}



void Graph::getChildren( const vgd::node::Node* pSourceNode, std::list< vgd::Shp<vgd::node::Node> >& outChildren ) const
{
	assert( bgl_isOutEdgesPacked(pSourceNode->vertexDescriptor()) && "OutEdges not packed" );

	const detail::VertexNamePropertyMap&	vertexNamePM = getVertexNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator		out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		detail::bglGraphTraits::vertex_descriptor vdTarget = target(*out_i, bglGraph());
		
		outChildren.push_back( vertexNamePM[vdTarget] );
	}
}



void Graph::getEnabledChildren(	const vgd::node::Node* pSourceNode, std::list< vgd::Shp<vgd::node::Node> >& outChildren,
											const bool bGetEnabled ) const
{
	const detail::VertexNamePropertyMap&	vertexNamePM	= getVertexNamePropertyMap();
	const detail::EdgeNamePropertyMap&		edgeNamePM		= getEdgeNamePropertyMap();

	detail::bglGraphTraits::out_edge_iterator		out_i, out_end;
	for(	tie(out_i, out_end) = out_edges(pSourceNode->vertexDescriptor(), bglGraph());
			out_i != out_end;
			++out_i )
	{
		bool bIsEnabled;
		bIsEnabled = edgeNamePM[ *out_i ].enable();
		
		if ( bIsEnabled == bGetEnabled )
		{
			detail::bglGraphTraits::vertex_descriptor vdTarget = target(*out_i, bglGraph());
			outChildren.push_back( vertexNamePM[vdTarget] );
		}
	}
}



const uint32 Graph::getNumChildren( const vgd::node::Node* pSourceNode ) const
{
	const uint32 retVal = static_cast<uint32>( out_degree( pSourceNode->vertexDescriptor(), bglGraph() ) );

	return ( retVal );
}



void Graph::getParents( const vgd::node::Node* pTargetNode,	std::list< vgd::Shp<vgd::node::Node> >& outParents ) const
{
	const detail::VertexNamePropertyMap&	vertexNamePM = getVertexNamePropertyMap();

	detail::bglGraphTraits::in_edge_iterator		in_i, in_end;
	for(	tie(in_i, in_end) = in_edges(pTargetNode->vertexDescriptor(), bglGraph());
			in_i != in_end;
			++in_i )
	{
		detail::bglGraphTraits::vertex_descriptor vdSource = source(*in_i, bglGraph());

		outParents.push_back( vertexNamePM[vdSource] );
	}
}



void Graph::getEnabledParents(	const vgd::node::Node* pTargetNode,
											std::list< vgd::Shp<vgd::node::Node> >& outParents,
											const bool bGetEnabled ) const
{
	const detail::VertexNamePropertyMap&	vertexNamePM	= getVertexNamePropertyMap();
	const detail::EdgeNamePropertyMap&		edgeNamePM		= getEdgeNamePropertyMap();

	detail::bglGraphTraits::in_edge_iterator		in_i, in_end;
	for(	tie(in_i, in_end) = in_edges(pTargetNode->vertexDescriptor(), bglGraph());
			in_i != in_end;
			++in_i )
	{
		bool bIsEnabled;
		bIsEnabled = edgeNamePM[ *in_i ].enable();
		
		if ( bIsEnabled == bGetEnabled )
		{
			detail::bglGraphTraits::vertex_descriptor vdSource = source(*in_i, bglGraph());
			outParents.push_back( vertexNamePM[vdSource] );
		}
	}
}



const uint32 Graph::getNumParents( const vgd::node::Node* pTargetNode ) const
{
	const uint32 retVal = static_cast<uint32>( in_degree( pTargetNode->vertexDescriptor(), bglGraph() ) );

	return ( retVal );
}



void Graph::setEdges( const vgd::node::Node* pSourceNode, bool isEnable )
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



void Graph::setEdges( const vgd::node::Node* pSourceNode, const std::set< int32 >& setEdgeNameValue, bool bToEnable )
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



bool Graph::containsChild( const vgd::node::Node* pSourceNode, const vgd::node::Node* pNodeToFind )
{
	std::pair< detail::bglGraphTraits::edge_descriptor, bool > retValFind = 
		bgl_findOutEdge( pSourceNode->vertexDescriptor(), pNodeToFind->vertexDescriptor() );
		
	return ( retValFind.second );
}



int32 Graph::findChild( const vgd::node::Node* pSourceNode, const vgd::node::Node* pNodeToFind )
{
	assert( bgl_isOutEdgesPacked(pSourceNode->vertexDescriptor()) && "OutEdges not packed" );

	std::pair< detail::bglGraphTraits::edge_descriptor, bool > retValFind = 
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



detail::bglGraph&	Graph::bglGraph( void )
{
	return ( m_graph );
}



const detail::bglGraph&	Graph::bglGraph( void ) const 
{
	return ( m_graph );
}



bool Graph::bgl_isOutEdgesPacked( detail::bglGraphTraits::vertex_descriptor vertexDescriptor ) const
{
	int32													i32I;
	detail::bglGraphTraits::out_edge_iterator	out_i;
	detail::bglGraphTraits::out_edge_iterator	out_end;

	const detail::EdgeNamePropertyMap&			edgeNamePM = getEdgeNamePropertyMap();

	for (	i32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, i32I++)
	{
		if ( edgeNamePM[ *out_i ].value() != i32I )
		{
			return ( false );
		}
	}
	
	return ( true );
}



void Graph::bgl_packOutEdges( detail::bglGraphTraits::vertex_descriptor vertexDescriptor )
{
	assert( !bgl_isOutEdgesPacked(vertexDescriptor) && "already packed");

	uint32												ui32I;
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



void Graph::bgl_makePlaceInOutEdges	( detail::bglGraphTraits::vertex_descriptor vertexDescriptor, 
	const uint32 edgeNameValue )
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



std::pair< detail::bglGraphTraits::vertex_descriptor, bool > Graph::bgl_removeOutEdge(
	detail::bglGraphTraits::vertex_descriptor vertexDescriptor, 
	const uint32 edgeNameValue, const bool bAutoRepack )
{
	assert( edgeNameValue < out_degree(vertexDescriptor, bglGraph()) );

	std::pair< detail::bglGraphTraits::vertex_descriptor, bool >	retVal;
	retVal.second = false;

	uint32													ui32I;
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
				remove_edge( *out_toRemove, bglGraph() );
			}
			break;
		}
	}

	return ( retVal );
}



/* FIXME bool Graph::bgl_removeOutEdge(
	detail::bglGraphTraits::vertex_descriptor vertexDescriptorSource,
	detail::bglGraphTraits::vertex_descriptor vertexDescriptorTarget )
{
	std::pair< detail::bglGraphTraits::edge_descriptor, bool >		outedge;
	outedge = bgl_findOutEdge( vertexDescriptorSource, vertexDescriptorTarget );
	
	if ( outedge.second )
	{
		// find out-edge.
		remove_edge( retVal.first, bglGraph() );
		return ( true );
	}
	else
	{
		return ( false );
	}
}*/



std::pair< detail::bglGraphTraits::edge_descriptor, bool > Graph::bgl_findOutEdgeWithEdgeName(
	detail::bglGraphTraits::vertex_descriptor vertexDescriptor, const uint32 edgeNameValue ) const
{
	assert( edgeNameValue < out_degree(vertexDescriptor, bglGraph()) );

	std::pair< detail::bglGraphTraits::edge_descriptor, bool >	retVal;
	retVal.second = false;

	uint32									ui32I;
	detail::bglGraphTraits::out_edge_iterator		out_i;
	detail::bglGraphTraits::out_edge_iterator		out_end;

	for(	ui32I = 0, tie(out_i, out_end) = out_edges(vertexDescriptor, bglGraph());
			out_i != out_end;
			++out_i, ui32I++ )
	{
		if ( ui32I == edgeNameValue )
		{
			retVal.first	= *out_i;
			retVal.second	= true;
			
			return ( retVal );
		}
	}
	
	return ( retVal );
}



std::pair< detail::bglGraphTraits::edge_descriptor, bool > Graph::bgl_findOutEdge(
	detail::bglGraphTraits::vertex_descriptor vertexDescriptorSource,
	detail::bglGraphTraits::vertex_descriptor vertexDescriptorTarget ) const
{
	std::pair< detail::bglGraphTraits::edge_descriptor, bool >	retVal;
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
			
			return ( retVal );
		}
	}
	
	return ( retVal );
}



} // namespace graph

} // namespace vgd
