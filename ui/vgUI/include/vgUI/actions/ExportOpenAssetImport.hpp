// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGUI_ACTIONS_EXPORTOPENASSETIMPORT_HPP
#define _VGUI_ACTIONS_EXPORTOPENASSETIMPORT_HPP

#include "vgUI/vgUI.hpp"

#include <vgUI/actions/ActionsRegistry.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgUI
{

namespace actions
{

// EXPORTOPENASSETIMPORTCOLLADA
struct VGUI_API ExportOpenAssetImportCollada : public IActionUI
{
	META_ACTION_HPP( ExportOpenAssetImportCollada );

	ExportOpenAssetImportCollada();

	virtual const bool isValide( State state );
};


// EXPORTOPENASSETIMPORTOBJ
struct VGUI_API ExportOpenAssetImportObj : public IActionUI
{
	META_ACTION_HPP( ExportOpenAssetImportObj );

	ExportOpenAssetImportObj();

	virtual const bool isValide( State state );
};


// EXPORTOPENASSETIMPORTSTL
struct VGUI_API ExportOpenAssetImportStl : public IActionUI
{
	META_ACTION_HPP( ExportOpenAssetImportStl );

	ExportOpenAssetImportStl();

	virtual const bool isValide( State state );
};


// EXPORTOPENASSETIMPORTPLY
struct VGUI_API ExportOpenAssetImportPly : public IActionUI
{
	META_ACTION_HPP( ExportOpenAssetImportPly );

	ExportOpenAssetImportPly();

	virtual const bool isValide( State state );
};


} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_EXPORTOPENASSETIMPORT_HPP
