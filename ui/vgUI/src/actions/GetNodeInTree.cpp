// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/GetNodeInTree.hpp"

#include <vgAlg/actions/GetNodeInTree.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( GetNodeInTree, 1 )


GetNodeInTree::GetNodeInTree( ) :
IActionUI( "GetNodeInTree", "Select", "GetNodeInTree", DEFAULT, "", new vgAlg::actions::GetNodeInTree() )
{
}



const bool GetNodeInTree::isValide( State state )
{
	if( state.getSelectedNode() && state.getLocation() == CANVAS )
	{
		m_name = "Select " + state.getSelectedNode()->getName();
		return true;
	}
	else
	{
		return false;
	}
}



} // namespace actions

} // namespace vgUI

#endif // #ifdef __USE_VGALG__
