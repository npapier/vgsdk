// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/ExportNode.hpp"

#include <vgAlg/actions/ExportNode.hpp>


namespace vgUI
{

namespace actions
{

ExportNode::ExportNode( ) :
IActionUI( "ExportNode", "Export", "ExportNode", EXPORT, "", new vgAlg::actions::ExportNode() )
{
}



const bool ExportNode::isValide( State state ) const
{
	if( state.getSelectedNode() )
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
