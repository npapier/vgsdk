// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/PreviousNode.hpp"

#include <vgAlg/actions/PreviousNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( PreviousNode, 14 )


PreviousNode::PreviousNode( ) :
IActionUI( "Edit/PreviousNode", "Previous", "PreviousNode", PREVIOUS, "<control>Up", new vgAlg::actions::PreviousNode() )
{
}



const bool PreviousNode::isValide( State state ) const
{
	if( state.getLocation() == TREE )
	{
		if( state.getParent() && state.getSelectedNode() )
		{
			const int index = state.getParent()->findChild( state.getSelectedNode() );
			if ( index > 0 )
			{
				return true;
			}
		}
	}
	return false;
}



} // namespace actions

} // namespace vgUI
