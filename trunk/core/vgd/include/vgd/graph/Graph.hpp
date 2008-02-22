// VGSDK - Copyright (C) 2004, 2006 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_GRAPH_GRAPH_HPP
#define _VGD_GRAPH_GRAPH_HPP

#include <iostream>

#include "vgd/vgd.hpp"
#include "vgd/graph/detail/Graph.hpp"
#include "vgd/visitor/Exceptions.hpp"
#include "vgd/visitor/internal/dfs.hpp"

namespace vgd
{
	namespace node
	{
		struct Node;
		typedef std::list< vgd::Shp<vgd::node::Node> > NodeList;
	}
}



/** 
 * @namespace vgd::graph
 * 
 * @brief Scene graph implementation.
 * 
 * All scene graphs are stored in a unique graph. It can be manipulating with classes written in graph namespace and
 * traverse by classes founded in visitor namespace.
 */
namespace vgd
{

namespace graph
{

/**
 * @brief Graph interface.
 * 
 * Useful for global management of all scene graphes.
 *
 * @remarks \b DefaultConstructible and not Assignable.
 * 
 * @todo getEdges().
 * @todo Optimize graph manipulation and bench it(bench of property map, lazzy edgename packing).
 */
struct VGD_API Graph
{
	/**
	 * @name Constructor
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	Graph();
	//@}
	
	
	
	/**
	 * @name Operations on graph
	 */
	//@{

	/**
	 * @brief Adds a new vertex for the node.
	 * 
	 * @remarks Initialize vertex descriptor of the node.
	 */
	void addNode( vgd::Shp< vgd::node::Node > node );

	/**
	 * @brief Removes the vertex of a node.
	 */
	void	removeNode( vgd::node::Node* pNode );


	/**
	 * @brief Adds a new edge from source to target node.
	 *
	 * @remarks This edge is append to the end of the parent edge container.
	 */
	void	addEdge( vgd::node::Node* pSourceNode, vgd::Shp< vgd::node::Node > targetNode );

	/**
	 * @brief Adds a new edge from source to target node.
	 * 
	 * @remarks This edge is append to the edgeNameValue index of the parent edge container.
	 */
	void	addEdge( vgd::node::Node* pSourceNode, vgd::Shp< vgd::node::Node > targetNode, const uint32 edgeNameValue );


	/**
	 * @brief Removes an edge from pSourceNode to target node label by edgeNameValue.
	 * 
	 * @param bRepack	if sets to true, edge labels are repacked.
	 */
	void	removeEdge( vgd::node::Node* pSourceNode, const uint32 edgeNameValue, const bool bRepack  );

	/**
	 * @brief Removes all edges from pSourceNode.
	 */
	void	removeEdges( vgd::node::Node* pSourceNode );
	//@}
	
	
	
	/**
	 * @name Children accessors
	 */
	//@{

	/**
	 * @brief Returns the specified child node.
	 */	
	vgd::Shp<vgd::node::Node>	getChild( const vgd::node::Node* pSourceNode, const uint32 edgeNameValue ) const;

	/**
	 * @brief Returns all children of a node.
	 * 
	 * @param pSourceNode	parent of the children.
	 * @param outChildren	all children found for pSourceNode(append to the end)
	 */
	void getChildren( const vgd::node::Node* pSourceNode, vgd::node::NodeList& outChildren ) const;

	/**
	 * @brief Returns all enabled or disabled children of a node.
	 * 
	 * @param pSourceNode	parent of the children.
	 * @param outChildren	all children found for pSourceNode(append to the end).
	 * @param bGetEnabled	true to get all enabled children, false to get all disabled children.
	 */
	void getEnabledChildren(	const vgd::node::Node* pSourceNode, vgd::node::NodeList& outChildren,
								const bool bGetEnabled = true ) const;

	/**
	 * @brief Returns number of children.
	 *
	 * @param pSourceNode	parent of the children.
	 * @return the number of children.
	 */
	const uint32	getNumChildren( const vgd::node::Node* pSourceNode ) const;
	//@}
	
	
	
	/**
	 * @name Parents accessors
	 */
	//@{

	/**
	 * @brief Returns parents of a node.
	 *
	 * @param pTargetNode	node
	 * @param outParents	all parents founded for pTargetNode(append to the end).
	 */
	void	getParents( const vgd::node::Node* pTargetNode, vgd::node::NodeList& outParents ) const;

