// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/ui/RemoveNodeUI.hpp"
#include "vgQt/actions/alg/RemoveNode.hpp"

namespace vgQt
{

namespace actions
{

namespace ui
{

META_ACTION_CPP( RemoveNodeUI, 15 )

RemoveNodeUI::RemoveNodeUI()
{
    m_menuContrib = "Edit/RemoveNode";
    m_name = "Remove";
    m_id = "RemoveNode";
    m_icon = vgUI::actions::REMOVE;
    m_accelKey = "<control>Delete";
    m_action = vgd::makeShp( new vgQt::actions::alg::RemoveNode() );
}


} // namespace ui

} // namespace actions

} // namespace vgQt
