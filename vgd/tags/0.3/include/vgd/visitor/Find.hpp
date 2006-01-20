// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_FIND_H
#define _VGD_VISITOR_FIND_H

#include "vgd/vgd.hpp"

#include "vgd/node/Group.hpp"
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
	 * @name Constructor/Initialization.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	Find( const Predicate& predicate, bool bUseEdgeName = true, bool bVisitForest = false ) :
			vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest ),
			m_predicate( predicate ),
			m_trueNodes( new vgd::node::NodeList )
	{
		reset();
	}

	/**
	 * @brief Reset what it should in order to reuse this visitor.
	 * 
	 * @param numOfNodesHint : hint to specify the number of nodes that this visitor should encountered.
	 * This permits to reserve a minimum length of storage for the container of visited node in order to reduce reallocation.
	 */
	void	reset	( const int32 numOfNodesHint = 512 )
	{
		m_trueNodes->clear();
	}
	//@}



	/**
	 * @name Accessors.
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
	

	
	/**
	 * @name Visitor interface that could be overloaded.
	 */
	//@{
	template< typename Vertex , typename Graph >
	void discover_vertex( Vertex u, const Graph& g ) /*const*/
	{
		vgd::Shp< vgd::node::Node > node = getNode(u);

		if ( m_predicate( node ) )
		{
			m_trueNodes->push_back( node );
		}
	}
	//@}



private:

	/**
	 * @name Data.
	 */
	//@{

	vgd::Shp< vgd::node::NodeList >		m_trueNodes;
	
	const Predicate&							m_predicate;
	//@}
};



/**
 * @brief Traverse the graph starting on the specified node with the specified visitor to find node that returns true to 
 * the predicate.
 * 
 * @remark This method is an helper to simplify usage of traverse() with vgd::visitor::Find.
 */
template< class Predicate >
vgd::Shp< vgd::node::NodeList > find( vgd::Shp< vgd::node::Group > group, const Predicate& predicate )
{
	vgd::visitor::Find< Predicate >	find( predicate );

	group->traverse( find );
	
	return ( find.getShpNodes() );
}



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_FIND_H
