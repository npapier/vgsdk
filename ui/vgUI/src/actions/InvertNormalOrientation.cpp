// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/InvertNormalOrientation.hpp"

#include <vgAlg/actions/InvertNormalOrientation.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( InvertNormalOrientation, 21 )


InvertNormalOrientation::InvertNormalOrientation( ) :
IActionUI( "Transform/InvertNormalOrientation", "InvertNormalOrientation", "InvertNormalOrientation", DEFAULT, "", new vgAlg::actions::InvertNormalOrientation() )
{
}



const bool InvertNormalOrientation::isValide( State state ) const
{
	if( state.isShape() )
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
