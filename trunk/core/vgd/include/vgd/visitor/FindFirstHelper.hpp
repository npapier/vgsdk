// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_FINDFIRSTHELPER_HPP
#define _VGD_VISITOR_FINDFIRSTHELPER_HPP

#include "vgd/node/Group.hpp"
#include "vgd/visitor/FindFirst.hpp"



namespace vgd
{

namespace visitor
{



/**
 * @brief Traverse the graph starting on the specified node with the specified visitor to find the first node that 
 * returns true to the predicate.
 * 
 * @remark This method is an helper to simplify usage of traverse() with vgd::visitor::FindFirst.
 *
 * @deprecated @see g_vgd_visitor_helpers
 */
template< class Predicate >
std::pair< bool, vgd::Shp< vgd::node::Node > > findFirstDEPRECATED( vgd::Shp< vgd::node::Group > group, const Predicate& predicate )
{
	vgd::visitor::FindFirst< Predicate >	find( predicate );

	bool bFounded = false;

	try
	{
		group->traverse( find );
	}
	catch ( vgd::visitor::DesiredStop )
	{
		// ok, found the first node.
		bFounded = true;
	}

	return ( std::pair< bool, vgd::Shp< vgd::node::Node > >( bFounded, find.getShpNode() ) );
}



} // namespace visitor

} // namespace vgd



#endif //#ifndef _VGD_VISITOR_FINDFIRSTHELPER_HPP
