// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/visitor/predicate/ByReference.hpp"

#include "vgd/Shp.hpp"



namespace vgd
{

namespace visitor
{

namespace predicate
{



ByReference::ByReference( const vgd::node::Node *reference ) :
	m_reference( reference )
{}



const bool ByReference::operator () ( const vgd::Shp< vgd::node::Node > node ) const
{
	return ( node.get() == m_reference );
}



const vgd::Shp< IPredicate > ByReference::clone() const
{
	return vgd::makeShp( new ByReference( m_reference ) );
}



} // namespace predicate

} // namespace visitor

} // namespace vgd
