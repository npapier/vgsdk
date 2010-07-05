// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_HIDENODE_HPP
#define _VGALG_ACTIONS_HIDENODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Hide selected shape.
 */
struct VGALG_API HideNode : public IAction, input::INodeInput
{

	HideNode();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_HIDENODE_HPP
