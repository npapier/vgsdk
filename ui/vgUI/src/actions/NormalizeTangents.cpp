// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifdef __USE_VGALG__

#include "vgUI/actions/NormalizeTangents.hpp"

#include <vgAlg/actions/NormalizeTangents.hpp>



namespace vgUI
{

namespace actions
{


META_ACTION_CPP( NormalizeTangents, 26 )


NormalizeTangents::NormalizeTangents( )
: IActionUI( "Transform/Tangents/NormalizeTangents", "Normalize", "NormalizeTangents", DEFAULT, "", new vgAlg::actions::NormalizeTangents() )
{}



const bool NormalizeTangents::isValide( State state )
{
	return state.isShape();
}



} // namespace actions

} // namespace vgUI

#endif // #ifdef __USE_VGALG__
