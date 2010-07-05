// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONS_UI_REMOVENODEUI_HPP_
#define _VGGTK_ACTIONS_UI_REMOVENODEUI_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgUI/actions/RemoveNode.hpp>

namespace vgGTK
{

namespace actions
{

namespace ui
{


/**
 * @brief ActionUI to popup remove confirmation.
 */
	struct VGGTK_API RemoveNodeUI : public vgUI::actions::RemoveNode
{
	RemoveNodeUI();
};


} // namespace ui

} // namespace actions

} // namespace vgGTK

#endif /*_VGGTK_ACTIONS_UI_REMOVENODEUI_HPP_*/

