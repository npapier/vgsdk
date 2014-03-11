// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_EXPORTNODE_HPP
#define _VGALG_ACTIONS_EXPORTNODE_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>

#include <vgOpenCOLLADA/Settings.hpp>

namespace vgOpenCOLLADA
{

namespace actions
{

/**
 * @brief	Export the node.
 */
struct VGOPENCOLLADA_API ExportNode : public vgAlg::actions::IAction, public vgAlg::actions::input::INodeInput, public vgAlg::actions::input::IParentInput
{

	ExportNode();

	virtual void execute();

	void setExportSettings( vgOpenCOLLADA::Settings exportSettings );

private:

	vgOpenCOLLADA::Settings m_exportSettings;
};

} // namespace actions

} // namespace vgOpenCOLLADA

#endif //#ifndef _VGALG_ACTIONS_EXPORTNODE_HPP
