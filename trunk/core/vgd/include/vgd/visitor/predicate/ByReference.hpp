// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYREFERENCE_HPP
#define _VGD_VISITOR_PREDICATE_BYREFERENCE_HPP

#include "vgd/visitor/predicate/IPredicate.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by his pointer.
 *
 * @ingroup g_vgd_visitor_predicate
 *
 * @deprecated Previously useful to retrieve the shared pointer of a node from its pointer. Now, node inherits from EnableShpFromThis to do that.
 */
struct VGD_API ByReference : public IPredicate
{
	/**
	 * @brief Constructor
	 * 
	 * @param reference		node reference to find.
	 */
	ByReference( const vgd::node::Node *reference );

	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if name of node is the name specified to the constructor.
	 */
	const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;



private:

	const vgd::node::Node *m_reference;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYREFERENCE_HPP
