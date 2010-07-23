// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGUI_ACTIONS_SHOWNODE_HPP
#define _VGUI_ACTIONS_SHOWNODE_HPP


#include "vgUI/vgUI.hpp"

#include <vgAlg/actions/HiddenNode.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgUI
{

namespace actions
{


struct VGUI_API ShowNode : public IActionUI
{
	ShowNode();

	ShowNode( vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode );

	virtual const bool isValide( State state );

private:
	vgd::WeakPtr < vgAlg::actions::HiddenNode > m_hiddenNode;

};

} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_SHOWNODE_HPP
