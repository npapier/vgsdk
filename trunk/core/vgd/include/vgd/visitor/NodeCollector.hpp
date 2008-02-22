// VGSDK - Copyright (C) 2004, 2006 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_NODECOLLECTOR_HPP
#define _VGD_VISITOR_NODECOLLECTOR_HPP

#include <vector>

#include "vgd/visitor/Traverse.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief A collector of node.
 * 
 * NodeCollector class traverses a scene graph (like Traverse) and records all encountered nodes in the traverse order.
 *
 * Use this visitor for :
 * 
 * \li finding occurences of a node that satisfies specified conditions ( you can use std::find_if() ).
 * \li applying a functor on a colletion of nodes (with std::for_each() ).
 */
template< typename Visitors = boost::null_visitor >
struct NodeCollector : public Traverse<Visitors>
{
	/**
	 * @name Constructor/Initialization
	 */
	//@{
	
	/**
	 * @brief Default constructor
	 */
	NodeCollector( const bool bUseEdgeName = true, const bool bVisitForest = false ) :
		vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest )
	{
		reset();
	}


	/**
	 * @brief Reset what it should in order to reuse this visitor.
	 */
	void reset()
	{
		m_containerNodes.clear();
	}
	//@}



	/**
	 * @name Accessors
	 */
	//@{
	
	/**
	 * @brief Returns the vector of nodes ordered by traversing order.
	 * 
	 * The first node encountered is at the beginning of the vector.
	 */
	const vgd::node::PNodeList&	getNodes() const { return m_containerNodes; }
	
	//@}



	/**
	 * @name Visitor interface that could be overloaded
	 */
	//@{
	template< typename Vertex , typename Graph >
	void discover_vertex( Vertex u, const Graph& /*g*/ ) /*const*/
	{
		vgd::Shp< vgd::node::Node > node( getNode(u) );
		
		m_containerNodes.push_back( node.get() );
	}
	//@}



protected:


	/**
	 * @name Data
	 */
	//@{
	
	vgd::node::PNodeList		m_containerNodes;

	//@}
};



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_NODECOLLECTOR_HPP
