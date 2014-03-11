// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_ACTIONS_COMPUTETANGENTS_HPP
#define _VGALG_ACTIONS_COMPUTETANGENTS_HPP

#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Compute tangents for a vertex shape.
 */
struct VGALG_API ComputeTangents : public IAction, input::INodeInput
{

	ComputeTangents();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_COMPUTETANGENTS_HPP
