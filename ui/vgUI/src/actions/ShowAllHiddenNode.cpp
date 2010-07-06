// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/ShowAllHiddenNode.hpp"

#include <vgAlg/actions/ShowAllHiddenNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( ShowAllHiddenNode, 33 )


ShowAllHiddenNode::ShowAllHiddenNode( ) :
IActionUI( "Visibility/ShowAllHiddenNode", "Show all", "ShowAllHiddenNode", DEFAULT, "", new vgAlg::actions::ShowAllHiddenNode() )
{
}



const bool ShowAllHiddenNode::isValide( State state ) const
{
	if( state.getNumberOfHiddenNode() > 0 )
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
