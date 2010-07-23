// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGUI_ACTIONS_INVERTTIRANGLEORIENTATION_HPP
#define _VGUI_ACTIONS_INVERTTIRANGLEORIENTATION_HPP


#include "vgUI/vgUI.hpp"

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/IActionUI.hpp>

namespace vgUI
{

namespace actions
{


struct VGUI_API InvertTriangleOrientation : public IActionUI
{
	META_ACTION_HPP( InvertTriangleOrientation );

	InvertTriangleOrientation();

	virtual const bool isValide( State state );

};

} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_INVERTTIRANGLEORIENTATION_HPP
