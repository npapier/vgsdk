// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYTYPE_HPP
#define _VGD_VISITOR_PREDICATE_BYTYPE_HPP

#include "vgd/visitor/predicate/IPredicate.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by his type.
 * 
 * @sa vgd::node::Node::isA()
 *
 * @ingroup g_vgd_visitor_predicate
 */
template< typename Type >
struct ByType : public IPredicate
{
	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if node has the same type as template parameter \c Type.
	 */
	const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const
	{
		return ( node->template isA<Type>() );
	}
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYTYPE_HPP
