// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_SETOPTIONALTODEFAULT_HPP
#define _VGALG_ACTIONS_SETOPTIONALTODEFAULT_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Set optional field to default to current node.
 */
struct VGALG_API SetOptionalToDefault : public IAction, input::INodeInput
{

	SetOptionalToDefault();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_SETOPTIONALTODEFAULT_HPP
