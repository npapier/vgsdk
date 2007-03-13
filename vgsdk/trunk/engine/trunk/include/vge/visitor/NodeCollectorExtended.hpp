// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_VISITOR_NODECOLLECTOREXTENDED_HPP
#define _VGE_VISITOR_NODECOLLECTOREXTENDED_HPP

#include <utility>
#include <vector>

#include <vgd/node/Kit.hpp>
#include <vgd/visitor/Traverse.hpp>

#include "vge/vge.hpp"



namespace vge
{
	
namespace visitor
{

/**
 * @name Typedefs.
 */
//@{

/**
 * @brief Each time a node is encountered a TraverseElement structure is filled for storing traverse informations.
 * 
 * bool means :
 * \li true		<=> preTraverse	: This is invoked when a node is encountered for the first time.
 * \li false	<=> postTraverse	: This is invoked when all children of this node have been already encountered.
 */
typedef std::pair< vgd::node::Node*, bool >	TraverseElement;

/**
 * @brief All encountered traverse elements are stored by this structure
 * 
 * @todo cache system
 * @todo Move to another file and improve interface (TraverseElement).
 */
struct TraverseElementVector
{
	typedef std::vector< TraverseElement >::iterator			iterator;
	typedef std::vector< TraverseElement >::const_iterator		const_iterator;

	void clear() { m_elements.clear(); }
	void reserve( int size ) { m_elements.reserve( size ); }

	int size() const { return static_cast<int>(m_elements.size()); }

	void push_back( const TraverseElement& val ) { m_elements.push_back( val ); }

	template< class InputIterator >
	void insert( iterator where, InputIterator first, InputIterator last )
	{
		m_elements.insert(where, first, last);
	}

	iterator begin() { return m_elements.begin(); }
	const_iterator begin() const { return m_elements.begin(); }
	
	iterator end() { return m_elements.end(); }
	const_iterator end() const { return m_elements.end(); }

	vgd::node::Node *getRoot() { m_elements.begin()->first; }


private:
	std::vector< TraverseElement > m_elements;
//typedef std::vector< TraverseElement >			TraverseElementVector;
};
//@}



/**
 * @brief An extended collector of nodes.
 * 
 * NodeCollectorExtended class traverses a scene graph (like Traverse) and records all encountered nodes and
 * when they are encountered(preTraverse, postTraverse) during this process.
 * 
 * Use this visitor for :
 * 
 * \li storing all informations to be able to evaluate scene graph without retraversing it for each pass(used by Engine).
 */
template< typename Visitors = boost::null_visitor >
struct NodeCollectorExtended : public vgd::visitor::Traverse<Visitors>
{
	/**
	 * @name Constructor/Initialization.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	NodeCollectorExtended( bool bUseEdgeName = true, bool bVisitForest = false ) :
		vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest )
	{
		reset();
	}


	/**
	 * @brief Reset what it should in order to reuse this visitor.
	 * 
	 * @param numOfNodesHint : hint to specify the number of nodes that this visitor should encountered.
	 * This permits to reserve a minimum length of storage for the container of visited node in order to reduce reallocation.
	 */
	void	reset	( const int32 numOfNodesHint = 1024 )
	{
		m_traverseElementContainer.clear();
		m_traverseElementContainer.reserve(numOfNodesHint);
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
	const TraverseElementVector*	getTraverseElements() const	{ return ( &m_traverseElementContainer ); }
	
	TraverseElementVector*			getTraverseElements()		{ return ( &m_traverseElementContainer ); }	
	//@}



	/**
	 * @name Visitor interface that could be overloaded
	 */
	//@{
	template< typename Vertex , typename Graph >
	void discover_vertex( Vertex u, const Graph& /*g*/ )
	{
		vgd::Shp< vgd::node::Node > pNode = getNode(u);

		m_traverseElementContainer.push_back( TraverseElement(pNode.get(), true ) );
		
		vgd::Shp< vgd::node::Kit > pKit( vgd::dynamic_pointer_cast< vgd::node::Kit >( pNode ) );
		
		if ( pKit.get() != 0 )
		{
			// FIXME : optme, concat new collected node to the current collector.
			vgd::Shp< vgd::node::Group > pGroup = pKit->getRoot();
			
			if ( pGroup.get() != 0 )
			{
				NodeCollectorExtended<> collector;
				pGroup->traverse( collector );
			
				m_traverseElementContainer.insert(
					m_traverseElementContainer.end(),
					collector.m_traverseElementContainer.begin(),
					collector.m_traverseElementContainer.end()
				 );
			}
		}
		// else nothing to do
	}

	template <class Vertex, class Graph>
	void finish_vertex(Vertex u, const Graph& /*g*/)
	{
		vgd::Shp< vgd::node::Node > pNode = getNode(u);
		
		m_traverseElementContainer.push_back( TraverseElement(pNode.get(), false ) );
	}
	//@}



private:


	/**
	 * @name Data.
	 */
	//@{
	
	TraverseElementVector	m_traverseElementContainer;

	//@}
};



} // namespace visitor

} // namespace vge

#endif //#ifndef _VGE_VISITOR_NODECOLLECTOREXTENDED_HPP
