// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/GetNodeInTree.hpp"

#include <vgAlg/actions/GetNodeInTree.hpp>


namespace vgUI
{

namespace actions
{



GetNodeInTree::GetNodeInTree( ) :
IActionUI( "GetNodeInTree", "Select", "GetNodeInTree", DEFAULT, "", new vgAlg::actions::GetNodeInTree() )
{
}



const bool GetNodeInTree::isValide( State state ) const
{
	if( state.getSelectedNode() && state.getLocation() == CANVAS )
	{
		return true;
	}
	else
	{
		return false;
	}
}



} // namespace actions

} // namespace vgUI
