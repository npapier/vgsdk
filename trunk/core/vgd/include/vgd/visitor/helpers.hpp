// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_HELPERS_HPP
#define _VGD_VISITOR_HELPERS_HPP

#include <vgd/node/Group.hpp>
#include <vgd/visitor/FindFirstHelper.hpp>
#include <vgd/visitor/predicate/ByName.hpp>


namespace vgd
{

namespace visitor
{


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
	std::pair< bool, vgd::Shp< vgd::node::Node > > result = vgd::visitor::findFirst( root, predicate );

	vgd::Shp< T > retVal;

	if ( result.first )
	{
		retVal = vgd::dynamic_pointer_cast< T >(result.second);
		assert( retVal && "Found node, but dynamic cast fails. Wrong given type ?" );
	}
	// else nothing to do

	return retVal;
}



} // namespace visitor

} // namespace vgd



#endif //#ifndef _VGD_VISITOR_HELPERS_HPP
