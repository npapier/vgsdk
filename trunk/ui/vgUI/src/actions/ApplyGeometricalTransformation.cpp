// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/ApplyGeometricalTransformation.hpp"

#include <vgAlg/actions/ApplyGeometricalTransformation.hpp>


namespace vgUI
{

namespace actions
{



ApplyGeometricalTransformation::ApplyGeometricalTransformation( ) :
IActionUI( "Transform/ApplyGeometricalTransformation", "ApplyGeometricalTransformation", "ApplyGeometricalTransformation", DEFAULT, "", new vgAlg::actions::ApplyGeometricalTransformation() )
{
}



const bool ApplyGeometricalTransformation::isValide( State state ) const
{
	return true;
}



} // namespace actions

} // namespace vgUI
