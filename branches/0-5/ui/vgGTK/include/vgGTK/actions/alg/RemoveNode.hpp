// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONS_ALG_REMOVENODE_HPP_
#define _VGGTK_ACTIONS_ALG_REMOVENODE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>

namespace vgGTK
{

namespace actions
{

namespace alg
{


/**
 * @brief Popup remove confirmation.
 */
	struct VGGTK_API RemoveNode : public vgAlg::actions::IAction, vgAlg::actions::input::INodeInput, vgAlg::actions::input::IParentInput
{
	RemoveNode();

	~RemoveNode();

	virtual void execute();


private:


};


} // namespace alg

} // namespace actions

} // namespace vgGTK

#endif /*_VGGTK_ACTIONS_ALG_REMOVENODE_HPP_*/

