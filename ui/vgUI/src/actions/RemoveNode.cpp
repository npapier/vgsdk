// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/RemoveNode.hpp"

#include <vgAlg/actions/RemoveNode.hpp>


namespace vgUI
{

namespace actions
{


RemoveNode::RemoveNode( ) :
IActionUI( "Edit/RemoveNode", "Remove", "RemoveNode", REMOVE, "<control>Delete", new vgAlg::actions::RemoveNode() )
{
}



const bool RemoveNode::isValide( State state )
{
	if( state.getSelectedNode() && !state.isRoot() )
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
