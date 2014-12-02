// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/SetToDefault.hpp"

#include <vgAlg/actions/SetToDefault.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( SetToDefault, 31 )


SetToDefault::SetToDefault( ) :
IActionUI( "Transform/Fields/SetToDefault", "SetToDefault", "SetToDefault", DEFAULT, "", new vgAlg::actions::SetToDefault() )
{
}



const bool SetToDefault::isValide( State state )
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

#endif // #ifdef __USE_VGALG__
