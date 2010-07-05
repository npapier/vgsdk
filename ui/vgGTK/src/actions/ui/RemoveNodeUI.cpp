// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/ui/RemoveNodeUI.hpp"

#include <vgGTK/actions/alg/RemoveNode.hpp>


namespace vgGTK
{

namespace actions
{

namespace ui
{


RemoveNodeUI::RemoveNodeUI()
{
	m_menuContrib = "Edit/RemoveNode";
	m_name = "Remove";
	m_id = "RemoveNode";
	m_icon = vgUI::actions::REMOVE;
	m_accelKey = "<control>Delete";
	m_action = vgd::makeShp( new vgGTK::actions::alg::RemoveNode() );
}


} // namespace ui

} // namespace actions

} // namespace vgGTK
