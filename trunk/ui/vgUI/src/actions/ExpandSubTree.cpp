// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/ExpandSubTree.hpp"

#include <vgAlg/actions/ExpandSubTree.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( ExpandSubTree, 40 )


ExpandSubTree::ExpandSubTree( ) :
IActionUI( "ExpandSubTree", "Expand", "ExpandSubTree", DEFAULT, "", new vgAlg::actions::ExpandSubTree() )
{
}



const bool ExpandSubTree::isValide( State state ) const
{
	if( state.getLocation() == TREE && state.isGroup() )
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
