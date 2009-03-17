// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_GROUP_HPP
#define _VGD_NODE_GROUP_HPP

#include <iostream>
#include <string>

#include "vgd/graph/Graph.hpp"
#include "vgd/node/IGroup.hpp"
#include "vgd/node/IBoundingBox.hpp"
#include "vgd/node/Node.hpp"
//#include "vgd/visitor/FindFirst.hpp"



namespace vgd
{

namespace node
{

/**
 * @brief Base class for all group nodes. Container for the child nodes.
 * 
 * This node defines the base class for all group nodes. Group is a
 * node that contains an ordered list of child nodes. The ordering of the
 * child nodes represents the traversal order for all operations (for
 * example, rendering, picking, and so on). This node is simply a
 * container for the child nodes and does not alter the traversal state
 * in any way. During traversal, state accumulated for a child is passed
 * on to each successive child and then to the parents of the group
 * (\c Group does not push or pop traversal state as \c Separator does).
 * 
 * All child nodes are traversing.
 * 
 * @todo getFChildren(), getFSelectedChildren()
 * 
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 */
struct VGD_API Group : public IGroup, public IBoundingBox, public Node
{
	META_NODE_HPP( Group );

	/**
	 * @name IGroup interface and getChild()
	 */
	//@{
	void			addChild			( vgd::Shp<Node> node );
	void			insertChild			( vgd::Shp<Node> node, const int newChildIndex = 0 );

	void			replaceChild		( vgd::Shp<Node> newChild, const int index );
	void			replaceChild		( vgd::Shp<Node> oldChild, vgd::Shp<Node> newChild );

	void			removeChild			( const int childIndex );
	bool			removeChild			( vgd::Shp<Node> childToRemove );
	void			removeAllChildren	( void );

	bool			containsChild		( const vgd::Shp<Node> node ) const;
	int				findChild			( const vgd::Shp<Node> node ) const;

	vgd::Shp<Node>	getAbstractChild	( const int index );
	void			getChildren			( NodeList& children) const;
	void			getEnabledChildren	( NodeList& children, const bool bGetEnabled = true) const;
	int				getNumChildren		( void ) const;

	const int size() const;
	//@}


	/**
	 * @brief Returns pointer to child node with the given index.
	 *
	 * A more user friendly method for getting a child than getAbstractChild().
	 * 
	 * @remark An assert occurs when internal dynamic_pointer_cast fails.
	 *
	 * @code 
	 * 
	 * vgd::Shp< vgd::node::Transform > transform;
	 * 
	 * // You can get a child with getAbstractChild().
	 * transform = vgd::dynamic_pointer_cast< vgd::node::Transform >(m_sceneGraph->getAbstractChild(0));
	 * 
	 * or
	 * 
	 * // You can get a child with getChild().
	 * transform = m_sceneGraph->getChild<vgd::node::Transform>(0);
	 * 
	 * @endcode
	 */
	template< typename nodeType >
	vgd::Shp< nodeType > getChild( const int index )
	{
		vgd::Shp< vgd::node::Node > child	= getAbstractChild( index );

		vgd::Shp< nodeType > castedChild 	= vgd::dynamic_pointer_cast< nodeType >(child);
		assert( castedChild.get() != 0 && "Wrong node type." );

		return castedChild;
	}


	/**
	 * @todo
	 * brief Finds the first node that matches the predicate.
	 * 
	 * This method traverses the scene graph from this group node and searches the first node that
	 * cause the predicate to return true
	 * 
	 * param predicate		the predicate to test matching
	 * 
	 * return The first node that matches the predicate, or an empty shared pointer.
	 */
//	template< class Predicate >
//	vgd::Shp< vgd::node::Node > findFirst( const Predicate& predicate )
//	{
//		vgd::visitor::FindFirst< Predicate > find( predicate );
//		
//		traverse( find );
//		
//		return find.getShpNode();
//	}
		



	/**
	 * @name Traverse scene graph
	 */
	//@{

	/**
	 * @brief Traverse the graph starting on this node with the specified visitor.
	 * 
	 * @remark A traverse action is like a depth first visit.
	 * @todo Removes the template.
	 */
	template< typename DFSVisitor >
	void traverse( DFSVisitor& visitor ) const
	{
		graph().traverse( vertexDescriptor(), visitor );
	}

	//@}



	/**
	 * @name Bounding box
	 */
	//@{

	/**
	 * @brief Computes the bounding box.
	 *
	 * @pre all direct children of this node are valid.
	 * 
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 * 
	 * @remark Computes only if bounding box dirty flag is invalidate.
	 *
	 * @remark This bounding box is valid if and only if all direct children of this node are valid.
	 * An invalid node at depth > 1 could exist when bounding box dirty flag is valid.
	 * 
	 * @todo transformation is not used, because transformation in Group BB is always identity and it's not useful to 
	 * compute group BB => remove it ?
	 */
	bool computeBoundingBox( const vgm::MatrixR& transformation /* not used */ );

	/***
	 * @todo Returns a good value, only possible after some work on graph (getFChildrenSelection(), getFChildren() ).
	 */
	bool isBoundingBoxValid() const;

	void invalidateBoundingBox( bool bInvalidate = true );
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
	 */
	void	writeGraphviz( std::ostream& out = std::cout ) const;
	//@}



	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when children list changed.
	 */
	static const std::string getDFChildren( void );
	
	/**
	 * @brief Returns name of dirty flag that is invalidate when selection of children is changed (see Switch and MultiSwitch).
	 */
	static const std::string getDFChildrenSelection( void );

	/**
	 * @brief Returns name of dirty flag that is invalidate when bounding box is invalidate and must be recomputed.
	 */
	static const std::string getDFBoundingBox( void );

	//@}



protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Constructor.
	 */
	Group( const std::string nodeName );

	/**
	 * @brief Set fields and dirty flags to default values.
	 */
	void setToDefaults( void );

	void setOptionalsToDefaults();

	//@}



	/**
	 * @name Debug methods
	 */
	//@{

	bool	checkChildIndex( const int index ) const;

	//@}


	// Overridden
	void updateGraph( void );
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_GROUP_HPP
