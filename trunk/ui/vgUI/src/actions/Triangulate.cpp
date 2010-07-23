// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/Triangulate.hpp"

#include <vgAlg/actions/Triangulate.hpp>


namespace vgUI
{

namespace actions
{

META_ACTION_CPP( Triangulate, 25 )


Triangulate::Triangulate( ) :
IActionUI( "Transform/Triangulate", "Triangulate", "Triangulate", DEFAULT, "", new vgAlg::actions::Triangulate() )
{
}



const bool Triangulate::isValide( State state )
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
