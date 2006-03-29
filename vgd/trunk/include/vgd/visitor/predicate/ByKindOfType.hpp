// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYKINDOFTYPE_HPP
#define _VGD_VISITOR_PREDICATE_BYKINDOFTYPE_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/Node.hpp"



namespace vgd
{
	
namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by his type.
 * 
 * @sa vgd::node::Node::isAKindOf()
 */
template< typename Type >
struct ByKindOfType
{
	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if node is derived from the template parameter \c Type.
	 */
	bool operator () ( const vgd::Shp< vgd::node::Node > node ) const
	{
		return ( node->template isAKindOf<Type>() != 0 );
	}
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYKINDOFTYPE_HPP