	/**
	 * @brief Returns all enabled or disabled parents of a node.
	 * 
	 * @param pTargetNode	node
	 * @param outParents	all parents found for pTargetNode(append to the end).
	 * @param bGetEnabled	true to get all enabled parents, false to get all disabled parents.
	 */
	void	getEnabledParents(	const vgd::node::Node* pTargetNode, vgd::node::NodeList& outParents,
								const bool bGetEnabled = true ) const;

	/**
	 * @brief Returns number of parents.
	 *
	 * @param pTargetNode	node
	 * @return the number of parents
	 */
	const uint32	getNumParents( const vgd::node::Node* pTargetNode ) const;
	//@}
	
	
	
	/**
	 * @name Edges accessors
	 */
	//@{

	/**
	 * @brief Enables/disables edge name state used during the traversing.
	 * 
	 * @param pSourceNode	parent of the children
	 * @param isEnable		true to enable the traverse of all children, false to disable the traverse of all children
	 */
	void setEdges( const vgd::node::Node* pSourceNode, const bool isEnable );

	/**
	 * @brief Enables/disables edge name state used during the traversing.
	 * 
	 * @param pSourceNode 		parent of the children
	 * @param setEdgeNameValue	set of edge name value(see EdgeName class)
	 * @param bToEnable			all edge name founded in the setEdgeNameValue are set to bToEnable, 
	 * 							others are set to (not bToEnable).
	 */
	 void setEdges( const vgd::node::Node* pSourceNode, const std::set< int32 >& setEdgeNameValue, const bool bToEnable );

	/**
	 * @brief Negate the edge name state used during the traversing.
	 * 
	 * @param pSourceNode	parent of the children
	 */
	void setEdgesNegate( const vgd::node::Node* pSourceNode );
	//@}



	/**
	 * @name Find accessors
	 */
	//@{
	
	/**
	 * @brief Search a specified node in children list of a node(pSourceNode).
	 * 
	 * @param pSourceNode	starting point of the searching.
	 * @param pNodeToFind	node to find.
	 * @return true if founded, false otherwise.
	 */
	const bool containsChild( const vgd::node::Node* pSourceNode, const vgd::node::Node* pNodeToFind );

	/**
	 * @brief Search a specified node in children list of a node(pSourceNode).
	 * 
	 * @param pSourceNode	starting point of the searching
	 * @param pNodeToFind	node to find
	 * @return a value between 0 and getNumChildren()-1 if found, if not found then return getNumChildren().
	 */
	const int32 findChild( const vgd::node::Node* pSourceNode, const vgd::node::Node* pNodeToFind );
	//@}



	/**
	 * @brief Alias on vertex descriptor.
	 */
	typedef detail::bglGraphTraits::vertex_descriptor	vertex_descriptor;
	
	/**
	 * @brief Alias on edge descriptor.
	 */
	typedef detail::bglGraphTraits::edge_descriptor		edge_descriptor;



	/**
	 * @name Traverse/Evaluate scene graph
	 */
	//@{
	
	/**
	 * @brief Performs a traverse (like a depth first visit).
	 * 
	 * @todo Manage exceptions (like hasCycle()).
	 */
	template< typename DFSVisitor >
	void traverse( vertex_descriptor startingNode, DFSVisitor& visitor )
	{
//		try
//		{
			// Colors
			// @todo Could be optimize (don't reallocate this vector for each traverse call).
			std::vector< boost::default_color_type > colors( num_vertices(bglGraph()) );
			const boost::default_color_type c = boost::white_color;
			
			// Index Map
			typedef boost::property_map<detail::bglGraph, boost::vertex_index_t>::type IndexMap;
			IndexMap indexmap = boost::get(boost::vertex_index, bglGraph());

			// Initialize visitor
			visitor.initialize(	&getVertexNamePropertyMap(), &getEdgeNamePropertyMap() );
	
			// Depth first search
			vgd::visitor::internal::depth_first_search(
				bglGraph(),
				visitor,
	
				make_iterator_property_map(
					colors.begin(),
					indexmap,
					c ),
		
				startingNode
			 );
//		}
//		catch (vgd::visitor::HasCycle e)
//		{
//			throw e;
			// FIXME
			//return ( true );
//		}
	}

	//@}



	/**
	 * @name Debugging methods
	 */
	//@{
	
