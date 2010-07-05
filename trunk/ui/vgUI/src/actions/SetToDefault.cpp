// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/SetToDefault.hpp"

#include <vgAlg/actions/SetToDefault.hpp>


namespace vgUI
{

namespace actions
{



SetToDefault::SetToDefault( ) :
IActionUI( "Transform/SetToDefault", "SetToDefault", "SetToDefault", DEFAULT, "", new vgAlg::actions::SetToDefault() )
{
}



const bool SetToDefault::isValide( State state ) const
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
