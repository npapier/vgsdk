// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_FIND_HPP
#define _VGD_VISITOR_FIND_HPP

#include "vgd/node/Group.hpp"
#include "vgd/visitor/predicate/IPredicate.hpp"
#include "vgd/visitor/Traverse.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief A visitor for finding node(s) in a scene graph.
 * 
 * This class traverses a scene graph (like Traverse) and search nodes that causes the predicate to return true.
 * 
 * Take a look at vgd::visitor::predicate namespace if you want to create your custom predicate.
 *
 * \code
 * // Usage with method vgd::node::Group::traverse()
 * vgd::visitor::predicate::ByName predicate("lightSwitcher");
 * vgd::visitor::Find< vgd::visitor::predicate::ByName > find( predicate );
 * m_root->traverse( find );
 * const vgd::node::NodeList& result = find.getNodes();
 * 
 * // Usage with helper method vgd::visitor::find()
 * vgd::Shp< vgd::node::NodeList > result;
 * result = vgd::visitor::find( m_root, vgd::visitor::predicate::ByName("lightSwitcher") );
 * \endcode
 */
template< class Predicate, typename Visitors = boost::null_visitor  >
struct Find : public Traverse<Visitors>
{
	/**
	 * @name Constructor/Initialization
	 */
	//@{
	
	/**
	 * @brief Default constructor
	 */
	Find( const Predicate& predicate, bool bUseEdgeName = true, bool bVisitForest = false ) :
			vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest ),
			m_trueNodes( new vgd::node::NodeList )
	{
		addPredicate( predicate.clone() );
		reset();
	}

	/**
	 * @brief Reset what it should in order to reuse this visitor
	 */
	void reset()
	{
		m_trueNodes->clear();
	}
	//@}



	/**
	 * @name Accessors
	 */
	//@{
	
	/**
	 * @brief Returns the vector of nodes ordered by traversing order that cause the predicate to return true.
	 * 
	 * The first node encountered is at the beginning of the vector.
	 */
	const vgd::node::NodeList&	getNodes() const { return ( m_trueNodes.get() ); }

	/**
	 * @brief Returns the vector of nodes ordered by traversing order that cause the predicate to return true.
	 * 
	 * The first node encountered is at the beginning of the vector.
	 */
	vgd::Shp< vgd::node::NodeList >	getShpNodes() { return ( m_trueNodes ); }
	//@}
	

	void addPredicate( vgd::Shp< vgd::visitor::predicate::IPredicate > pred )
	{
		m_vPredicate.push_back( pred );
	}


	/**
	 * @name Visitor interface that could be overloaded
	 */
	//@{
	template< typename Vertex , typename Graph >
	void discover_vertex( Vertex u, const Graph& /*g*/ ) /*const*/
	{
		vgd::Shp< vgd::node::Node > node = getNode(u);

		for( uint i = 0; i < m_vPredicate.size(); i++)
		{
			if ( (*m_vPredicate[i])( node ) == false )
			{
				return;
			}
		}

		m_trueNodes->push_back( node );
	}
	//@}



private:

	/**
	 * @name Data
	 */
	//@{

	vgd::Shp< vgd::node::NodeList >		m_trueNodes;
	
	std::vector< vgd::Shp< vgd::visitor::predicate::IPredicate > > m_vPredicate;
	//@}
};



/**
 * @brief Traverse the graph starting on the specified node with the specified visitor to find node that returns true to 
 * the predicate.
 * 
 * @remark This method is an helper to simplify usage of traverse() with vgd::visitor::Find.
 * @deprecated
 */
template< class Predicate >
vgd::Shp< vgd::node::NodeList > findDEPRECATED( vgd::Shp< vgd::node::Group > group, const Predicate& predicate )
{
	vgd::visitor::Find< Predicate >	find( predicate );

	group->traverse( find );
	
	return ( find.getShpNodes() );
}



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_FIND_HPP
