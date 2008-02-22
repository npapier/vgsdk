// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_SORT_HPP
#define _VGD_VISITOR_SORT_HPP

#include <utility>

#include "vgd/node/Group.hpp"
//#include "vgd/node/Node.hpp"
#include "vgd/visitor/Traverse.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief A visitor for finding node(s) in a scene graph.
 * 
 * This class traverses a scene graph (like Traverse) and search nodes that causes the predicate to return true.
 * All encountered nodes are classified in two sets. One that stored all nodes that causes the predicate to return and
 * the others.
 * 
 * Take a look at vgd::visitor::predicate namespace if you want to create your custom predicate.
 * @sa vgd::visitor::Find.
 * 
 * \code
 * // Usage with method vgd::node::Group::traverse()
 * TODO
 * 
 * // Usage with helper method vgd::visitor::sort()
 * vgd::Shp< vgd::node::NodeList > resultT, resultF;
 * boost::tie( resultT, resultF ) = vgd::visitor::sort( m_root, vgd::visitor::predicate::ByName("lightSwitcher") );
 * lightSwitcher = vgd::dynamic_pointer_cast< vgd::node::Switch >( *(resultT->begin()) );
 * \endcode
 */
template< class Predicate, typename Visitors = boost::null_visitor  >
struct Sort : public Traverse<Visitors>
{
	/**
	 * @name Constructor/Initialization.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	Sort( const Predicate& predicate, bool bUseEdgeName = true, bool bVisitForest = false ) :
			vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest ),
			m_predicate( predicate ),
			m_trueNodes( new vgd::node::NodeList ),
			m_falseNodes( new vgd::node::NodeList )
	{
		reset();
	}

	/**
	 * @brief Resets what it should in order to reuse this visitor.
	 */
	void reset()
	{
		m_trueNodes->clear();
		m_falseNodes->clear();
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
	const vgd::node::NodeList&	getTrueNodes() const { return m_trueNodes.get(); }
	
	/**
	 * @brief Returns the vector of nodes ordered by traversing order that cause the predicate to return false.
	 * 
	 * The first node encountered is at the beginning of the vector.
	 */
	const vgd::node::NodeList&	getFalseNodes() const { return m_falseNodes.get(); }
	
	/**
	 * @brief Returns the vector of nodes ordered by traversing order that cause the predicate to return true.
	 * 
	 * The first node encountered is at the beginning of the vector.
	 */
	vgd::Shp< vgd::node::NodeList >	getShpTrueNodes() { return m_trueNodes; }
	
	/**
	 * @brief Returns the vector of nodes ordered by traversing order that cause the predicate to return false.
	 * 
	 * The first node encountered is at the beginning of the vector.
	 */
	vgd::Shp< vgd::node::NodeList >	getShpFalseNodes() { return m_falseNodes; }	
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
			m_trueNodes->push_back( node );
		}
		else
		{
			m_falseNodes->push_back( node );
		}
	}
	//@}



private:

	/**
	 * @name Data
	 */
	//@{

	vgd::Shp< vgd::node::NodeList	>	m_trueNodes;
	vgd::Shp< vgd::node::NodeList >		m_falseNodes;
	
	const Predicate&					m_predicate;
	//@}
};


/**
 * @brief Traverse the graph starting on the specified node with the specified visitor to sort nodes.
 * 
 * @remark This method is an helper to simplify usage of traverse() with vgd::visitor::Sort.
 */
template< class Predicate >
std::pair< vgd::Shp< vgd::node::NodeList >, vgd::Shp< vgd::node::NodeList > >
	sort( vgd::Shp< vgd::node::Group > group, const Predicate& predicate )
{
	vgd::visitor::Sort< Predicate >	sort( predicate );

	group->traverse( sort );
	
	return ( std::pair< vgd::Shp< vgd::node::NodeList >, vgd::Shp< vgd::node::NodeList > >(
					sort.getShpTrueNodes(), sort.getShpFalseNodes() ) );
}



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_SORT_HPP
