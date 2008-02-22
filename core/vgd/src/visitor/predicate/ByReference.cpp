// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/visitor/predicate/ByReference.hpp"



namespace vgd
{

namespace visitor
{
	
namespace predicate
{



ByReference::ByReference( const vgd::node::Node *reference ) :
	m_reference( reference )
{}



bool ByReference::operator () ( const vgd::Shp< vgd::node::Node > node ) const
{
	return ( node.get() == m_reference );
}



} // namespace predicate

} // namespace visitor

} // namespace vgd
