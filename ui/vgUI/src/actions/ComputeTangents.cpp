// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/actions/ComputeTangents.hpp"

#include <vgAlg/actions/ComputeTangents.hpp>



namespace vgUI
{

namespace actions
{


META_ACTION_CPP( ComputeTangents, 25 )


ComputeTangents::ComputeTangents( )
: IActionUI( "Transform/Tangents/ComputeTangents", "Compute", "ComputeTangents", DEFAULT, "", new vgAlg::actions::ComputeTangents() )
{}



const bool ComputeTangents::isValide( State state )
{
	return state.isShape();
}



} // namespace actions

} // namespace vgUI
