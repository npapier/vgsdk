// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/visitor/predicate/ByDirtyFlag.hpp"

#include "vgd/field/DirtyFlag.hpp"



namespace vgd
{

namespace visitor
{
	
namespace predicate
{



bool ByDirtyFlag::operator () ( const vgd::Shp< vgd::node::Node > node ) const
{
	const vgd::field::DirtyFlag *pDirtyFlag;
	pDirtyFlag = node->getDirtyFlag( node->getDFNode() );

	return pDirtyFlag->isDirty();
}



} // namespace predicate

} // namespace visitor

} // namespace vgd
