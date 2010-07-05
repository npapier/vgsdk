// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/input/IHiddenNodeInput.hpp"

namespace vgAlg
{

namespace actions
{

namespace input
{


void IHiddenNodeInput::setHiddenNode( vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode )
{
	m_hiddenNode = hiddenNode;
}

vgd::Shp < vgAlg::actions::HiddenNode > IHiddenNodeInput::getHiddenNode()
{
	return m_hiddenNode.lock();
}

} // namespace input

} // namespace actions

} // namespace vgAlg