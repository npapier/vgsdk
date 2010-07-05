// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_GETNODEINTREE_HPP
#define _VGALG_ACTIONS_GETNODEINTREE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Select the node in vgGTK::graph::Browser
 */
struct VGALG_API GetNodeInTree : public IAction, input::INodeInput
{

	GetNodeInTree();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_GETNODEINTREE_HPP
