// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_PREVIOUSNODE_HPP
#define _VGALG_ACTIONS_PREVIOUSNODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Switch the node with its brother to put it back.
 */
struct VGALG_API PreviousNode : public IAction, input::INodeInput, input::IParentInput
{

	PreviousNode();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_PREVIOUSNODE_HPP
