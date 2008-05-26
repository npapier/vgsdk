// VGSDK - Copyright (C) 2004, 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/graph/detail/Graph.hpp"



namespace vgd
{

namespace graph
{

namespace detail
{




EdgeName::EdgeName( vgd::Shp< vgd::node::Node > child, const int value, const bool isEnable )
:	m_child		(child),
	m_value		(value),
	m_isEnable	(isEnable)
{}



vgd::Shp<vgd::node::Node>& EdgeName::child()
{
	return m_child;
}



const vgd::Shp<vgd::node::Node>& EdgeName::child() const
{
	return m_child;
}



int& EdgeName::value()
{
	return m_value;
}



const int EdgeName::value() const
{
	return m_value;
}



bool& EdgeName::enable()
{
	return m_isEnable;
}



const bool EdgeName::enable() const
{
	return m_isEnable;
}



void EdgeName::negate()
{
	m_isEnable = !m_isEnable;
}



const bool EdgeName::operator < ( const EdgeName& edge ) const
{
	const bool retVal = m_value < edge.value();
	return retVal;
}



} // namespace detail

} // namespace graph

} // namespace vgd
