// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/ui/ExportNodeUI.hpp"
#include "vgQt/actions/alg/ExportNode.hpp"

namespace vgQt
{

namespace actions
{

namespace ui
{

META_ACTION_CPP( ExportNodeUI, 41 )

ExportNodeUI::ExportNodeUI() :
IActionUI( "ExportNode", "Export", "ExportNode", vgUI::actions::EXPORT, "", new vgQt::actions::alg::ExportNode() )
{}


const bool ExportNodeUI::isValide( vgUI::actions::State state )
{
	return state.getSelectedNode();
}


} // namespace ui

} // namespace actions

} // namespace vgQt
