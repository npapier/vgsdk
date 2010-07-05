// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_EXPORTNODE_HPP
#define _VGALG_ACTIONS_EXPORTNODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>
#include <vgAlg/actions/input/IStringInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Export the node.
 */
struct VGALG_API ExportNode : public IAction, input::INodeInput, input::IParentInput, input::IStringInput
{

	ExportNode();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_EXPORTNODE_HPP
