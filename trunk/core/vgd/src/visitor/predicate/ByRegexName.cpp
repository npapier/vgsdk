// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/visitor/predicate/ByRegexName.hpp"



namespace vgd
{

namespace visitor
{
	
namespace predicate
{



ByRegexName::ByRegexName( std::string regexName ) :
	m_regexName( regexName )
{
}



bool ByRegexName::operator () ( const vgd::Shp< vgd::node::Node > node ) const
{
	return ( boost::regex_match( node->getName().c_str(), m_regexName ) );
}



} // namespace predicate

} // namespace visitor

} // namespace vgd
