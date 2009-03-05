// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYDIRTYFLAG_HPP
#define _VGD_VISITOR_PREDICATE_BYDIRTYFLAG_HPP

#include "vgd/visitor/predicate/IPredicate.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node when "node" dirty flag is invalidate (i.e. when a modification is done in any 
 * fields).
 *
 * @ingroup g_vgd_visitor_predicate
 */
struct VGD_API ByDirtyFlag : public IPredicate
{
	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if the "node" dirty flag is invalidate.
	 */
	const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYDIRTYFLAG_HPP
