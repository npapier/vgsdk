// VGSDK - Copyright (C) 2004, 2006 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_TRAVERSE_HPP
#define _VGD_VISITOR_TRAVERSE_HPP

#include "vgd/graph/Graph.hpp"
#include "vgd/node/Group.hpp"
#include "vgd/visitor/Exceptions.hpp"
#include "vgd/visitor/internal/dfs.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief Traverse visitor.
 *
 * vgd::visitor::dfs_visitor<Visitors> is a derived version of dfs.hpp from boost.
 * It is left very similar to the boost version to make futur cvs update easier.
 * The Traverse classe finalize this derivative work.
 */
template< typename Visitors = boost::null_visitor>
struct Traverse : public vgd::visitor::internal::dfs_visitor<Visitors>
{
	/**
	 * @name Constructor/Initialization
	 */
	//@{
	
	/**
	 * @brief Default constructor
	 * 
	 * @remarks This constructor should call reset(), where initialization are done.
	 */
	Traverse( const bool bUseEdgeName = true, const bool bVisitForest = false ) :
		m_bUseEdgeName(	bUseEdgeName ),
		m_bVisitForest(	bVisitForest )
	{
		reset();
	}

	/**
	 * @brief Reset what it should in order to reuse this visitor.
	 * 
	 * @remarks Typically restore initial values of private data used during traversing(like node statistics for
	 * vgd::visitor::Statistics class.
	 */
	void reset()
	{}
	//@}



	/**
	 * name Visitor interface that could be overloaded.
	 */
	//@{
	
//	template< typename Vertex , typename Graph >
//	void discover_vertex( Vertex /*u*/, const Graph& /*g*/ ) const
//	{
//		//vgd::Shp< vgd::node::Node > node = getNode(u);
//		//std::cout << node->getName()  << " ";
//	}
	//@}



	/**
	 * @name Extended traverse accessors
	 */
	//@{
	
	/**
	 * @brief Returns the visit forest flag.
	 */
	bool visitForest() const					{ return m_bVisitForest; }
	
	/**
	 * @brief Sets the visit forest flag.
	 * 
	 * @param bVisitForest true to traverse a set of depth-first trees which together form the depth-first forest, 
	 * false to travese only the first depth-first tree.
	 */
	void visitForest( const bool bVisitForest )	{ m_bVisitForest = bVisitForest; }

	/**
	 * @brief Returns the edge name usage.
	 * 
	 * @return bUseEdgeName false to traverse all children, true to activate the normal behavior of group node(traverse only
	 * selected children).
	 */
	const bool useEdgeName() const				{ return m_bUseEdgeName; }
	
	/**
	 * @brief Sets the edge name usage.
	 * 
	 * @param bUseEdgeName false to traverse all children, true to activate the normal behavior of group node(traverse only
	 * selected children).
	 */
	void useEdgeName(const bool bUseEdgeName )	{ m_bUseEdgeName = bUseEdgeName; }
	//@}



	/**
	 * @name Helpers
	 */
	//@{
	
	/**
	 * @brief Returns node from a vertex.
	 */
	vgd::Shp< vgd::node::Node > getNode( vgd::graph::detail::bglGraphTraits::vertex_descriptor u ) const
	{
		vgd::Shp< vgd::node::Node > node( (*m_vertexNamePropertyMap)[u] );

		return node;
	}

	//@}



	/**
	 * @name Visitor interface
	 * 
	 * @remarks If you don't know exactly what you are doing, never overload it.
	 */

	/**
	 * @brief Enable or disable the visit of target(u).
	 * 
	 * @remarks Never overload it.
	 */
    template <class Edge, class Graph>
    void examine_edge(Edge e, const Graph& /*g*/)
    {
    	if ( useEdgeName() )
    	{
    		vgd::graph::detail::EdgeName edgeName = getEdgeName(e);
    		
    		visitVertex( edgeName.enable() );
    	}
    	/*else do nothing, because it is done once in initialize().
    	{
    		visitVertex( true );
    	}*/
    }



	/**
	 * @brief Called when a cycle is detected.
	 * 
	 * Throw the exception hasCycle().
	 * 
	 * @remarks Never overload it.
	 */
	template< typename Edge, typename Graph >
	void back_edge(Edge /*e*/, const Graph& /*g*/)
	{
		throw HasCycle();
	}
	//@}



	/**
	 * @name Extended traverse accessors
	 */
	//@{
	
	/**
	 * @brief Returns if the current vertex must be visit(see dfs.hpp).
	 */
	const bool visitVertex() const				{ return m_bVisitVertex; }

	/**
	 * @brief Sets if the current vertex must be visit(see dfs.hpp).
	 */
	void visitVertex( const bool bVisitVertex )	{ m_bVisitVertex = bVisitVertex; }
	//@}



	/**
	 * @name Extended helpers.
	 */
	//@{
	/**
	 * @brief Returns edgeName from an edge.
	 */
	vgd::graph::detail::EdgeName getEdgeName( vgd::graph::detail::bglGraphTraits::edge_descriptor e ) const
	{ 
		return (*m_edgeNamePropertyMap)[e];
	}
	//@}


	/**
	 * @brief Prepare the traverse.
	 *
	 * @todo Hide this method or move it to another class GraphGetter() with ShpNode getNode( vert_desc) and getEdge().
	 * @remarks Called by vgd::graph::Graph::traverse()
	 */
	void initialize(	vgd::graph::detail::VertexNamePropertyMap*	vertexNamePropertyMap,
						vgd::graph::detail::EdgeNamePropertyMap*	edgeNamePropertyMap )
	{
		m_vertexNamePropertyMap	= vertexNamePropertyMap;
		m_edgeNamePropertyMap	= edgeNamePropertyMap;
		
		m_bVisitVertex			= true;
	}

private:
	/**
	 * @name Data
	 */
	//@{
	bool	m_bUseEdgeName;
	bool	m_bVisitForest;



	vgd::graph::detail::VertexNamePropertyMap*		m_vertexNamePropertyMap;
	vgd::graph::detail::EdgeNamePropertyMap*		m_edgeNamePropertyMap;

	/**
	 * @brief Temporary value used during traverse.
	 */
	bool	m_bVisitVertex;
	//@}
};



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_TRAVERSE_HPP
