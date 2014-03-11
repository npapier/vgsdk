// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/input/INodeInput.hpp"

namespace vgAlg
{

namespace actions
{

namespace input
{

void INodeInput::setNode( vgd::Shp< vgd::node::Node > node )
{
	m_node = node;
}

vgd::Shp< vgd::node::Node > INodeInput::getNode()
{
	return m_node.lock();
}

} // namespace input

} // namespace actions

} // namespace vgAlg