	/**
	 * @brief Write the scene graph in \c Graphviz format.
	 * 
	 * This is to write a BGL graph(scene graph) object into a output stream in graphviz dot format so that users can make 
	 * use of AT&T graphviz to draw a picture with nice layout.
	 * 
	 * @todo Use pSourceNode.
	 */
	void	writeGraphviz( const vgd::node::Node* pSourceNode, std::ostream& out = std::cout ) /*const*/;
	//@}
	
	
	
protected:
	/**
	 * @name Some useful methods for manipulating bgl graph
	 */
	//@{

	/**
	 * @brief Accessor to graph.
	 */
	detail::bglGraph&			bglGraph();
	
	/**
	 * @brief Accessor to graph.
	 */
	const detail::bglGraph&		bglGraph() const;

	/**
	 * @brief Test if out_edges().value() of vertexDescriptor are a sequence (i.e. edgeName[i].value() = i for i>=0 && i<getNumChildren()).
	 */
	const bool bgl_isOutEdgesPacked	( vertex_descriptor vertexDescriptor ) const;

	/**
	 * @brief Pack out_edges().value() of vertexDescriptor(i.e. edgeName[i].value() = i for i>=0 && i<getNumChildren()).
	 */
	void	bgl_packOutEdges( vertex_descriptor vertexDescriptor );

	/**
	 * @brief Increase by one all out_edges().value() for childs of vertexDescriptor with edgeName.value() >= edgeNameValue.
	 */
	void	bgl_makePlaceInOutEdges	( vertex_descriptor vertexDescriptor, const uint32 edgeNameValue );

	/**
	 * @brief Removes all out-edges from vertex descriptor of the given node.
	 */
	void	bgl_removeAllOutEdges( vertex_descriptor vertexDescriptor );

	/**
	 * @brief Remove the out-edge with source specified by vertex descriptor and the \c edgeName label.
	 * 
	 * Edge labels are repacked if bAutoRepack is true.
	 */
	std::pair< vertex_descriptor, bool > bgl_removeOutEdge(	vertex_descriptor vertexDescriptor,
															const uint32 edgeNameValue, const bool bAutoRepack = false );

//	/**
//	 * brief Remove the out-edge from source to target vertex descriptors(specified by vertex descriptor).
//	 * 
//	 * todo add const bool bAutoRepack = false option.
//	 */
//	bool	bgl_removeOutEdge( vertex_descriptor vertexDescriptorSource, vertex_descriptor vertexDescriptorTarget );
// FIXME
	//@}



	/**
	 * @name Searching methods on bgl graph
	 */
	//@{

	/**
	 * @brief Find the out-edge from specified source vertex descriptor with the \c edgeName label.
	 */
	std::pair< edge_descriptor, bool >	bgl_findOutEdgeWithEdgeName( vertex_descriptor source, const uint32 edgeNameValue ) const;

	/**
	 * @brief Find the out-edge from specified source to target vertex descriptors.
	 */
	std::pair< edge_descriptor, bool >	bgl_findOutEdge( vertex_descriptor source, vertex_descriptor target ) const;
	//@}



	/**
	 * @name Accessor to property maps
	 */
	//@{
	
	/**
	 * @brief Accessor to property map for vertex name.
	 */
	detail::VertexNamePropertyMap&			getVertexNamePropertyMap();

	/**
	 * @brief Accessor to property map for vertex name.
	 */
	const detail::VertexNamePropertyMap&	getVertexNamePropertyMap() const;
		
	/**
	 * @brief Accessor to property map for edge name.
	 */
	detail::EdgeNamePropertyMap&			getEdgeNamePropertyMap();

	/**
	 * @brief Accessor to property map for edge name.
	 */
	const detail::EdgeNamePropertyMap&		getEdgeNamePropertyMap() const;
	//@}



private:
	/**
	 * @name Data
	 */
	//@{
	detail::bglGraph				m_graph;
	
	detail::VertexNamePropertyMap	m_vertexNamePropertyMap;
	detail::EdgeNamePropertyMap		m_edgeNamePropertyMap;

	/**
	 * @brief Type definition for container of vertex descriptors.
	 */
	typedef std::list< vertex_descriptor >	VertexDescriptorListType;
	
	/**
	 * @brief Container of vertex descriptors no more associated to a node (because the node has been deleted).
	 */
	VertexDescriptorListType		m_freeVertexDescriptors;

	//@}

	/**
	 * @brief True predicate used by removeOutEdges().
	 */
	template <typename edge_descriptor>
	struct true_edge_predicate 
	{
		const bool operator()( const edge_descriptor& e ) const 
		{
			return true;
		}
	};
};



} // namespace graph
	
} // namespace vgd

#endif //#ifndef _VGD_GRAPH_GRAPH_HPP
