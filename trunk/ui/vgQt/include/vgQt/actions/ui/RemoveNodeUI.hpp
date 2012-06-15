// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ACTIONS_UI_REMOVENODEUI_HPP_
#define _VGQT_ACTIONS_UI_REMOVENODEUI_HPP_

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/RemoveNode.hpp>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace actions
{

namespace ui
{


/**
 * @brief ActionUI to popup remove confirmation.
 */
    struct VGQT_API RemoveNodeUI : public vgUI::actions::RemoveNode
{
    META_ACTION_HPP( RemoveNodeUI )

    RemoveNodeUI();
};


} // namespace ui

} // namespace actions

} // namespace vgQt

#endif // _VGQT_ACTIONS_UI_REMOVENODEUI_HPP_
