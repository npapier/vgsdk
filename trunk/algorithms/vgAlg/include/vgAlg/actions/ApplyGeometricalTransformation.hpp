// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_APLLYGEOMETRICALTRANSFORMATION_HPP
#define _VGALG_ACTIONS_APLLYGEOMETRICALTRANSFORMATION_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/IRootInput.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/Shp.hpp>

namespace vgAlg
{

namespace actions
{

/**
 * @brief	Apply all geometrical transformation to each node and delete all transform/matrixtransform node.
 */
struct VGALG_API ApplyGeometricalTransformation : public IAction, input::IRootInput
{

	ApplyGeometricalTransformation();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_APLLYGEOMETRICALTRANSFORMATION_HPP
