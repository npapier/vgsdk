// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYREGEXNAME_HPP
#define _VGD_VISITOR_PREDICATE_BYREGEXNAME_HPP

#include <boost/regex.hpp>
#include "vgd/visitor/predicate/IPredicate.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by regular expression on node name.
 *
 * @ingroup g_vgd_visitor_predicate
 */
struct VGD_API ByRegexName : public IPredicate
{
	/**
	 * @brief Constructor
	 * 
	 * @param regexName		regular expression for node name to find.
	 */
	ByRegexName( std::string regexName );

	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if name of node matches the given regular expression (in the constructor).
	 */
	const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;

	const vgd::Shp< IPredicate > clone() const;

private:

	boost::regex		m_regexName;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYREGEXNAME_HPP
