// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/InvertTriangleOrientation.hpp"

#include <vgAlg/actions/InvertTriangleOrientation.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( InvertTriangleOrientation, 30 )


InvertTriangleOrientation::InvertTriangleOrientation( ) :
IActionUI( "Transform/InvertTriangleOrientation", "InvertTriangleOrientation", "InvertTriangleOrientation", DEFAULT, "", new vgAlg::actions::InvertTriangleOrientation() )
{}



const bool InvertTriangleOrientation::isValide( State state )
{
	return state.isShape();
}



} // namespace actions

} // namespace vgUI

#endif // #ifdef __USE_VGALG__
