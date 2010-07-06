// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/HideAllNode.hpp"

#include <vgAlg/actions/HideAllNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( HideAllNode, 31 )


HideAllNode::HideAllNode( ) :
IActionUI( "Visibility/HideAllNode", "Hide all", "HideAllNode", DEFAULT, "", new vgAlg::actions::HideAllNode() )
{
}



const bool HideAllNode::isValide( State state ) const
{
	if( state.getNumberOfDisplayedNode() > 0 )
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
