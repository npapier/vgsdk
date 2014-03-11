// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_PASTENODE_HPP
#define _VGALG_ACTIONS_PASTENODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Paste clipboarded node next to current node.
 */
struct VGALG_API PasteNode : public IAction, input::INodeInput, input::IParentInput
{

	PasteNode();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_PASTENODE_HPP
