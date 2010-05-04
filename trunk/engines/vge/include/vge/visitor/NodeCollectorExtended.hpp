// VGSDK - Copyright (C) 2004, 2007, 2008, 2010, Nicolas Papier.
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
* @brief	Replace the TraverseElement std::pair to add a third parameter: isKit.
*			isKit define if the node is contained in a kit or not.
*/
struct TraverseElement
{

	TraverseElement( vgd::node::Node* node, const bool traverse, const bool isKit = false )
	:	first( node ),
		second( traverse ),
		m_isKit( isKit )
	{}

	//@todo rename everywhere and encapsulate.
	vgd::node::Node*	first;

	/**
	 * @brief Each time a node is encountered a TraverseElement structure is filled for storing traverse informations.
	 * 
	 * bool means :
	 * \li true		<=> preTraverse	: This is invoked when a node is encountered for the first time.
	 * \li false	<=> postTraverse	: This is invoked when all children of this node have been already encountered.
	 */
	bool				second;

	vgd::node::Node* node() const
	{
		return first;
	}

	const bool preTraverse() const
	{
		return second;
	}

	void setKit( bool isKit )
	{
		m_isKit = isKit;
	}

	const bool isKit() const
	{
		return m_isKit;
	}

private:
	bool				m_isKit;
};

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

	iterator begin() { return m_elements.begin(); }
	const_iterator begin() const { return m_elements.begin(); }
	
	iterator end() { return m_elements.end(); }
	const_iterator end() const { return m_elements.end(); }

	void clear() { m_elements.clear(); }
	void reserve( int size ) { m_elements.reserve( size ); }

	int size() const { return static_cast<int>(m_elements.size()); }

	void push_back( const TraverseElement& val ) { m_elements.push_back( val ); }

	template< class InputIterator >
	void insert( iterator where, InputIterator first, InputIterator last )
	{
		m_elements.insert(where, first, last);
	}



	vgd::Shp< vgd::node::Group > getRoot()
	{
		using vgd::node::Group;
		using vgd::node::Node;

		Node *				rootNodePtr	= getAbstractRootPtr();
		assert( rootNodePtr != 0 && "No root node." );

		vgd::Shp< Node >	rootNode	= rootNodePtr->shpFromThis();
		vgd::Shp< Group >	rootGroup	= vgd::dynamic_pointer_cast< Group >( rootNode );
		assert( rootGroup != 0 && "Root node is not a Group." );

		return rootGroup;
	}

	vgd::node::Group *getRootPtr()
	{
		using vgd::node::Group;
		Group * root = dynamic_cast< Group * >( getAbstractRootPtr() );
		assert( root != 0 && "Root node is not a Group." );

		return root;
	}


	vgd::node::Node *getAbstractRootPtr()
	{
		return m_elements.begin()->first;
	}


private:
	std::vector< TraverseElement > m_elements;
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
	 * @name Constructor/Initialization
	 */
	//@{
	
	/**
	 * @brief	Defines how the collector should traverse kit node.
	 */
	enum KitPolicy
	{
		TRAVERSE_KIT,	///< if there is a kit, traverse it.
		IGNORE_KIT,		///< if there is a kit, don't traverse it.
		FORCE_KIT		///< we are already in a kit, mark all node as "in a kit" and traverse sub-kit.
	};

	/**
	 * @brief Default constructor
	 */
	NodeCollectorExtended( bool bUseEdgeName = true, bool bVisitForest = false, const KitPolicy kitPolicy = TRAVERSE_KIT )
	:	vgd::visitor::Traverse<Visitors>( bUseEdgeName, bVisitForest ),
		m_kitPolicy( kitPolicy )
	{
		reset();
	}


	/**
	 * @brief Reset what it should in order to reuse this visitor.
	 * 
	 * @param numOfNodesHint	hint to specify the number of nodes that this visitor should encountered.
	 * This permits to reserve a minimum length of storage for the container of visited node in order to reduce reallocation.
	 */
	void reset( const int32 numOfNodesHint = 1024 )
	{
		m_traverseElementContainer.clear();
		m_traverseElementContainer.reserve( numOfNodesHint );
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

		TraverseElement traverseElem( pNode.get(), true );
		switch ( m_kitPolicy )
		{
			case TRAVERSE_KIT:
				break;

			case IGNORE_KIT:
				m_traverseElementContainer.push_back( traverseElem );
				return;

			case FORCE_KIT:
				traverseElem.setKit( true );
				break;

			default:
				assert(false);
		}

		m_traverseElementContainer.push_back( traverseElem );

		vgd::Shp< vgd::node::Kit > pKit( vgd::dynamic_pointer_cast< vgd::node::Kit >( pNode ) );
		if ( pKit )
		{
			// @todo OPTME concat new collected node to the current collector.
			vgd::Shp< vgd::node::Group > pGroup = pKit->getRoot();
			if ( pGroup )
			{
				NodeCollectorExtended<> collector( true, false, FORCE_KIT );
				pGroup->traverse( collector );
				
				m_traverseElementContainer.insert(
					m_traverseElementContainer.end(),
					collector.m_traverseElementContainer.begin(), collector.m_traverseElementContainer.end() );
			}
			// else nothing to do
		}
		// else nothing to do
	}

	template <class Vertex, class Graph>
	void finish_vertex(Vertex u, const Graph& /*g*/)
	{
		vgd::Shp< vgd::node::Node > pNode = getNode(u);

		TraverseElement traverseElem( pNode.get(), false );

		switch ( m_kitPolicy )
		{
			case TRAVERSE_KIT:
			case IGNORE_KIT:
				break;

			case FORCE_KIT:
				traverseElem.setKit( true );
				break;

			default:
				assert(false);
		}

		m_traverseElementContainer.push_back( traverseElem );
	}
	//@}

private:


	/**
	 * @name Data
	 */
	//@{
	
	TraverseElementVector	m_traverseElementContainer;

	KitPolicy				m_kitPolicy;

	//@}
};



} // namespace visitor

} // namespace vge

#endif //#ifndef _VGE_VISITOR_NODECOLLECTOREXTENDED_HPP
