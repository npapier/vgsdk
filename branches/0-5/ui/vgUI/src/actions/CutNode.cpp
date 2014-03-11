// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/CutNode.hpp"

#include <vgAlg/actions/CutNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( CutNode, 11 )


CutNode::CutNode( ) :
IActionUI( "Edit/CutNode", "Cut", "CutNode", CUT, "<control>X", new vgAlg::actions::CutNode() )
{
}



const bool CutNode::isValide( State state )
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
