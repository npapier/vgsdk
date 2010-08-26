// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONS_UI_ENCRYPTFILEUI_HPP_
#define _VGGTK_ACTIONS_UI_ENCRYPTFILEUI_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/EncryptFile.hpp>

namespace vgGTK
{

namespace actions
{

namespace ui
{


/**
 * @brief ActionUI to popup remove confirmation.
 */
	struct VGGTK_API EncryptFileUI : public vgUI::actions::EncryptFile
{
	META_ACTION_HPP( EncryptFileUI );
	
	EncryptFileUI();
};


} // namespace ui

} // namespace actions

} // namespace vgGTK

#endif /*_VGGTK_ACTIONS_UI_ENCRYPTFILEUI_HPP_*/

