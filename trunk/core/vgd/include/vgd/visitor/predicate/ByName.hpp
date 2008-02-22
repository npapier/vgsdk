// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYNAME_HPP
#define _VGD_VISITOR_PREDICATE_BYNAME_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/Node.hpp"



namespace vgd
{
	
namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node by his name.
 */
struct VGD_API ByName
{
	/**
	 * @brief Constructor
	 * 
	 * @param name		node name to find.
	 */
	ByName( std::string name );

	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if name of node is the name specified to the constructor.
	 */
	bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;



private:

	std::string		m_name;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYNAME_HPP
