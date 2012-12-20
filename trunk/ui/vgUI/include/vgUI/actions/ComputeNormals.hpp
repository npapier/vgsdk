// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGUI_ACTIONS_COMPUTENORMALS_HPP
#define _VGUI_ACTIONS_COMPUTENORMALS_HPP

#include "vgUI/vgUI.hpp"

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgUI
{

namespace actions
{

struct VGUI_API ComputeNormals : public IActionUI
{
	META_ACTION_HPP( ComputeNormals );

	ComputeNormals();

	virtual const bool isValide( State state );

};


} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_COMPUTENORMALS_HPP
