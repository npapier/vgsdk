// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_INPUT_IROOTINPUT_HPP
#define _VGALG_ACTIONS_INPUT_IROOTINPUT_HPP


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
 * @brief	Interface to add root node getter/setter to an action.
 */
struct VGALG_API IRootInput
{
	void setRoot( vgd::Shp< vgd::node::Group > root );

	vgd::Shp< vgd::node::Group > getRoot();


protected:
	vgd::Shp< vgd::node::Group > m_root;
};

} // namespace input

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_INPUT_IROOTINPUT_HPP
