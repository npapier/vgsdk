// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/CopyNode.hpp"

#include <vgAlg/actions/CopyNode.hpp>


namespace vgUI
{

namespace actions
{



CopyNode::CopyNode( ) :
IActionUI( "Edit/CopyNode", "Copy", "CopyNode", COPY, "<control>C", new vgAlg::actions::CopyNode() )
{
}



const bool CopyNode::isValide( State state ) const
{
	return ( state.getSelectedNode() && !state.isRoot() );
}



} // namespace actions

} // namespace vgUI

