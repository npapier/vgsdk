// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/HideNode.hpp"

#include <vgAlg/actions/HideNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( HideNode, 32 )


HideNode::HideNode( ) :
IActionUI( "Visibility/HideNode", "Hide", "HideNode", DEFAULT, "", new vgAlg::actions::HideNode() )
{
}



const bool HideNode::isValide( State state )
{
	if( state.isShape() && !state.isHidden() )
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
