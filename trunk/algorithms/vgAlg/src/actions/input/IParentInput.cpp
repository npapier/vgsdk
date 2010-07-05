// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/input/IParentInput.hpp"

namespace vgAlg
{

namespace actions
{

namespace input
{

void IParentInput::setParent( vgd::Shp< vgd::node::Group > parent )
{
	m_parent = parent;
}

vgd::Shp< vgd::node::Group > IParentInput::getParent()
{
	return m_parent.lock();
}

} // namespace input

} // namespace actions

} // namespace vgAlg