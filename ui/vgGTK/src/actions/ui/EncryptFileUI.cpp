// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/ui/EncryptFileUI.hpp"

#include <vgGTK/actions/alg/EncryptFile.hpp>


namespace vgGTK
{

namespace actions
{

namespace ui
{

META_ACTION_CPP( EncryptFileUI, 16 );


EncryptFileUI::EncryptFileUI()
{
	m_menuContrib = "Edit/EncryptFile";
	m_name = "Encrypt File";
	m_id = "EncryptFile";
	m_icon = vgUI::actions::DEFAULT;
	m_accelKey = "";
	m_action = vgd::makeShp( new vgGTK::actions::alg::EncryptFile() );
}


} // namespace ui

} // namespace actions

} // namespace vgGTK
