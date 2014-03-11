// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_HIDEALLEXCEPTSELECTEDNODE_HPP
#define _VGALG_ACTIONS_HIDEALLEXCEPTSELECTEDNODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IRootInput.hpp>

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Hide all shape in graph except selected shape.
 */
struct VGALG_API HideAllExceptSelectedNode : public IAction, input::INodeInput, input::IRootInput
{

	HideAllExceptSelectedNode();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_HIDEALLEXCEPTSELECTEDNODE_HPP
