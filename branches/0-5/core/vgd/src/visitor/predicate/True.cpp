// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/visitor/predicate/True.hpp"

#include <vgd/Shp.hpp>



namespace vgd
{

namespace visitor
{

namespace predicate
{



const bool True::operator () ( const vgd::Shp< vgd::node::Node > node ) const
{
	return true;
}



const vgd::Shp< IPredicate > True::clone() const
{
	return vgd::makeShp( new True() );
}



} // namespace predicate

} // namespace visitor

} // namespace vgd
