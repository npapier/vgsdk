// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_SHOWALLHIDDENNODE_HPP
#define _VGALG_ACTIONS_SHOWALLHIDDENNODE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/HiddenNode.hpp>
#include <vgd/Shp.hpp>

#include <vgAlg/actions/IAction.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Show all hidden node.
 */
struct VGALG_API ShowAllHiddenNode : public IAction
{

	ShowAllHiddenNode();

	virtual void execute();
};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_SHOWALLHIDDENNODE_HPP
