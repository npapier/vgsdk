// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/HideAllExceptSelectedNode.hpp"

#include <vgAlg/actions/HideAllExceptSelectedNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( HideAllExceptSelectedNode, 50 )


HideAllExceptSelectedNode::HideAllExceptSelectedNode( ) :
IActionUI( "Visibility/HideAllExceptSelectedNode", "Hide all except selection", "HideAllExceptSelectedNode", DEFAULT, "", new vgAlg::actions::HideAllExceptSelectedNode() )
{
}



const bool HideAllExceptSelectedNode::isValide( State state )
{
	if( state.getNumberOfDisplayedNode() > 1 && state.isShape() )
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

#endif // #ifdef __USE_VGALG__
