// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/PasteNode.hpp"

#include <vgAlg/actions/PasteNode.hpp>


namespace vgUI
{

namespace actions
{



PasteNode::PasteNode( ) :
IActionUI( "Edit/PasteNode", "Paste", "PasteNode", PASTE, "<control>V", new vgAlg::actions::PasteNode() )
{
	m_menuContrib = "Edit/PasteNode";
	m_name = "Paste";
	m_id = "PasteNode";
	m_icon = PASTE;
	m_accelKey = "<control>V";
	m_action = vgd::makeShp( new vgAlg::actions::PasteNode() );
}



const bool PasteNode::isValide( State state ) const
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
