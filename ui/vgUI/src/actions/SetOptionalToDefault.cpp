// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/SetOptionalToDefault.hpp"

#include <vgAlg/actions/SetOptionalToDefault.hpp>


namespace vgUI
{

namespace actions
{



SetOptionalToDefault::SetOptionalToDefault( ) :
IActionUI( "Transform/SetOptionalToDefault", "SetOptionalToDefault", "SetOptionalToDefault", DEFAULT, "", new vgAlg::actions::SetOptionalToDefault() )
{
}



const bool SetOptionalToDefault::isValide( State state ) const
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
