// VGSDK - Copyright (C) 2013, 2014 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_ACTIONS_EXPORTOPENASSETIMPORT_HPP
#define _VGUI_ACTIONS_EXPORTOPENASSETIMPORT_HPP

#include "vgUI/vgUI.hpp"

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgUI
{

namespace actions
{


/**
 * @brief	Generic class for UI actions dedicated to the integration of vgOpenAssetImport::actions::aiExport specializations.
 */
template< typename aiExportT >
struct ExportOpenAssetImport : public IActionUI
{
	ExportOpenAssetImport()
	: IActionUI( "Export", "Export", "ExportOpenAssetImport", EXPORT, "", new aiExportT() )
	{}

	const bool isValide( State state )
	{
		return state.isShape();
	}
};


} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_EXPORTOPENASSETIMPORT_HPP

