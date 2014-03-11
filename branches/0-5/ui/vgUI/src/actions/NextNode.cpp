// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/NextNode.hpp"

#include <vgAlg/actions/NextNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( NextNode, 13 )


NextNode::NextNode( ) :
IActionUI( "Edit/NextNode", "Next", "NextNode", NEXT, "<control>Down", new vgAlg::actions::NextNode() )
{
}



const bool NextNode::isValide( State state )
{
	if( state.getLocation() == TREE )
	{
		if( state.getParent() && state.getSelectedNode() )
		{
			const int index = state.getParent()->findChild( state.getSelectedNode() );
			if ( index < state.getParent()->size() -1 )
			{
				return true;
			}
		}
	}
	return false;
}



} // namespace actions

} // namespace vgUI
