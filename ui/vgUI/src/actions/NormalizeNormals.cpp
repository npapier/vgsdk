// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/actions/NormalizeNormals.hpp"

#include <vgAlg/actions/NormalizeNormals.hpp>



namespace vgUI
{

namespace actions
{


META_ACTION_CPP( NormalizeNormals, 22 )


NormalizeNormals::NormalizeNormals( )
: IActionUI( "Transform/Normals/NormalizeNormals", "Normalize", "NormalizeNormals", DEFAULT, "", new vgAlg::actions::NormalizeNormals() )
{}



const bool NormalizeNormals::isValide( State state )
{
	return state.isShape();
}



} // namespace actions

} // namespace vgUI
