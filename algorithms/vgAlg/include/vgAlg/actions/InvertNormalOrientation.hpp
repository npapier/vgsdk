// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_INVERTNORMALORIENTATION_HPP
#define _VGALG_ACTIONS_INVERTNORMALORIENTATION_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Invert normal orientation fo the node.
 */
struct VGALG_API InvertNormalOrientation : public IAction, input::INodeInput
{

	InvertNormalOrientation();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_INVERTNORMALORIENTATION_HPP
