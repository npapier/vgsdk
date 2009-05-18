// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_TRUE_HPP
#define _VGD_VISITOR_PREDICATE_TRUE_HPP

#include "vgd/visitor/predicate/IPredicate.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate returning always true
 *
 * @ingroup g_vgd_visitor_predicate
 */
struct VGD_API True : public IPredicate
{
	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns always true.
	 */
	const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_TRUE_HPP
