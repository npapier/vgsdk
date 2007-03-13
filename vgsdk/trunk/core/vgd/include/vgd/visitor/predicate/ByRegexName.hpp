// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYREGEXNAME_HPP
#define _VGD_VISITOR_PREDICATE_BYREGEXNAME_HPP

#include <boost/regex.hpp>

#include "vgd/vgd.hpp"
#include "vgd/node/Node.hpp"




namespace vgd
{
	
namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by regular expression on node name.
 */
struct VGD_API ByRegexName
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
	bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;



private:

	boost::regex		m_regexName;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYREGEXNAME_HPP
