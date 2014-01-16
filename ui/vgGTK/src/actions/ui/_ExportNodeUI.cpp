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

META_ACTION_CPP( ExportNodeUI, 41 );


ExportNodeUI::ExportNodeUI() :
IActionUI( "ExportNode", "Export", "ExportNode", vgUI::actions::EXPORT, "", new vgGTK::actions::alg::ExportNode() )
{
}



const bool ExportNodeUI::isValide( vgUI::actions::State state )
{
        if( state.getSelectedNode() )
        {
                return true;
        }
        else
        {
                return false;
        }
}



} // namespace ui

} // namespace actions

} // namespace vgGTK
