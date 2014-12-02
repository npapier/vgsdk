// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/PasteNode.hpp"

#include <vgAlg/actions/PasteNode.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( PasteNode, 12 )


PasteNode::PasteNode( ) :
IActionUI( "Edit/PasteNode", "Paste", "PasteNode", PASTE, "<control>V", new vgAlg::actions::PasteNode() )
{
}



const bool PasteNode::isValide( State state )
{
	if( state.getLocation() == TREE && state.hasAClipboardedNode() )
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
