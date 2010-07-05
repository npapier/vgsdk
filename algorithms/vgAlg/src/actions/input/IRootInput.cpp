// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/input/IRootInput.hpp"

namespace vgAlg
{

namespace actions
{

namespace input
{

void IRootInput::setRoot( vgd::Shp< vgd::node::Group > root )
{
	m_root = root;
}

vgd::Shp< vgd::node::Group > IRootInput::getRoot()
{
	return m_root;
}

} // namespace input

} // namespace actions

} // namespace vgAlg