// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ACTIONS_ALG_REMOVENODE_HPP_
#define _VGQT_ACTIONS_ALG_REMOVENODE_HPP_

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace actions
{

namespace alg
{


/**
 * @brief Popup remove confirmation.
 */
struct VGQT_API RemoveNode : public vgAlg::actions::IAction, vgAlg::actions::input::INodeInput, vgAlg::actions::input::IParentInput
{
    RemoveNode();

    ~RemoveNode();

    virtual void execute();


private:


};


} // namespace alg

} // namespace actions

} // namespace vgQt

#endif // _VGQT_ACTIONS_ALG_REMOVENODE_HPP_
