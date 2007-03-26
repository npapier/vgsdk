// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_FINDFIRST_HPP
#define _VGD_VISITOR_FINDFIRST_HPP

#include <utility>

#include "vgd/node/Group.hpp"
#include "vgd/visitor/Traverse.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief A visitor for finding node(s) in a scene graph.
 * 
 * This class traverses a scene graph (like Traverse) and search the first node that causes the predicate to return true.
 * 
 * Take a look at vgd::visitor::predicate namespace if you want to create your custom predicate.
 *
 * \code
 * // Usage with method vgd::node::Group::traverse()
 * vgd::visitor::predicate::ByName predicate("lightSwitcher");
 * vgd::visitor::FindFirst< vgd::visitor::predicate::ByName > find( predicate );
 * m_root->traverse( find );
 * vgd::Shp< vgd::node::Node > result = find.getShpNode();
 * 
 * // Usage with helper method vgd::visitor::findFirst()
 * std::pair< bool, vgd::Shp< vgd::node::Node > > result;
 * result = vgd::visitor::findFirst( m_root, vgd::visitor::predicate::ByName("lightSwitcher") );
 * if ( result.first )
 * {
 * 	// Found
 * 	// use result.second
 * }
 * else
 * {
 * 	// Not found
 * }
 * \endcode
 */
template< class Predicate, typename Visitors = boost::null_visitor  >
struct FindFirst : public Traverse<Visitors>
{
	/**
	 * @name Constructor/Initialization
	 */
	//@{
	
	/**
	 * @brief Default constructor
	 */
	FindFirst( const Predicate& predicate, bool bUseEdgeName = true, bool bVisitForest = false ) :
			vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest ),
			m_predicate( predicate )
	{
		reset();
	}

	/**
	 * @brief Reset what it should in order to reuse this visitor.
	 */
	void reset()
	{
		m_node.reset();
	}
	//@}



	/**
	 * @name Accessors
	 */
	//@{
	
	/**
	 * @brief Returns node that cause the predicate to return true.
	 */
	vgd::Shp< vgd::node::Node >	getShpNode() { return ( m_node ); }
	//@}
	

	
	/**
	 * @name Visitor interface that could be overloaded
	 */
	//@{
	template< typename Vertex , typename Graph >
	void discover_vertex( Vertex u, const Graph& /*g*/ ) /*const*/
	{
		vgd::Shp< vgd::node::Node > node = getNode(u);

		if ( m_predicate( node ) )
		{
			m_node = node;
			
			throw DesiredStop();
		}
	}
	//@}



private:

	/**
	 * @name Data
	 */
	//@{

	vgd::Shp< vgd::node::Node >	m_node;
	
	const Predicate&					m_predicate;
	//@}
};



/**
 * @brief Traverse the graph starting on the specified node with the specified visitor to find the first node that 
 * returns true to the predicate.
 * 
 * @remark This method is an helper to simplify usage of traverse() with vgd::visitor::FindFirst.
 */
template< class Predicate >
std::pair< bool, vgd::Shp< vgd::node::Node > > findFirst( vgd::Shp< vgd::node::Group > group, const Predicate& predicate )
{
	vgd::visitor::FindFirst< Predicate >	find( predicate );
	
	bool	bFounded = false;

	try
	{
		group->traverse( find );
	}
	catch ( vgd::visitor::DesiredStop )
	{
		// ok, found the first node.
		bFounded = true;
	}

	return ( std::pair< bool, vgd::Shp< vgd::node::Node > >( bFounded, find.getShpNode() ) );
}



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_FINDFIRST_HPP
