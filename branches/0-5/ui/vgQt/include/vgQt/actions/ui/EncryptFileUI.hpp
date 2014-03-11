// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ACTIONS_UI_ENCRYPTFILEUI_HPP_
#define _VGQT_ACTIONS_UI_ENCRYPTFILEUI_HPP_

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/EncryptFile.hpp>
#include <vgUI/actions/IActionUI.hpp>

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

struct VGQT_API EncryptFileUI : public vgUI::actions::EncryptFile
{
    META_ACTION_HPP( EncryptFileUI )

    EncryptFileUI();
};


} // namespace ui

} // namespace actions

} // namespace vgQt



#endif /*_VGQT_ACTIONS_UI_ENCRYPTFILEUI_HPP_*/

