// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYNAME_HPP
#define _VGD_VISITOR_PREDICATE_BYNAME_HPP

#include <string>
#include "vgd/visitor/predicate/IPredicate.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by his name.
 *
 * @ingroup g_vgd_visitor_predicate
 */
struct VGD_API ByName : public IPredicate
{
	/**
	 * @brief Constructor
	 * 
	 * @param name		node name to find.
	 */
	ByName( const std::string name );

	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if name of node is the name specified to the constructor.
	 */
	const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;



private:

	std::string		m_name;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYNAME_HPP
