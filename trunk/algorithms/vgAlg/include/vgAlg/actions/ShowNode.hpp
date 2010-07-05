// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_SHOWNODE_HPP
#define _VGALG_ACTIONS_SHOWNODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/IHiddenNodeInput.hpp>

#include <vgd/Shp.hpp>

namespace vgAlg
{

namespace actions
{

/**
 * @brief	Show selected node.
 */
struct VGALG_API ShowNode : public IAction, input::IHiddenNodeInput
{

	ShowNode();

	ShowNode( vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode );

	virtual void execute();
};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_SHOWNODE_HPP
