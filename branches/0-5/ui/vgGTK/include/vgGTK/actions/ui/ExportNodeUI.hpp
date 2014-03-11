// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONS_UI_EXPORTNODEUI_HPP_
#define _VGGTK_ACTIONS_UI_EXPORTNODEUI_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/IActionUI.hpp>

namespace vgGTK
{

namespace actions
{

namespace ui
{



/**
 * @brief ActionUI to popup remove confirmation.
 */
	struct VGGTK_API ExportNodeUI : public vgUI::actions::IActionUI
{
	META_ACTION_HPP( ExportNodeUI );
	
	ExportNodeUI();

	virtual const bool isValide( vgUI::actions::State state );
};



} // namespace ui

} // namespace actions

} // namespace vgGTK

#endif /*_VGGTK_ACTIONS_UI_EXPORTNODEUI_HPP_*/

