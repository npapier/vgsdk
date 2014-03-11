// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_CUTNODE_HPP
#define _VGALG_ACTIONS_CUTNODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Cut a node and put it in SelectedNode clipboard.
 */
struct VGALG_API CutNode : public IAction, input::INodeInput, input::IParentInput
{

	CutNode();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_CUTNODE_HPP
