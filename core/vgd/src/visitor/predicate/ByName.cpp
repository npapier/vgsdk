// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/visitor/predicate/ByName.hpp"



namespace vgd
{

namespace visitor
{
	
namespace predicate
{



ByName::ByName( std::string name ) :
	m_name( name )
{}



bool ByName::operator () ( const vgd::Shp< vgd::node::Node > node ) const
{
	return ( node->getName() == m_name );
}



} // namespace predicate

} // namespace visitor

} // namespace vgd
