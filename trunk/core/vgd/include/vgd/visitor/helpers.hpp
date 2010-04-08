// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_HELPERS_HPP
#define _VGD_VISITOR_HELPERS_HPP

#include <vgd/node/Group.hpp>
#include "vgd/visitor/Find.hpp"
#include "vgd/visitor/FindFirst.hpp"
#include <vgd/visitor/predicate/ByDirtyFlag.hpp>
#include <vgd/visitor/predicate/ByName.hpp>



namespace vgd
{

namespace visitor
{

/**
 * @addtogroup g_vgd_visitor_helpers	Helpers for visitors
 * @ingroup g_vgd_visitor
 */
//@{



/**
 * @brief Traverses the scene graph from the specified root node to locate the first occurence of a node that matches the given predicate.
 *
 * @param root		the starting point of the traversing
 * @param predicate	the object that defines a set of criteria and determines whether the specified node meets those criteria.
 *
 * @return A shared pointer on the desired node. If no such node exists, returns an empty shared pointer.
 */
template< typename T, typename Predicate >
vgd::Shp< T > findFirst( vgd::Shp< vgd::node::Group > root, const Predicate& predicate )
{
	vgd::Shp< T > retVal;

	vgd::visitor::FindFirst< Predicate > find( predicate );

	bool bFounded = false;

	try
	{
		root->traverse( find );
	}
	catch ( vgd::visitor::DesiredStop )
	{
		// ok, found the first node.
		bFounded = true;
	}

	if ( bFounded )
	{
		retVal = vgd::dynamic_pointer_cast< T >( find.getShpNode() );
		assert( retVal && "Found node, but dynamic cast fails. Wrong given type ?" );
	}
	// else nothing to do

	return retVal;
}



/**
 * @brief Traverses the scene graph from the specified root node to locate the all occurences of node that matches the given predicate.
 *
 * @param root		the starting point of the traversing
 * @param predicate	the object that defines a set of criteria and determines whether the specified node meets those criteria.
 *
 * @return A shared pointer on the desired node list.
 *
 * @remarks When a node matches the predicate during scene graph traversing, it is added at the end of the returned node list.
 */
template< typename Predicate >
vgd::Shp< vgd::node::NodeList > find( vgd::Shp< vgd::node::Group > root, const Predicate& predicate )
{
	vgd::visitor::Find< Predicate > find( predicate );

	root->traverse( find );

	vgd::Shp< vgd::node::NodeList > retVal = find.getShpNodes();

	return retVal;
}



/**
 * @brief Traverses the scene graph from the specified root node to locate the first occurence of a node with a "node" dirty flag invalidated.
 *
 * @param root		the starting point of the traversing
  *
 * @return A shared pointer on the desired node. If no such node exists, returns an empty shared pointer.
 */
template< typename T >
vgd::Shp< T > findFirstByDirtyFlag( vgd::Shp< vgd::node::Group > root )
{
	using vgd::visitor::predicate::ByDirtyFlag;

	vgd::Shp< T > retVal = findFirst<T, ByDirtyFlag>( root, ByDirtyFlag() );

	return retVal;
}



/**
 * @brief Traverses the scene graph from the specified root node to locate the first occurence of a node with the desired name.
 *
 * @param root		the starting point of the traversing
 * @param name		name of the node to find
 *
 * @return A shared pointer on the desired node. If no such node exists, returns an empty shared pointer.
 */
template< typename T >
vgd::Shp< T > findFirstByName( vgd::Shp< vgd::node::Group > root, const std::string name )
{
	using vgd::visitor::predicate::ByName;
	const ByName predicate(name);

	vgd::Shp< T > retVal = findFirst<T, ByName>( root, predicate );

	return retVal;
}

//@}



} // namespace visitor

} // namespace vgd



#endif //#ifndef _VGD_VISITOR_HELPERS_HPP

