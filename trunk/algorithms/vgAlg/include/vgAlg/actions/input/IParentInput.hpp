// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_INPUT_IPARENTINPUT_HPP
#define _VGALG_ACTIONS_INPUT_IPARENTINPUT_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgd/node/Group.hpp>
#include <vgd/Shp.hpp>

namespace vgAlg
{

namespace actions
{

namespace input
{

/**
 * @brief	Interface to add parent group getter/setter to an action.
 */
struct VGALG_API IParentInput
{
	void setParent( vgd::Shp< vgd::node::Group > parent );

	vgd::Shp< vgd::node::Group > getParent();


protected:
	vgd::WeakPtr< vgd::node::Group > m_parent;
};

} // namespace input

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_INPUT_IPARENTINPUT_HPP
