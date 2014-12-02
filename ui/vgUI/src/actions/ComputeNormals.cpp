// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifdef __USE_VGALG__

#include "vgUI/actions/ComputeNormals.hpp"

#include <vgAlg/actions/ComputeNormals.hpp>



namespace vgUI
{

namespace actions
{


META_ACTION_CPP( ComputeNormals, 21 )


ComputeNormals::ComputeNormals( )
: IActionUI( "Transform/Normals/ComputeNormals", "Compute", "ComputeNormals", DEFAULT, "", new vgAlg::actions::ComputeNormals() )
{}



const bool ComputeNormals::isValide( State state )
{
	return state.isShape();
}



} // namespace actions

} // namespace vgUI

#endif // #ifdef __USE_VGALG__
