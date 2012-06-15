// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/ui/EncryptFileUI.hpp"
#include "vgQt/actions/alg/EncryptFileAction.hpp"

namespace vgQt
{

namespace actions
{

namespace ui
{

META_ACTION_CPP( EncryptFileUI, 16 )

EncryptFileUI::EncryptFileUI()
{
    m_menuContrib = "Edit/EncryptFile";
    m_name = "Encrypt File";
    m_id = "EncryptFile";
    m_icon = vgUI::actions::DEFAULT;
    m_accelKey = "";
    m_action = vgd::makeShp( new vgQt::actions::alg::EncryptFileAction() );
}

} // namespace ui

} // namespace actions

} // namespace vgQt
