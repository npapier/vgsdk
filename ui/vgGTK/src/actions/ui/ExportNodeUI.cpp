// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/ui/ExportNodeUI.hpp"

#include <vgGTK/actions/alg/ExportNode.hpp>


namespace vgGTK
{

namespace actions
{

namespace ui
{


ExportNodeUI::ExportNodeUI()
{
	m_menuContrib = "ExportNode";
	m_name = "Export";
	m_id = "ExportNode";
	m_icon = vgUI::actions::EXPORT;
	m_accelKey = "";
	m_action = vgd::makeShp( new vgGTK::actions::alg::ExportNode() );
}



} // namespace ui

} // namespace actions

} // namespace vgGTK
