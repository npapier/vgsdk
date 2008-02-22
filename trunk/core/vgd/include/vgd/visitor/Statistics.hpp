// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_STATISTICS_HPP
#define _VGD_VISITOR_STATISTICS_HPP

#include <fstream>
#include <map>

#include "vgd/visitor/Traverse.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief Statistics visitor.
 * 
 * The Statistics visitor collect some informations during a traverse of a scene graph :
 * 
 * \li The different node types encountered.
 * \li The number of each different node types encountered.
 * \li The total number of nodes.
 */
template< typename Visitors = boost::null_visitor >
struct Statistics : public Traverse<Visitors>
{
	/**
	 * @name Constructor/Initialization
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Statistics( bool bUseEdgeName = true, bool bVisitForest = false ) :
		vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest )
	{
		reset();
	}



	void reset()
	{
		m_nodeCount = 0;
		
		m_mapNodes.clear();
	}	
	//@}
	
	
	
	/**
	 * @name Accessors
	 * 
	 * @todo Add more accessors (like getTypes(), isIn(std::string nodeType), getNumOfInstance(std::string nodeType)...
	 */
	//@{
	
	/**
	 * @brief Returns the total number of nodes.
	 */
	const uint	getNodeCount() const { return ( m_nodeCount ); }
	

	/**
	 * @brief Send statistics to an output stream.
	 */
	void	print( std::ostream& out = std::cout )
	{
		out << "NodeCount=" << getNodeCount() << std::endl;
		
		NodeTypeIterator iter, iter_end;

		for(	boost::tie( iter, iter_end ) = getNodeTypeIterators();
				iter != iter_end;
				iter++
			)
		{
			out << "(" << iter->first << ", " << iter->second << ")" << std::endl;
		}
	}
	//@}



	/**
	 * @name Visitor interface that could be overloaded
	 */
	//@{
	template< typename Vertex , typename Graph >
	void discover_vertex( Vertex u, const Graph& /*g*/ ) /*const*/
	{
		vgd::Shp< vgd::node::Node > node = getNode(u);
		
		// *** update statistics. ***
		
		// node count
		m_nodeCount++;
		
		// node type and count of node type
		std::pair < NodeTypeMap::iterator, bool> retVal;
		retVal = m_mapNodes.insert( NodeTypeValue(node->getClassName(), 1) );
		
		if ( !retVal.second )
		{
			// node type already encountered.
			NodeTypeMap::iterator aClass = retVal.first;
			aClass->second++;
		}
		//else nothing
	}
	//@}



private:
	/**
	 * @name Typedefs
	 */
	//@{

	/**
	 * @brief Associate each class name with number of instance of it.
	 */
	typedef std::map< std::string, uint > NodeTypeMap;

	/**
	 * @brief Informations on one node type.
	 * 
	 * \li std::string	: the node type name.
	 * \li int32		: the number of times it is instanciated.
	 */
	typedef std::pair< std::string, uint > NodeTypeValue;
	
	/**
	 * @brief Iterator for the container of NOdeTypeValue.
	 */
	typedef NodeTypeMap::iterator NodeTypeIterator;	
	//@}

	/**
	 * @brief Returns a pair of iterator (std::pair<begin(), end()>) to iterate on the container of
	 * NodeTypeValue.
	 */
	std::pair< NodeTypeIterator, NodeTypeIterator >	getNodeTypeIterators()
	{
		return ( std::pair< NodeTypeIterator, NodeTypeIterator >(m_mapNodes.begin(), m_mapNodes.end() ) );
	}


	/**
	 * @name Data
	 */
	//@{

	/**
	 * @brief Container of informations on nodes.
	 */
	NodeTypeMap 	m_mapNodes;

	/**
	 * @brief Number of node.
	 */
	uint			m_nodeCount;
	//@}
};



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_STATISTICS_HPP
