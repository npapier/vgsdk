// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ACTIONS_ALG_EXPORT_HPP_
#define _VGQT_ACTIONS_ALG_EXPORT_HPP_

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
 * @brief Popup export file windows.
 */
struct VGQT_API ExportNode : public vgAlg::actions::IAction, vgAlg::actions::input::INodeInput, vgAlg::actions::input::IParentInput
{
    ExportNode();

	~ExportNode();

	virtual void execute();

private:

};



} // namespace alg

} // namespace actions

} // namespace vgQt


#endif // _VGQT_ACTIONS_ALG_EXPORT_HPP_

