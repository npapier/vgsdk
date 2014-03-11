// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_INPUT_IHIDDENNODEINPUT_HPP
#define _VGALG_ACTIONS_INPUT_IHIDDENNODEINPUT_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/HiddenNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>

namespace vgAlg
{

namespace actions
{

namespace input
{

/**
 * @brief	Interface to add hidden node getter/setter to an action.
 */
struct VGALG_API IHiddenNodeInput
{
	void setHiddenNode( vgd::Shp < vgAlg::actions::HiddenNode > hiddenNode );

	vgd::Shp < vgAlg::actions::HiddenNode > getHiddenNode();


protected:
	vgd::Wkp< vgAlg::actions::HiddenNode > m_hiddenNode;
};

} // namespace input

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_INPUT_IHIDDENNODEINPUT_HPP
