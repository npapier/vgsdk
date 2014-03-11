// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_EXPANDSUBTREE_HPP
#define _VGALG_ACTIONS_EXPANDSUBTREE_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Expand sub tree in vgGTK::graph::Browser
 */
struct VGALG_API ExpandSubTree : public IAction
{

	ExpandSubTree();

	virtual void execute();

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_EXPANDSUBTREE_HPP
