// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_BYDIRTYFLAG_H
#define _VGD_VISITOR_PREDICATE_BYDIRTYFLAG_H

#include "vgd/vgd.hpp"

#include "vgd/node/Node.hpp"



namespace vgd
{
	
namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate to sort/find node when "node" dirty flag is invalidate (i.e. when a modification is done in any 
 * fields).
 */
struct VGD_API ByDirtyFlag
{
	/**
	 * @brief Test the predicate.
	 * 
	 * @return Returns true if the "node" dirty flag is invalidate.
	 */
	bool operator () ( const vgd::Shp< vgd::node::Node > node ) const;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_BYDIRTYFLAG_H
